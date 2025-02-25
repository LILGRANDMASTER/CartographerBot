#include "i2c_interface.hpp"

int main(void)
{
  i2c::I2C_Interface i2c;
  i2c.init(I2C1, 100000);
  
  while (1) {

  }
  return 0;
}