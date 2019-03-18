
# PdM - Solución Ejercicios clase 1 

## Ejercicio 1 [entregable] 
### Objetivo

Practicar la utilización del lenguaje C y el desarrollo de programas en microcontroladores. En particular utilizar las funciones de manejo de GPIO y retardos (Delay).

## Resumen

Desarrollar un programa que controle una secuencia de LEDs mediante los pulsadores de la EDU-CIAA-NXP..

- Utilizar solamente LED azul de los LEDs RGB (llamado LEDB, por Blue). 
- Controlar el sentido de la secuencia con los botones TEC2 y TEC3.
- Cada led permanece encendido 0,5 segundos.
- Una vez que se pasa al siguiente led los demás deberán apagarse.
- Inicialmente la secuencia comienza LEDB -> LED1 -> LED2 -> LED3 -> LEDB ...
- Al presionar TEC3 la secuencia se recorre en sentido inverso, esto es: LED3 -> LED2 -> LED1 -> LEDB -> LED3 ...
- Al presionar TEC2 la secuencia vuelve al orden inicial.

## Solución

```C
/*==================[inclusions]=============================================*/
#include "sapi.h"              // <= sAPI header
#include "stdio.h"
/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){
	/* Inicializar la placa */
	boardConfig();
	delay_t delay;
	/* Inicializar Retardo no bloqueante con tiempo en milisegundos
                    (500ms = 0,5s) */
	delayConfig( &delay, 500 );

	int8_t i = 3;
	uint8_t sequence = 0;

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		if ( !gpioRead( TEC2 ) ){
			sequence = 0;
		}
		if ( !gpioRead( TEC3 ) ){
			sequence = 1;
		}
		if ( delayRead( &delay ) ){
			if ( !sequence ){
				i--;
			}
			else{
				i++;
			}
		}
       	/* ------------- SECUENCIAS ------------- */

		if ( i == 0 ){
			gpioWrite( LEDB, ON );
			gpioWrite( LED1, OFF );
			gpioWrite( LED2, OFF );
			gpioWrite( LED3, OFF );
		}
		if ( i == 1 ){
			gpioWrite( LEDB, OFF );
			gpioWrite( LED1, ON );
			gpioWrite( LED2, OFF );
			gpioWrite( LED3, OFF );
		}
		if ( i == 2 ){
			gpioWrite( LEDB, OFF );
			gpioWrite( LED1, OFF );
			gpioWrite( LED2, ON );
			gpioWrite( LED3, OFF );
		}
		if ( i == 3 ){
			gpioWrite( LEDB, OFF );
			gpioWrite( LED1, OFF );
			gpioWrite( LED2, OFF );
			gpioWrite( LED3, ON );
		}
		if ( i < 0 ){
			i = 3;
		}
		if ( i > 3 ){
			i = 0;
		}
	}

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
	return 0 ;
}

/*==================[FIN DEL ARCHIVO]============================================*/

```