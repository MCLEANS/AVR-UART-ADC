#ifndef _ADC_H
#define _ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

class ADC{
    private:
    private:
    public:
        uint16_t value;
    public:
        ADC();
        void init();
        uint16_t get_value();
        void convert();
};



#endif //_ADC_H