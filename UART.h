#ifndef _UART_H
#define _UART_H 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUFFER_SIZE 256


struct ADC_channel_value{
    uint16_t channel_0;
    uint16_t channel_1;
    uint16_t channel_2;
    uint16_t channel_3;
    uint16_t channel_4;
    uint16_t channel_5;
    uint16_t channel_6;
    uint16_t channel_7;
    uint16_t channel_8;
    uint16_t channel_9;
    uint16_t channel_10;
    uint16_t channel_11;
    uint16_t channel_12;
    uint16_t channel_13;
    uint16_t channel_14;
    uint16_t channel_15;
};


class UART{

    private:
        
        
    private:
        void set_baudrate(uint32_t baud);
      
    public:
        uint8_t buffer_position;
        bool is_endline;
        char receive_buffer[BUFFER_SIZE];

    public:
        UART();
        void init(uint32_t baudrate);
        void send_string(char *data);
        void send_char(char data);
        char receive_char() const;
        void flush_buffer();

      


};


#endif //_UART_H