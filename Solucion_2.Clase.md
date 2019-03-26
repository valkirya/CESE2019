
# PdM - Solución Ejercicios clase 2

## Ejercicio 1 [entregable] 
### Objetivo

Practicar la utilización del lenguaje C y el desarrollo de programas en microcontroladores. En particular utilizar la modularización del código en distintos archivos y el uso de bibliotecas.

## Resumen

Desarrollar una biblioteca para controlar los LEDs de la EDU-CIAA-NXP, re-implementar el ejercicio 1 y desarrollar nuevas funcionalidades en base a la biblioteca creada.

## Condiciones de funcionamiento.

Implementar la biblioteca para el manejo de LEDs en dos archivos independientes leds.c y leds.h que contengan la implementación de las funciones y los prototipos de las funciones públicas de la biblioteca, respectivamente.

La biblioteca debe permitir:

1. Hacer parpadear indefinidamente un led cualquiera de la EDU-CIAA-NXP con un período simétrico (ciclo de trabajo 50%) entre 100 y 1000 ms.  Implementar una función con el siguiente prototipo:
void LED_parpadear ( gpioMap_t led, uint16_t periodo ); 

    **NOTA**: El tipo "gpioMap_t" es un enum que está definido en:

    https://github.com/epernia/cese-edu-ciaa-template/blob/master/libs/sapi/sapi_v0.5.2/board/inc/sapi_peripheral_map.h
    
    Todos los tipos de datos definidos sobre un Enum pueden ser usados también como int (en este caso equivalente a int32_t).

2. Hacer parpadear un número de veces específico, "n_veces" entre 1 y 10, un led cualquiera de la EDU-CIAA-NXP con un período simétrico (ciclo de trabajo 50%) entre 100 y 1000 ms.  Implementar una función con el siguiente prototipo:

    ```C
    void LED_parpadear_n_veces ( gpioMap_t led,     uint16_t periodo, uint8_t n_veces );
    ```

3. Mostrar periódica y secuencialmente los leds LEDB, LED1, LED2, LED3 con un período individual de cada led variable entre 100 y 1000 ms.  Implementar una función con el siguiente prototipo:
    
    ```C
    void LED_secuencia_fija( uint16_t periodo );
    ```

4.  Mostrar periódicamente una secuencia arbitraria de 4 leds con un período individual de cada led variable entre 100 y 1000 ms.  
Implementar una función con el siguiente prototipo:

    ```C
    void LED_secuencia_arbitraria( uint16_t periodo, gpioMap_t * psecuencia);
    ```
    **Ayuda**: psecuencia es un puntero a gpio_t que debe apuntarse a un arreglo con la secuencia ordenada de leds.  Por ejemplo:
    ```C
    gpioMap_t secuencia[] = {LED1, LED3, LED1, LED2};
    gpioMap_t* psecuencia = secuencia;
    // equivalente a gpioMap_t* psecuencia = &secuencia[0];
    ```

5. Mostrar periódicamente una secuencia arbitraria de leds, indicando la cantidad de leds mediante un parámetro "n_leds", entre 1 y 10, con un período individual de cada led variable entre 100 y 1000 ms.  
Implementar una función con el siguiente prototipo:

    ```C
    void LED_secuencia_arbitraria( uint16_t periodo, gpioMap_t* psecuencia, uint8_t n_leds);
    ```



## Solución
File: libs_leds.c

