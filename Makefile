MCU = atmega2560
TARGET = blinky
PROGRAMMER =  usbasp
PORT = usb

CC = avr-g++
CFLAGS = -Os -D F_CPU=8000000 -mmcu=$(MCU)
LFLAGS = -D F_CPU=8000000 -mmcu=$(MCU) 



hex :
	$(CC) $(CFLAGS) -c $(TARGET).cpp 
	$(CC) $(LFLAGS) -o $(TARGET).elf $(TARGET).o
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex
	avr-size --format=avr --mcu=$(MCU) $(TARGET).elf

flash :
	avrdude -c $(PROGRAMMER) -p m2560 -P $(PORT) -U flash:w:$(TARGET).hex

clean :
	rm *.hex *.o *.elf
	