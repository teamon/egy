#ifndef MOTOR_H_
#define MOTOR_H_

class Motor
{
public:
  Motor(){}
  Motor(volatile uint16_t* reg, volatile uint8_t* port, unsigned char pin);
  void set_power(char power);
  void stop();

private:
  volatile uint16_t* REG;
  volatile uint8_t* DIR_PORT;
  unsigned char DIR_PIN;
};

extern Motor motor_left;
extern Motor motor_right;

#endif
