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