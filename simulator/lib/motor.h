#ifndef MOTOR_H_
#define MOTOR_H_

class Motor{
public:
	Motor();
	void setPower(char power);
	void stop();
	char getPower();
	bool reverse;

private:
	char power;
};

extern Motor motor[2];

#endif
