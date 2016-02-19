/*
 * motor.h
 * 
 * Copyright 2013 Shimon <shimon@monistit.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#ifndef MOTOR_H
#define MOTOR_H
 
#include <avr/io.h>
 
#define MOTOR_DDR			DDRC
#define MOTOR_PORT			PORTC
#define MOTOR_PIN_A			PC4
#define MOTOR_PIN_B			PC5
#define MOTOR_PORT_INIT()	(MOTOR_DDR=(1<<MOTOR_PIN_A)|(1<<MOTOR_PIN_B))
#define MOTOR_ROTATE_CW()	(MOTOR_PORT=(1<<MOTOR_PIN_A))
#define MOTOR_ROTATE_CCW()	(MOTOR_PORT=(1<<MOTOR_PIN_B))
#define MOTOR_OFF()			(MOTOR_PORT=0x00)
 
#endif

