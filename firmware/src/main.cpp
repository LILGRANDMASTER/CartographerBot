#include "clock_config.hpp"
#include "i2c_interface.hpp"
#include "i2c_motor.hpp"

int main(void)
{
  if (clock::f103_clock_config()) return 1;

  /* Инициализация I2C */
  i2c::I2C_Interface i2c1;
  i2c1.init(I2C1_BASE, 100000);

  motors::I2C_Motor motor(i2c1, 0x0C);
  motor.set_speed_rpm(500);

  while (1) {

  }
  
  return 0;
}