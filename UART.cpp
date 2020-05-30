#include "UART.h"

void UART::set_baudrate(uint32_t baud){
	switch(F_CPU){
		case 1000000UL:
			switch(baud){
				case 9600:
					UBRR0L = 6;
					break;
				case 4800:
					UBRR0L = 12;
					break;
				default:
					break;
				}
		case 8000000UL:
			switch(baud){
				case 115200:
					UBRR0L = 3;
					break;
				case 9600:
					UBRR0L = 51;
					break;
				case 4800:
					UBRR0L = 207;
					break;
				default:
					break;
			}
		
		case 16000000UL:
			switch(baud){
				case 115200:
					 UBRR0L = 8;
					 break;
				case 9600:
					UBRR0L = 103;
					break;
				case 4800:
					UBRR0L = 207;
					break;
				default:
					break;
					
			}
		default:
			break;
			
	}
}

void UART::init_UART(uint32_t baudrate){
	set_baudrate(baudrate);
	//Enable RECEIVER and TRANSMITER
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	//Enable receiver complete Interrupt;
	UCSR0B |= (1<<RXCIE0);
	//set character size to 8 bits
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
	//set Asynchronous mode
	UCSR0C &= ~(1<<UMSEL00);
	UCSR0C &= ~(1<<UMSEL01);
	//enable global Interrupt
	sei();
	
}

void UART::send_char(char data){
	while(!(UCSR0A & (1<<UDRE0))){}
	UDR0 = data;
}

void UART::send_string(char *byte){
	for(;*byte;byte++) send_char(*byte);
}