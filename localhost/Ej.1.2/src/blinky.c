/*==================[inclusions]=============================================*/
#include "sapi.h"              // <= sAPI header

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void) {
	/* Inicializar la placa */
	boardConfig();

	/* Declaración de variables */
	int32_t sequence = 0;
	uint8_t led = OFF;

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while (1) {
		while (!gpioRead(TEC1)) {
			sequence++;
		}
		if (sequence) {
			gpioWrite(LEDB, ON);
			delay(sequence / 2040);
			gpioWrite(LEDB, OFF);
			sequence = 0;
		}
	}
	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	 por ningun S.O. */
	return 0;
}
/*==================[end of file]============================================*/
