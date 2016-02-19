#include <avr/io.h>
#include <lcd.h>
#include <util/delay.h>
#include <spi.h>

int main()
{
	uint8_t data=0;
	_delay_ms(50);
	
	spi_init();
	
	while(1)
	{
		ENABLE_CHIP();		
		spi_transmit(data++);
		DISABLE_CHIP();
		_delay_ms(1000);
	}
}
