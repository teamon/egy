#ifndef MOTOR_H_
#define MOTOR_H_

class Motor
{
public:
  Motor(){}
  Motor(volatile uint16_t* reg, volatile uint8_t* port, unsigned char pin, unsigned char max);
  void set_power(char power);
  void stop();

private:
  unsigned int max_power;
  volatile uint16_t* REG;
  volatile uint8_t* DIR_PORT;
  unsigned char DIR_PIN;
};

#endif
