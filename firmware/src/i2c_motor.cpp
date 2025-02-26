#include "i2c_motor.hpp"

namespace motors
{
  void I2C_Motor::set_speed_pwm(uint16_t pwm)
  {
    uint8_t data[2] = {0};
    uint8_t reg = static_cast<uint8_t>(Motor_Registers::REG_MOT_SET_PWM_L);

    data[0] = static_cast<uint8_t>(pwm & 0xFF);
    data[1] = static_cast<uint8_t>((pwm >> 8) & 0xFF);
 
    i2c_.write_register(address_, reg, data, 2);
  }

  void I2C_Motor::set_speed_rpm(uint16_t rpm)
  {
    uint8_t data[2] = {0};
    uint8_t reg = static_cast<uint8_t>(Motor_Registers::REG_MOT_SET_RPM_L);

    data[0] = static_cast<uint8_t>(rpm & 0xFF);
    data[1] = static_cast<uint8_t>((rpm >> 8) & 0xFF);
 
    i2c_.write_register(address_, reg, data, 2);
  }

  uint16_t I2C_Motor::get_speed_rpm()
  {
    uint8_t data[2] = {0};
    uint8_t reg = static_cast<uint8_t>(Motor_Registers::REG_MOT_GET_RPM_L);

    i2c_.read_register(address_, reg, data, 2);
    
    return static_cast<uint16_t>((data[1] << 8) | data[0]);
  }

}