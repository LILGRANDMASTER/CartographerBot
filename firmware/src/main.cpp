#include "i2c_interface.hpp"
#include "i2c_motor.hpp"
#include <stdio.h>  // Для отладочного вывода

int main(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  i2c::I2C_Interface i2c;
  i2c.init(I2C1, 100000);

  motors::I2C_Motor motor(i2c, 0x0C);
  


  printf("Setting speed to 1000 RPM\n");
  motor.set_speed_rpm(1000);

  while (1) {
      uint16_t speed = motor.get_speed_rpm();
      printf("Current speed: %d RPM\n", speed);
      for (volatile int i = 0; i < 1000000; ++i);  // Задержка
  }
  return 0;
}