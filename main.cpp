#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#include "UART.h"

//create UART object
UART uart;

char querry[] = "AT";
char response[] = "OK\n";



ISR (USART0_RX_vect){
	uart.receive_buffer[uart.buffer_position] = uart.receive_char();

	if(uart.receive_buffer[uart.buffer_position] == '\n') {
	uart.is_endline = true;
    }
    
    uart.buffer_position++;
	
    if(uart.buffer_position > BUFFER_SIZE) uart.buffer_position = 0;
}


void listen(){
	if(uart.is_endline){
        if(strncmp(uart.receive_buffer,querry,(sizeof(querry)/sizeof(char))) == 0){
		uart.send_string(response);
		uart.flush_buffer();
		}

		else{
			uart.flush_buffer();
		}

		uart.is_endline = false;
	}

	

}

int main(void)
{
	uart.init(9600);
	
    
    while (1) 
    {
		listen();
    }
}