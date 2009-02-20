#ifndef MOTOR_H_
#define MOTOR_H_

class Motor{
public:
	Motor(){}
	Motor(volatile uint16_t* reg, volatile uint8_t* port, unsigned char pin);
	void setPower(char power);
	void stop();
	char getPower();
	bool reverse;

private:
	volatile uint16_t* REG;
	volatile uint8_t* DIR_PORT;
	unsigned char DIR_PIN;
	char power;
};

extern Motor motor[2];

#endif
