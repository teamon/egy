PROGNAME=main
CC=avr-g++
MMCU=atmega32
OPT= -O2
ARGS=$(OPT) -mmcu=$(MMCU)
HEX=$(PROGNAME).hex

all: $(HEX)

$(HEX): $(PROGNAME).elf
	avr-objcopy -O ihex $^ $@
	
$(PROGNAME).elf: $(PROGNAME).o lib/dist.cpp lib/ground.cpp lib/led.cpp lib/motor.cpp lib/queue.cpp lib/servo.cpp lib/switch.cpp lib/usart.cpp lib/wait.cpp
	$(CC) $(ARGS) $^ -o $@	
	
$(PROGNAME).o: $(PROGNAME).cpp
	$(CC) $(ARGS) -c $(PROGNAME).cpp -o $@
	
lib/dist.o: lib/dist.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/dist.cpp -o $@

lib/ground.o: lib/ground.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/ground.cpp -o $@

lib/led.o: lib/led.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/led.cpp -o $@

lib/motor.o: lib/motor.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/motor.cpp -o $@

lib/queue.o: lib/queue.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/queue.cpp -o $@

lib/servo.o: lib/servo.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/servo.cpp -o $@

lib/switch.o: lib/switch.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/switch.cpp -o $@

lib/usart.o: lib/usart.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/usart.cpp -o $@

lib/wait.o: lib/wait.cpp lib/sumo.h
	$(CC) $(ARGS) -c lib/wait.cpp -o $@
	
clean:
	rm -f *.o
	rm -f sumolib/*.o
	rm -f $(PROGNAME).elf

