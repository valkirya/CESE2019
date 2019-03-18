
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
#include "sapi.h"              // <= sAPI header
/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){
	/* Inicializar la placa */
	boardConfig();
	delay_t delay;
	/* Inicializar Retardo no bloqueante con tiempo en milisegundos
                    (500ms = 0,5s) */
	delayConfig( &delay, 500 );

    /* Declaración de variables */
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

/*==================[Fin del Codigo]============================================*/

```
## Ejercicio 1 [Opcional]

### Objetivo

Medir el tiempo de pulsación de un botón y mostrar el tiempo medido encendiendo un LED. 

### Resumen 

El programa espera a que un botón sea pulsado. Mientras el botón está pulsado, se mide el tiempo utilizando un contador hasta que el botón es soltado. En ese momento, se enciende 
el led asociado al botón durante el tiempo calculado. 

### Comentarios 

Para medir el tiempo del botón es posible implementar un bucle iterativo que se extienda mientras el botón está apretado. Dentro de ese bucle, existirá un delay pequeño (por ejemplo, de 1 milisegundo) y por cada iteración se incrementará en 1 el contador. Cuando el bucle finaliza, significa que el botón fue soltado y en el contador tendremos la cantidad de milisegundos que debemos encender el led. 

## Para pensar

Luego de resolver el problema, analice: ¿Qué sucede si mientras estoy pulsando una tecla, comienzo a pulsar otra? ¿Qué sucede si mientras el LED está encendido mostrando el tiempo de una tecla, presiona otra tecla (o la misma)? 

## Solución

```C

#include "sapi.h"              // <= sAPI header

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){
	/* Inicializar la placa */
	boardConfig();

	/* Declaración de variables */
	int32_t sequence = 0;
	uint8_t led = OFF;

/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		while( !gpioRead( TEC1 ) ){
			sequence++;
		}
		if(sequence){
			gpioWrite( LEDB, ON );
            /* Se tiene que calcular los ciclos de la máquina en este caso es de 2040 */
			delay(sequence/2040);
			gpioWrite( LEDB, OFF );
			sequence = 0;
		}
	}
/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	      por ningun S.O. */
	return 0 ;
}
/*==================[Fin del Codigo]============================================*/
```

