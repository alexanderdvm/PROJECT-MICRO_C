// // Directivas
#include <16f877a.h>
#fuses xt, nowdt
#use delay(clock=4000000)

#include <lcd.c>

// Configuraci�n de E/S
#use standard_io(C)
#use standard_io(B)

// Prototipos de funciones
void Mostrar_Mensaje_Inicial();
void Ingresar_Codigo();
void Verificar_Codigo();
void Reiniciar_Sistema();
void Bloqueo_Sistema();
void Configurar_Modo();
void Mostrar_Digitos(int);

// Variables globales
int codigo_ingresado[4];
int codigo_secreto[4] = {4, 3, 2, 1}; // C�digo predefinido
int indice = 0;
int intentos_fallidos = 0;
int modo_configuracion = 0;
int primer_intento_fallido = 0; // Para controlar el primer intento fallido
int primer_ingreso = 1; // Para mostrar el mensaje de bienvenida solo la primera vez

// Programa principal
void main() {
    // Configuraci�n de perif�ricos
    port_b_pullups(true); // Activamos las resistencias de pullup del puerto B
    lcd_init();           // Inicializamos el LCD

    // Mostrar mensaje de bienvenida solo al inicio
    if (primer_ingreso) {
        Mostrar_Mensaje_Inicial();
        primer_ingreso = 0; // Cambiamos el estado para que no se vuelva a mostrar
    }

    // Bucle infinito
    while (1) {
        if (modo_configuracion) {
            Configurar_Modo();
        } else {
            Ingresar_Codigo();
            Verificar_Codigo();
            Reiniciar_Sistema();
        }
    }
}

// Funci�n para mostrar mensaje inicial en el LCD
void Mostrar_Mensaje_Inicial() {
    lcd_putc('\f');
    lcd_putc("Bienvenido!");
    delay_ms(2000);
    lcd_putc('\f');
    lcd_putc("Ingrese Codigo");
}

// Funci�n para ingresar el c�digo
void Ingresar_Codigo() {
    int boton_soltado1 = 1, boton_soltado2 = 1, boton_soltado3 = 1;
    int digito_actual = 0;
    indice = 0;

    while (indice < 4) {
        // Comprobar entrada en modo configuraci�n
        if (input(PIN_B1) == 0 && input(PIN_B2) == 0) {
            modo_configuracion = 1;
            return; // Salimos de la funci�n para entrar en configuraci�n
        }

        // Incrementar el valor del d�gito (Bot�n 1)
        if (input(PIN_B0) == 0 && boton_soltado1 == 1) {
            delay_ms(20);
            boton_soltado1 = 0;
            digito_actual++;
            if (digito_actual > 9) digito_actual = 0;
            Mostrar_Digitos(digito_actual);
        }
        if (input(PIN_B0) == 1 && boton_soltado1 == 0) {
            delay_ms(20);
            boton_soltado1 = 1;
        }

        // Confirmar d�gito (Bot�n 2)
        if (input(PIN_B1) == 0 && boton_soltado2 == 1) {
            delay_ms(20);
            boton_soltado2 = 0;
            codigo_ingresado[indice] = digito_actual;
            indice++;
            if (indice < 4) digito_actual = 0; // Reiniciar para el pr�ximo d�gito
        }
        if (input(PIN_B1) == 1 && boton_soltado2 == 0) {
            delay_ms(20);
            boton_soltado2 = 1;
        }

        // Reiniciar el ingreso del c�digo (Bot�n 3)
        if (input(PIN_B2) == 0 && boton_soltado3 == 1) {
            delay_ms(20);
            boton_soltado3 = 0;
            lcd_putc('\f');
            lcd_putc("Se reinicio el");
            lcd_putc('\n');
            lcd_putc("sistema");
            delay_ms(2000); // Mantener el mensaje de reinicio por 2 segundos
            indice = 0;
            digito_actual = 0;
            lcd_putc('\f');
            lcd_putc("Ingrese Codigo");
        }
        if (input(PIN_B2) == 1 && boton_soltado3 == 0) {
            delay_ms(20);
            boton_soltado3 = 1;
        }
    }
}

// Funci�n para mostrar los d�gitos en el LCD
void Mostrar_Digitos(int digito) {
    lcd_putc('\f');
    lcd_gotoxy(1, 1);
    lcd_putc("Codigo: ");
    if (indice > 1) {
        lcd_putc(codigo_ingresado[indice - 2] + '0');
        lcd_putc(codigo_ingresado[indice - 1] + '0');
    }
    lcd_putc(digito + '0');
}

