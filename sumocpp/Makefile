PROGNAME=basic
CC=avr-gcc
MMCU=atmega32
OPT= -O2
ARGS=$(OPT) -mmcu=$(MMCU)
HEX=$(PROGNAME).hex

all: $(HEX)

$(HEX): $(PROGNAME).elf
	avr-objcopy -O ihex $^ $@
	
$(PROGNAME).elf: $(PROGNAME).o sumolib/led.o sumolib/sled.o sumolib/switch.o sumolib/ground.o sumolib/distance.o sumolib/servo.o sumolib/motor.o sumolib/usart.o sumolib/wait.o sumolib/random.o
	$(CC) $(ARGS) $^ -o $@	
	
$(PROGNAME).o: $(PROGNAME).c sumoconfig.h
	$(CC) $(ARGS) -c $(PROGNAME).c -o $@

sumolib/sled.o: sumolib/sled.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/sled.c -o $@
	
sumolib/switch.o: sumolib/switch.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/switch.c -o $@	
	
sumolib/ground.o: sumolib/ground.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/ground.c -o $@	
	
sumolib/distance.o: sumolib/distance.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/distance.c -o $@
	
sumolib/servo.o: sumolib/servo.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/servo.c -o $@	
	
sumolib/motor.o: sumolib/motor.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/motor.c -o $@		
	
sumolib/usart.o: sumolib/usart.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/usart.c -o $@	
	
sumolib/wait.o: sumolib/wait.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/wait.c -o $@	
	
sumolib/random.o: sumolib/random.c sumolib/sumolib.h sumoconfig.h
	$(CC) $(ARGS) -c sumolib/random.c -o $@	
	
clean:
	rm -f *.o
	rm -f sumolib/*.o
	rm -f $(PROGNAME).elf
	

	
	
	
	
	
