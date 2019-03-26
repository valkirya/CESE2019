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
