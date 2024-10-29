# PROJECT-MICRO_C

# Sistema de Control de Acceso con Código Secreto

Este proyecto implementa un sistema de control de acceso con un **microcontrolador PIC16F877A**, diseñado para validar la entrada mediante un código secreto de 4 dígitos. El sistema utiliza una pantalla LCD para mostrar instrucciones, confirmaciones y el estado del acceso, junto con LEDs para indicar el éxito o error en el ingreso. Este proyecto está desarrollado en **MPLAB X IDE** y utiliza el compilador **CCS C**.

## Tabla de Contenidos

- [Descripción del Proyecto](#descripción-del-proyecto)
- [Requisitos del Sistema](#requisitos-del-sistema)
- [Hardware Utilizado](#hardware-utilizado)
- [Configuración del Proyecto](#configuración-del-proyecto)
- [Funcionamiento del Sistema](#funcionamiento-del-sistema)
- [Modo de Configuración del Código](#modo-de-configuración-del-código)
- [Pantalla de Bienvenida](#pantalla-de-bienvenida)
- [Instalación y Ejecución](#instalación-y-ejecución)
- [Licencia](#licencia)

## Descripción del Proyecto

El sistema de control de acceso permite la entrada solo a personas que ingresen un código secreto correcto de 4 dígitos. Los dígitos se ingresan mediante botones que simulan un teclado numérico, y el sistema proporciona retroalimentación visual en una pantalla LCD. Además, se incluyen LEDs para indicar el resultado del acceso.

## Requisitos del Sistema

1. **Ingreso del Código Secreto:**
   - **Botón 1 (Incrementar):** Incrementa el valor del dígito actual de 0 a 9. Al alcanzar 9, vuelve a 0.
   - **Botón 2 (Seleccionar/Confirmar dígito):** Confirma el dígito actual y avanza al siguiente. Cuando se ingresan los 4 dígitos, este botón termina la entrada del código.
   - **Botón 3 (Reiniciar):** Reinicia la entrada del código en caso de error.

2. **Visualización en LCD:**
   - La pantalla LCD muestra cada dígito ingresado de forma secuencial y mantiene ocultos los primeros dígitos para mayor seguridad. Por ejemplo, si el código ingresado es "3485", la pantalla muestra:
     - Después de "3" y "4": muestra "\*\*34".
     - Después de "8": muestra "\*\348".
     - Después de "5": muestra "3485".

3. **Verificación del Código:**
   - **Código predeterminado:** **4321**
   - **Acceso Concedido:** Muestra "Acceso Concedido" en el LCD y enciende el LED1.
   - **Acceso Denegado:** Muestra "Acceso Denegado" en el LCD y enciende el LED2, que permanece encendido por 5 segundos para indicar el rechazo.

4. **Reinicio del Sistema:**
   - Después de cada intento (exitoso o fallido), el sistema se reinicia automáticamente en 5 segundos, y el LCD vuelve a mostrar "Ingrese Código".

5. **Bloqueo por Intentos Fallidos:**
   - Si se ingresa incorrectamente el código en **3 intentos consecutivos**, el sistema se bloquea por 10 segundos y muestra "Sistema Bloqueado" en el LCD. Los LEDs LED3 y LED4 permanecen encendidos durante el tiempo de bloqueo.

6. **Modo de Configuración del Código:**
   - Al presionar simultáneamente el **Botón 2** y el **Botón 3**, el sistema entra en modo de configuración. En este modo, el usuario puede ingresar un nuevo código de 4 dígitos para reemplazar el código predefinido. El LED5 parpadea mientras el sistema se encuentra en modo de configuración.

7. **Pantalla de Bienvenida:**
   - Al iniciar el sistema o tras un reinicio, el LCD muestra un mensaje de bienvenida personalizado, por ejemplo, "Bienvenido, Ingrese Código".

## Hardware Utilizado

- **Microcontrolador:** PIC16F877A
- **IDE:** MPLAB X IDE
- **Compilador:** CCS C Compiler
- **Pantalla LCD 16x2**
- **Botones para ingreso de código**
- **LEDs de retroalimentación**

## Configuración del Proyecto

1. **Configuración de Hardware:**
   - Conectar los botones, pantalla LCD y LEDs siguiendo el esquema de conexión especificado.
2. **Configuración de Software:**
   - El código está desarrollado en **MPLAB X IDE** usando **CCS C Compiler** para PIC.
   - Programar el PIC16F877A con el archivo compilado utilizando un programador compatible.
   - Simulacioon del hardware con **PROTEUS** en el archivo **PARCIAL 2 MICROC PROTEUS [20241018, 20-56-55].pdsprj**

## Funcionamiento del Sistema

1. **Ingreso del Código Secreto:** 
   - El usuario ingresa un código de 4 dígitos usando los botones, y la pantalla LCD muestra el progreso de forma segura.
   
2. **Verificación del Código:** 
   - Una vez ingresado el código, el sistema lo verifica con el código predefinido o el último configurado.
   
3. **Retroalimentación Visual:** 
   - El resultado del intento se muestra en el LCD y se indica también mediante LEDs.
   
4. **Reinicio Automático:** 
   - El sistema se reinicia tras cada intento para permitir otro ingreso.

## Modo de Configuración del Código

En el modo de configuración, el usuario puede establecer un nuevo código de 4 dígitos. El LED5 parpadea indicando que el sistema se encuentra en modo de configuración. El nuevo código reemplazará el código predeterminado hasta que el sistema se resetee nuevamente.

## Pantalla de Bienvenida

Al iniciar el sistema, el LCD muestra un mensaje de bienvenida personalizado antes de solicitar el código de acceso.

## Instalación y Ejecución

1. **Compilar el Código:** Utilizar el **CCS C Compiler** en **MPLAB X IDE** para compilar el proyecto.
2. **Programar el PIC16F877A:** Conectar el programador compatible y cargar el archivo compilado.
3. **Configurar Hardware:** Conectar los botones, LEDs y LCD siguiendo el esquema de hardware.
4. **Ejecutar el Sistema:** Al encender, el sistema estará listo para recibir el código y operará de acuerdo a los requerimientos.

## Licencia

Este proyecto se distribuye bajo la [Licencia MIT](LICENSE).
