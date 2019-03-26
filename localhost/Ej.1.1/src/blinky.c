/*==================[inclusions]=============================================*/
#include "sapi.h"             // <= sAPI header

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

/*==================[end of file]============================================*/
