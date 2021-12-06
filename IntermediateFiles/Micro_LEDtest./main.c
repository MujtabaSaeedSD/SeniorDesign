
#define F_CPU 16000000UL


#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
    DDRB |= 1 << PINB7;
	
    while (1) 
    {
		// testing different timings to ensure proper communication between micro controller and code
		PORTB |= 1 <<PINB7;
		_delay_ms(1000);
		PORTB &= ~(1 <<PINB7);
		_delay_ms(1000);
		
		
		PORTB |= 1 <<PINB7;
		_delay_ms(100);
		PORTB &= ~(1 <<PINB7);
		_delay_ms(100);
		
		
		
		PORTB |= 1 <<PINB7;
		_delay_ms(500);
		PORTB &= ~(1 <<PINB7);
		_delay_ms(500);
		
    }
}

