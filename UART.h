#ifndef _UART_H
#define _UART_H 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUFFER_SIZE 256

char receive_buffer[BUFFER_SIZE];



class UART{

    private:
        
        
    private:
        void set_baudrate(uint32_t baud);
        void flush_buffer();
        void send_char(char data);
        char receive_char() const;
        

    public:
        uint8_t buffer_position = 0;
        bool endline = false;

    public:
        void init_UART(uint32_t baudrate);
        void send_string(char *data);
        void listen();


};


#endif //_UART_H