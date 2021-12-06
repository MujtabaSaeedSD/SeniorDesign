#define F_CPU 16000000UL // CPU Frequency

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates Blocking Delay

#define USART_BAUDRATE 9600 // Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

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
char buf[400];
char buf1[80];
char gpgga[]={'$','G','P','G','G','A'};

void USART_Init()
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	UBRR1H = BAUD_PRESCALER >> 8;
	UBRR1L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR1C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
}

uint8_t USART_ReceivePolling()
{
	uint8_t DataByte;
	while (( UCSR1A & (1<<RXC1)) == 0) {}; // Do nothing until data have been received
	DataByte = UDR1 ;
	return DataByte;


}





void USART_TransmitPolling(char DataByte)
{
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
	UDR0 = DataByte;
}

int main()
{

	USART_Init();
	char LocalData;
	
	
	for(int i = 0; i < 400; i++){
		
		LocalData = USART_ReceivePolling();
		buf[i] = LocalData;
		

	}
	for(int i = 0; i < 400; i++){
		if ((buf[i] == gpgga[0]) && (buf[i+1] == gpgga[1])
		&& (buf[i+2] == gpgga[2]) && (buf[i+3] == gpgga[3]) && (buf[i+4] == gpgga[4])){
			for(int j = 0; j < 80; j++){
				buf1[j] = buf[i+j];
				
			}
			
		}
		

	}
	for(int j = 0; j < 79; j++){
		USART_TransmitPolling(buf1[j]);
	}
	return 0;
}