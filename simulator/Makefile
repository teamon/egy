
all: main

main: lib/ClientSocket.o lib/debug.o lib/dist.o lib/ground.o lib/led.o lib/motor.o lib/queue.o lib/servo.o lib/simulator.o lib/Socket.o lib/switch.o lib/usart.o lib/wait.o main.o
	g++ -o main lib/ClientSocket.o lib/debug.o lib/dist.o lib/ground.o lib/led.o lib/motor.o lib/queue.o lib/servo.o lib/simulator.o lib/Socket.o lib/switch.o lib/usart.o lib/wait.o main.o
	
lib/ClientSocket: lib/ClientSocket.cpp
lib/debug: lib/debug.cpp
lib/dist: lib/dist.cpp
lib/ground: lib/ground.cpp
lib/led: lib/led.cpp
lib/motor: lib/motor.cpp
lib/queue: lib/queue.cpp
lib/servo: lib/servo.cpp
lib/simulator: lib/simulator.cpp
lib/Socket: lib/Socket.cpp
lib/switch: lib/switch.cpp
lib/usart: lib/usart.cpp
lib/wait: lib/wait.cpp
	
clean:
	rm -f *.o

