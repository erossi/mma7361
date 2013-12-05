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

#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "adc.h"

int main(void)
{
	char *string;
	struct accel_t *accel;

	PORTC = 0;
	DDRC |= _BV(PC3);

	accel = malloc(sizeof(struct accel_t));
	accel->flags = 0;
	adc_init();

	/* Start the serial port. */
	string = malloc(20);
	uart_init(0);
	uart_printstr(0, "\n\nConnected!\n");

	/* wait 10 seconds */
	_delay_ms(10000);
	/* 1st read to settle the initial values */
	adc_read(accel);
	accel->flags &= ~_BV(CHANGED);

	while (1) {
		adc_read(accel);

		if (accel->flags & _BV(CHANGED)) {
			uart_printstr(0, "x: ");
			string = utoa(accel->xyz[0], string, 10);
			uart_printstr(0, string);
			uart_printstr(0, " y: ");
			string = utoa(accel->xyz[1], string, 10);
			uart_printstr(0, string);
			uart_printstr(0, " z: ");
			string = utoa(accel->xyz[2], string, 10);
			uart_printstr(0, string);
			uart_printstr(0, "\n");
			accel->flags &= ~_BV(CHANGED);
			PORTC |= _BV(PC3);
			_delay_ms(5000);
			PORTC &= ~_BV(PC3);
		}
	}

	return(0);
}
