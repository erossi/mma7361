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

/*! \file adc.h */

#ifndef ADC_H_
#define ADC_H_

#define ZERO_G 0
#define G_SELECT 1
#define CHANGED 2

#define ALRM_LEVEL 2

struct accel_t {
	uint8_t xyz[3];
	uint8_t xyz_temp[3];
	uint8_t flags;
};

void adc_init(void);
void adc_read(struct accel_t *accel);

#endif
