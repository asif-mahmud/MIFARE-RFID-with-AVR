/*
 * main.c
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
 
#include <avr/io.h>
#include <util/delay.h>
#include <lcd.h>
#include <utils.h>
#include <spi.h>
#include <mfrc522.h>
#include <motor.h>

#define BLUE 	2
#define WHITE 	3

void gate_action();

int main()
{
	uint8_t byte;
	uint8_t str[MAX_LEN];
	uint8_t person_recognised = 0;
	uint8_t Blue[5]  ={0x3d,0x21,0xe4,0xd3,0x2b};
	uint8_t White[5] ={0x0e,0x65,0xe2,0x13,0x9a};
	
	_delay_ms(50);
	LCDInit(LS_BLINK);
	LCDWriteStringXY(2,0,"RFID Reader");
	LCDWriteStringXY(5,1,VERSION_STR);
	
	
	MOTOR_PORT_INIT();
	spi_init();
	mfrc522_init();
	_delay_ms(1500);
	LCDClear();
	
	//init reader
	
	
	//check version of the reader
	byte = mfrc522_read(VersionReg);
	if(byte == 0x92)
	{
		LCDWriteStringXY(2,0,"MIFARE RC522v2");
		LCDWriteStringXY(4,1,"Detected");
	}else if(byte == 0x91 || byte==0x90)
	{
		LCDWriteStringXY(2,0,"MIFARE RC522v1");
		LCDWriteStringXY(4,1,"Detected");
	}else
	{
		LCDWriteStringXY(0,0,"No reader found");
	}
	
	_delay_ms(1500);
	LCDClear();
	
	while(1){
		LCDClear();
		LCDWriteStringXY(1,0,"Show Your Card");
		byte = mfrc522_request(PICC_REQALL,str);
		
		if(byte == CARD_FOUND)
		{
			byte = mfrc522_get_card_serial(str);
			if(byte == CARD_FOUND)
			{
				person_recognised = 1;
				for(byte=0;byte<5;byte++)
				{
					if(Blue[byte] != str[byte])
						break;
				}
				if(byte == 5)
					person_recognised = BLUE;
				else
				{
					for(byte=0;byte<5;byte++)
					{
						if(White[byte] != str[byte])
							break;
					}
					if(byte == 5)
						person_recognised = WHITE;
				}
				switch(person_recognised)
				{
					case BLUE : 
					{
						LCDClear();
						LCDWriteStringXY(3,0,"Hello Blue");						
						gate_action();
						break;
					}
					case WHITE : 
					{
						LCDClear();
						LCDWriteStringXY(3,0,"Hello White");
						gate_action();
						break;
					}
					default :
					{
						LCDClear();
						LCDWriteStringXY(0,0,"Not Recognised !");
						break;
					}
				}
			}
			else
			{
				LCDClear();
				LCDWriteStringXY(5,0,"Error");
			}
		}
	}
}

void gate_action()
{
	LCDWriteStringXY(0,1,"Opening Gate ...");
	MOTOR_ROTATE_CW();
	_delay_ms(5000);
	MOTOR_OFF();
	_delay_ms(4000);
	LCDWriteStringXY(0,1,"Closing Gate ...");
	MOTOR_ROTATE_CCW();
	_delay_ms(5000);
	MOTOR_OFF();	
}