// Funci�n para verificar el c�digo ingresado
void Verificar_Codigo() {
    int correcto = 1; // Suponemos que el c�digo es correcto
    for (int i = 0; i < 4; i++) {
        if (codigo_ingresado[i] != codigo_secreto[i]) {
            correcto = 0; // Si un d�gito no coincide, marcamos como incorrecto
            break;
        }
    }

    if (correcto) {
        lcd_putc('\f');
        lcd_putc("Acceso Concedido");
        output_high(PIN_C0); // LED1 ON
        delay_ms(5000);
        output_low(PIN_C0);
        intentos_fallidos = 0; // Reiniciar el contador de intentos fallidos
        primer_intento_fallido = 0; // Reiniciar el indicador de primer intento fallido
    } else {
        lcd_putc('\f');
        output_high(PIN_C1); // LED2 ON
        lcd_putc("Intento fallido");
        delay_ms(1000); // Mantener "Intento fallido" por 1 segundo

        // Mostrar "Intente de nuevo" en una nueva l�nea
        lcd_putc('\f'); // Limpiar el LCD
        lcd_putc("Intente de nuevo");
        
        // Parpadeo del LED de intento fallido
        for (int j = 0; j < 5; j++) {
            output_toggle(PIN_C1);
            delay_ms(300); // Tiempo de parpadeo
        }
        output_low(PIN_C1);
        
        intentos_fallidos++;
        if (intentos_fallidos >= 3) {
            Bloqueo_Sistema(); // Llamamos a la funci�n de bloqueo
        }
    }
}

// Funci�n para reiniciar el sistema
void Reiniciar_Sistema() {
    delay_ms(5000);
    lcd_putc('\f');
    lcd_putc("Ingrese Codigo"); // Mostrar mensaje de ingreso de c�digo
}

// Funci�n para bloquear el sistema
void Bloqueo_Sistema() {
    lcd_putc('\f');
    lcd_putc("Sistema Bloqueado");
    output_high(PIN_C2); // LED3 ON
    output_high(PIN_C3); // LED4 ON
    delay_ms(10000); // Bloqueo por 10 segundos
    output_low(PIN_C2);
    output_low(PIN_C3);
    intentos_fallidos = 0; // Reiniciar el contador de intentos fallidos
    primer_intento_fallido = 0; // Reiniciar el indicador de primer intento fallido
}

// Funci�n para el modo de configuraci�n
void Configurar_Modo() {
    int boton_soltado1 = 1, boton_soltado2 = 1;
    int nuevo_codigo[4];
    int nuevo_indice = 0;
    int digito_actual = 0;

    output_high(PIN_C4); // Encender LED5 al entrar en modo de configuraci�n
    lcd_putc('\f');
    lcd_putc("Configurar Codigo");
    while (nuevo_indice < 4) {
        // Incrementar el valor del d�gito (Bot�n 1)
        if (input(PIN_B0) == 0 && boton_soltado1 == 1) {
            delay_ms(20);
            boton_soltado1 = 0;
            digito_actual++;
            if (digito_actual > 9) digito_actual = 0;
            Mostrar_Digitos(digito_actual);
        }
        if (input(PIN_B0) == 1 && boton_soltado1 == 0) {
            delay_ms(20);
            boton_soltado1 = 1;
        }

        // Confirmar d�gito (Bot�n 2)
        if (input(PIN_B1) == 0 && boton_soltado2 == 1) {
            delay_ms(20);
            boton_soltado2 = 0;
            nuevo_codigo[nuevo_indice] = digito_actual;
            nuevo_indice++;
            if (nuevo_indice < 4) digito_actual = 0; // Reiniciar para el pr�ximo d�gito
        }
        if (input(PIN_B1) == 1 && boton_soltado2 == 0) {
            delay_ms(20);
            boton_soltado2 = 1;
        }
    }

    // Actualizar el c�digo secreto con el nuevo c�dig
    for (int i = 0; i < 4; i++) {
        codigo_secreto[i] = nuevo_codigo[i];
    }

    output_low(PIN_C4); // Apagar LED5 al cambiar la clave
    lcd_putc('\f');
    lcd_putc("Codigo Guardado!");
    delay_ms(2000);
    lcd_putc('\f');
    lcd_putc("Ingrese Codigo");

    modo_configuracion = 0; // Salir del modo de configuraci�n
} 