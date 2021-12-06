#define F_CPU 16000000UL // CPU Frequency Definiton


#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Blocking Delay


#define USART_BAUDRATE 115200 // Desired Baud Rate // 115200, B4 9600
#define USART_BAUDRATE_1 9600 // Desired Baud Rate // 115200, B4 9600
#define BAUD_PRESCALER ((((F_CPU / (USART_BAUDRATE * 8UL))) - 1))/2
#define BAUD_PRESCALER_1 (((F_CPU / (USART_BAUDRATE_1 * 16UL))) - 1)
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


char GPS_Full[500];
char GPGGA_Line[76];
char gpgga[] = {'$','G','P','G','G','A'};


char latitude[12];
char longitude[12];


void USART_Init()
{
	
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	UBRR1H = BAUD_PRESCALER_1 >> 8;
	UBRR1L = BAUD_PRESCALER_1;
	
	// Set Frame Format
	UCSR1C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	
}






char USART_ReceivePolling() // keep this
{
	
	char DataByte;
	
	while (( UCSR1A & (1<<RXC1)) == 0) {}; // Do nothing until data have been received
	DataByte = UDR1 ;
	
	return DataByte;

}





void USART_TransmitPolling(char DataByte) // keep this
{
	
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
	UDR0 = DataByte;
	
}



int main()
{

	USART_Init();
	char LocalData;
	
	while(1){
		
	for(int i = 0; i < 500; i++){
		
		LocalData = USART_ReceivePolling();
		GPS_Full[i] = LocalData;
		
	}
	
	
	for(int i = 0; i < 500; i++){
		
		if ((GPS_Full[i] == gpgga[0])
		
		&& (GPS_Full[i+1] == gpgga[1])
		
		&& (GPS_Full[i+2] == gpgga[2])
		
		&& (GPS_Full[i+3] == gpgga[3])
		
		&& (GPS_Full[i+4] == gpgga[4])){
			
			for(int j = 0; j < 76; j++){
				
				GPGGA_Line[j] = GPS_Full[i+j];
			}
			
		}
		
	}
		
	
	char LocalData[] = "AT+SEND=0,11,";
	
	for(int transmitter_count = 0; transmitter_count <= 12; transmitter_count++){
		
		USART_TransmitPolling(LocalData[transmitter_count]);
		
	}
	
	
		
	for(int LAT_count = 17; LAT_count < 27; LAT_count++){
		
		latitude[LAT_count] = GPGGA_Line[LAT_count];
		
		USART_TransmitPolling(latitude[LAT_count]);
		
	}
		
	
	USART_TransmitPolling('\r');
	USART_TransmitPolling('\n');
		
		
	_delay_ms(2000);
	
	
	
	for(int transmitter_count = 0; transmitter_count <= 12; transmitter_count++){
			
		USART_TransmitPolling(LocalData[transmitter_count]);
			
	}
		
		
		
	for(int LONG_count = 30; LONG_count < 40; LONG_count++){
		
		longitude[LONG_count] = GPGGA_Line[LONG_count];
		
		USART_TransmitPolling(longitude[LONG_count]);
		
	}
	


	USART_TransmitPolling('\r');
	USART_TransmitPolling('\n');
		
		
	_delay_ms(1000);
	
	}
	
	
	return 0;
	
}






