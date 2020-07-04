#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#include "UART.h"
#include "ADC.h"
#include "commands.h"

//create UART object
UART uart;
//create ADC object
_ADC adc;

char response[4];

ISR (USART0_RX_vect){
	uart.receive_buffer[uart.buffer_position] = uart.receive_char();
	
	if(uart.receive_buffer[uart.buffer_position] == '\n') {
	uart.is_endline = true;
    }
    
    uart.buffer_position++;
	
    if(uart.buffer_position > BUFFER_SIZE) uart.buffer_position = 0;
}



ISR(ADC_vect){
	uint16_t adc_value = adc.get_value();
	itoa(adc_value,response,10);
}




void listen(){
	if(uart.is_endline){
		
		if(strncmp(uart.receive_buffer,FETCH_ADC0,(sizeof(FETCH_ADC0)/sizeof(char))-1) == 0){
			adc.convert();
			_delay_us(500);
			uart.send_string(response);
			uart.send_char(new_line);
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
	adc.init();
	
    
    while (1) 
    {
		listen();
    }
}