```C
/*=====[libs_leds.c]=====================================================
 * Copyright 2019 Iván C. Aranda C. <kmiloarandac@gmail.com>
 * All rights reserved.
 * Licencia: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause
 *
 * Version: 0.0.1
 * Fecha de creacion: 2019/03/24
 */

/*=====[Inclusiones de dependencias de funciones privadas]===================*/

#include "../inc/libs_leds.h"
#include "sapi.h"

/*=====[Implementaciones de funciones publicas]==============================*/

void LED_parpadear ( gpioMap_t led, uint16_t periodo ){
	delay_t delay;
	if (periodo >= 100 && periodo <= 1000){		//Validamos que este periodo este dentro de los umbrales indicados.
		delayConfig( &delay, (periodo*0.5) );	//Ciclo de trabajo 50%.
		gpioWrite(led, ON);						//Encendemos el led
		while (!delayRead(&delay))				//Esperamos a que se cumpla el termine el delay.
			continue;
		gpioWrite(led, OFF);					//Apagamos el led.
		while (!delayRead(&delay))				//Esperamos a que se cumpla el termine el delay.
			continue;
	}
}

void LED_parpadear_n_veces ( gpioMap_t led, uint16_t periodo, uint8_t n_veces ){
	static uint8_t i;
	if (n_veces >= 1 && n_veces <= 10){ //controlamos la entrada de número de veces para que este dentro del rango
	for (i=1;i <= n_veces; i++)
		LED_parpadear ( led, periodo ); //reutilizamos la primera función.
	}
}

void LED_secuencia_fija( uint16_t periodo ){
	static uint8_t j;
	static const char secuencia_leds[4]= { LEDB, LED1, LED2, LED3 }; //Variable estatica, y constante(no puede cambiar su valor en tiempo de ejecucion)
	for ( j=0; j <= 3; j++)
		LED_parpadear ( secuencia_leds[j], periodo ); //reutilizamos la primera función.
}

void LED_secuencia_arbitraria(uint16_t periodo, gpioMap_t* psecuencia) {
	uint8_t i;
	if (psecuencia) {
		for (i = 0; i < 4; i++) {
			LED_parpadear(*psecuencia++, periodo); //reutilizamos la primera función.
		}
	}

}

void LED_secuencia_arbitraria_leds(uint16_t periodo, gpioMap_t* psecuencia,
		uint8_t n_leds) {
	uint8_t i;
	if (n_leds <= 10 && psecuencia) {
		for (i = 0; i < n_leds; i++) {
			LED_parpadear(*psecuencia++, periodo); //reutilizamos la primera función.
		}
	}
}

/*==================[Fin del Codigo]============================================*/
```

File: libs_leds.h
```C
/*=====[libs_leds.h]=====================================================
 * Copyright 2019 Iván C. Aranda C. <kmiloarandac@gmail.com>
 * All rights reserved.
 * Licencia: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause
 *
 * Version: 0.0.0
 * Fecha de creacion: 2019/03/24
 */

/*=====[Evitar inclusion multiple comienzo]==================================*/

#ifndef _MODULE_NAME_H_
#define _MODULE_NAME_H_

/*=====[Inclusiones de dependencias de funciones publicas]===================*/

#include "sapi.h"

/*=====[C++ comienzo]========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Prototipos de funciones publicas]====================================*/

void LED_parpadear ( gpioMap_t led, uint16_t periodo );
void LED_parpadear_n_veces ( gpioMap_t led, uint16_t periodo, uint8_t n_veces );
void LED_secuencia_fija( uint16_t periodo );
void LED_secuencia_arbitraria( uint16_t periodo, gpioMap_t* psecuencia);
void LED_secuencia_arbitraria_leds( uint16_t periodo, gpioMap_t* psecuencia, uint8_t n_leds);

/*=====[C++ fin]=============================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Evitar inclusion multiple fin]=======================================*/

#endif /* _MODULE_NAME_H_ */
```
```C
File: main.c

/*==================[inclusions]=============================================*/
#include "../inc/libs_leds.h"		// <= libs_leds header
#include "sapi.h"					// <= sAPI header

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){
	gpioMap_t arb_1[4] = { LED1, LED2, LED1, LED3 };
	gpioMap_t arb_2[10] = { LED1, LED2, LED3, LED2, LED1, LED2, LED3, LED2,
				LED1, LED2 };


	/* Inicializar la placa */
	boardConfig();

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		//LED_parpadear ( LEDR, 500 );
		//if ( !gpioRead( TEC1 ) )
		//	LED_parpadear_n_veces(LEDG,1000,10);
		//LED_secuencia_fija( 500 );
		//LED_secuencia_arbitraria(500, &arb_1[0]);
		LED_secuencia_arbitraria_leds(250, &arb_2[0], 10);
	}

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
	return 0 ;
}

/*==================[end of file]============================================*/
```





