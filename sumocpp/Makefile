PROGNAME=basic
CC=avr-gcc
MMCU=atmega32
OPT= -O2 -w
ARGS=$(OPT) -mmcu=$(MMCU)
HEX=$(PROGNAME).hex

all: $(HEX)

$(HEX): $(PROGNAME).elf
	avr-objcopy -O ihex $^ $@
	
$(PROGNAME).elf: $(PROGNAME).o sumolib/distance.c sumolib/ground.c sumolib/motor.c sumolib/random.c sumolib/servo.c sumolib/sled.c sumolib/switch.c sumolib/usart.c sumolib/wait.c
	$(CC) $(ARGS) $^ -o $@	
	
$(PROGNAME).o: $(PROGNAME).c
	$(CC) $(ARGS) -c $(PROGNAME).c -o $@
	
sumolib/distance.o: sumolib/distance.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/distance.c -o $@

sumolib/ground.o: sumolib/ground.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/ground.c -o $@

sumolib/motor.o: sumolib/motor.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/motor.c -o $@

sumolib/random.o: sumolib/random.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/random.c -o $@

sumolib/servo.o: sumolib/servo.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/servo.c -o $@

sumolib/sled.o: sumolib/sled.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/sled.c -o $@

sumolib/switch.o: sumolib/switch.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/switch.c -o $@

sumolib/usart.o: sumolib/usart.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/usart.c -o $@

sumolib/wait.o: sumolib/wait.c sumoconfig.h
	$(CC) $(ARGS) -c sumolib/wait.c -o $@
	
clean:
	rm -f *.o
	rm -f sumolib/*.o
	rm -f $(PROGNAME).elf

