#include "ADC.h"

ADC::ADC(){

}

void ADC::init(){
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

uint16_t ADC::get_value(){
    this->value = ADCL >> 6;
	this->value |= ADCH << 2;
    
    return value;
}

void ADC::convert(){
    //do an ADC conversion
    ADCSRA |= (1<<ADSC);
}