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
