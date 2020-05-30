#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#include "UART.h"

//create UART object
UART uart;

char querry[] = "AT";
char response[4];



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
		
        if(strncmp(uart.receive_buffer,querry,(sizeof(querry)/sizeof(char))-1) == 0){
		uart.send_string(response);
		uart.flush_buffer();
		}

		else{
			uart.flush_buffer();
		}

		uart.is_endline = false;
	}

	

}

ISR(ADC_vect){

	uint16_t value;

	value = ADCL >> 6;
	value |= ADCH << 2;

	itoa(value,response,10);

	uart.send_string(response);
	uart.send_string("\n");

	ADCSRA |= (1<<ADSC);


}

void init_ADC(){
	//set ADC prescaler between 5 and 20 for 1MHz clock
	//Here set to 16
	ADCSRA |= (1<<ADPS2);
	//Enable ADC interrupt
	ADCSRA |= (1<<ADIE);
	//set ADC reference voltage
	ADMUX |= (1<<REFS0);
	//set ADC data to left adjusted
	ADMUX |= (1<<ADLAR);
	//Enable ADC
	ADCSRA |= (1<<ADEN);
	//start first ADC conversion
	ADCSRA |= (1<<ADSC);

}

int main(void)
{
	uart.init(9600);
	init_ADC();
	
    
    while (1) 
    {
		listen();
    }
}