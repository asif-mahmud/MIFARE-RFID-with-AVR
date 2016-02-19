#include <avr/io.h>
#include <lcd.h>
#include <util/delay.h>
#include <spi.h>

int main()
{
	uint8_t data;
	_delay_ms(50);
	LCDInit(LS_BLINK);
	
	
	spi_init();
	ENABLE_CHIP();
	
	while(1)
	{
		if(!(SPI_PIN & (1<<SPI_SS)))
		{
			data = spi_transmit(0);
			LCDHexDumpXY(0,0,data);
		}
	}
}
