#define F_CPU 16000000UL // CPU Frequency 

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Blocking Delay



#define USART_BAUDRATE 9600 // Desired Baud Rate // 115200, B4 9600
#define BAUD_PRESCALER ((((F_CPU / (USART_BAUDRATE * 16UL))) - 1))


#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection


#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)

#define PARITY_MODE  DISABLED // USART Parity Bit Selection


#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)

#define STOP_BIT ONE_BIT      // USART Stop Bit Selection


#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)

#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection





void USART_Init()
{
	
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	
}



char USART_ReceivePolling() // keep this
{
	
	
	while (( UCSR0A & (1<<RXC0)) == 0) {}; // Do nothing until data have been received

	
	return UDR0;

}



void USART_TransmitPolling(char DataByte) // keep this
{
	
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready

	UDR0 = DataByte;
	
}



int main(void)
{

    USART_Init();
    char LocalData;
	
    while(1){
    for(int i = 0; i < 30; i++){
	LocalData = USART_ReceivePolling();
	USART_TransmitPolling(LocalData);
		
	}
	
	    
	USART_TransmitPolling('\r');
	USART_TransmitPolling('\n');
	    
	_delay_ms(1000);
	    
	    
	}
	
	return 0;
}





