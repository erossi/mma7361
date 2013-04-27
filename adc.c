/* Copyright (C) 2013 Enrico Rossi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file adc.c
 * \brief Analog to digital converter for davids wind direction.
 */

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"

/*! Enable ADC. */
void adc_init(void)
{
	/*! select ADC clock = F_CPU / 128, manual sample. */
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

	/*! Set internal VREF, left adjusted result, adc0 */
	ADMUX = _BV(REFS0) | _BV(ADLAR);
}

/*! \brief Read the ADC value.
 * \note this proc. also re-set the entire ADMUX register.
 */
void adc_read(struct accel_t *accel)
{
	uint8_t i;

	for (i=0; i<3; i++) {
		ADMUX = _BV(REFS0) | _BV(ADLAR) | i;
		/* Start the conversion */
		ADCSRA |= _BV(ADSC);

		/* Wait until the conversion is ended */
		loop_until_bit_is_clear(ADCSRA, ADSC);

		accel->xyz_temp[i] = ADCH;

		if (abs(accel->xyz_temp[i] - accel->xyz[i]) > ALRM_LEVEL) {
			accel->xyz[i] = accel->xyz_temp[i];
			accel->flags |= _BV(CHANGED);
		}
	}
}
