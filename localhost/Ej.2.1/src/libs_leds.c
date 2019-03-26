/*=====[libs_leds.c]=====================================================
 * Copyright 2019 Iván C. Aranda C. <kmiloarandac@gmail.com>
 * All rights reserved.
 * Licencia: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause
 *
 * Version: 0.0.0
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
