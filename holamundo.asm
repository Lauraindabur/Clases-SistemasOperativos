section .data                 ; Sección para datos inicializados (variables, cadenas de texto, etc.)
    msg db 'Hola Mundo!', 0xA  ; Define 'msg' como una cadena de bytes.
                              ; 'Hola Mundo!' es el texto que queremos imprimir.
                              ; '0xA' es el valor ASCII para el carácter de nueva línea (Enter).

    len equ $ - msg           ; Define 'len' (longitud de la cadena 'msg').
                              ; '$' representa la posición actual del ensamblador en el código.
                              ; '$ - msg' calcula cuántos bytes hay desde el inicio de 'msg' hasta la posición actual,
                              ; dándonos la longitud exacta del mensaje.

section .text                 ; Sección para el código ejecutable del programa (donde van las instrucciones)
    global _start             ; Declara '_start' como el punto de entrada principal del programa.
                              ; El sistema operativo busca esta etiqueta para saber dónde debe empezar a ejecutar tu código.

_start:                       ; Esta etiqueta marca el inicio de la ejecución de nuestro programa

    ; --- Syscall para escribir en la salida estándar (sys_write) ---
    ; Para que nuestro programa imprima algo en la consola, necesitamos pedirle al sistema operativo (kernel)
    ; que lo haga por nosotros, a través de una "llamada al sistema" (syscall).
    ; En Linux para arquitecturas x86-64 (usadas por CPUs Intel y AMD), los argumentos para las syscalls
    ; se pasan en registros específicos:
    ; RAX: Contiene el número de la syscall (qué operación queremos realizar).
    ; RDI: Primer argumento de la syscall.
    ; RSI: Segundo argumento de la syscall.
    ; RDX: Tercer argumento de la syscall.

    mov rax, 1                ; Mueve el valor 1 al registro RAX.
                              ; El número de la syscall para 'write' (escribir datos) es 1.
    mov rdi, 1                ; Mueve el valor 1 al registro RDI.
                              ; El número 1 es el "descriptor de archivo" para la salida estándar (stdout),
                              ; que es tu terminal o consola.
    mov rsi, msg              ; Mueve la dirección de memoria donde se encuentra nuestra cadena 'msg' al registro RSI.
                              ; Esto le dice a 'sys_write' dónde encontrar el texto que queremos imprimir.
    mov rdx, len              ; Mueve la longitud de la cadena 'len' al registro RDX.
                              ; Esto le dice a 'sys_write' cuántos bytes debe escribir desde la dirección dada.
    syscall                   ; ¡Ejecuta la llamada al sistema! El kernel de Linux toma el control por un momento,
                              ; realiza la operación de escritura, y luego devuelve el control a tu programa.

    ; --- Syscall para salir del programa (sys_exit) ---
    ; Una vez que hemos terminado de imprimir nuestro mensaje, es importante indicarle al sistema operativo
    ; que nuestro programa ha finalizado y que puede liberar los recursos que estaba utilizando.

    mov rax, 60               ; Mueve el valor 60 al registro RAX.
                              ; El número de la syscall para 'exit' (terminar el proceso) es 60.
    mov rdi, 0                ; Mueve el valor 0 al registro RDI.
                              ; Este es el "código de salida" del programa. Un valor de 0 generalmente
                              ; indica que el programa terminó con éxito (sin errores).
    syscall                   ; Ejecuta la llamada al sistema 'exit'. El programa se detiene completamente.
    