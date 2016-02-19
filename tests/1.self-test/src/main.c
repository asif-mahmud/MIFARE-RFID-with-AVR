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

uint8_t SelfTestBuffer[64];
 
int main()
{
	uint8_t byte;
	_delay_ms(50);
	LCDInit(LS_BLINK);
	LCDWriteStringXY(2,0,"RFID Reader");
	LCDWriteStringXY(5,1,VERSION_STR);
	
	
	spi_init();
	_delay_ms(1000);
	LCDClear();
	LCDWriteStringXY(0,0,"FIFO Data : 0x");
	
	mfrc522_reset();
	for(byte = 0 ; byte<25; byte ++)
		mfrc522_write(FIFODataReg,0x00);
	mfrc522_write(CommandReg,Mem_CMD);
	mfrc522_write(AutoTestReg,0x09);
	mfrc522_write(FIFODataReg,0x00);
	mfrc522_write(CommandReg,CalcCRC_CMD);
	_delay_ms(500);
	for(byte = 0; byte<	64; byte++)
	{
		SelfTestBuffer[byte] = mfrc522_read(FIFODataReg);
		LCDHexDumpXY(14,0,SelfTestBuffer[byte]);
		_delay_ms(1500);
	}	
	
	while(1){} 
}
