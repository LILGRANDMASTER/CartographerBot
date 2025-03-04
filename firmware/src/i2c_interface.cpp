#include "i2c_interface.hpp"

namespace i2c
{
  void I2C_Interface::init(uint32_t i2c_periph, uint32_t speed)
  {
    i2c_periph_ = i2c_periph;
    speed_ = speed;

    switch (i2c_periph_)
    {
      case I2C1_BASE:
        hi2c_.Instance = I2C1;
      break;
      
      case I2C2_BASE:
        hi2c_.Instance = I2C2;
      break;

      default:
        return;
      break;
    }

    hi2c_.Init.ClockSpeed = speed_;
    hi2c_.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c_.Init.OwnAddress1 = 0;
    hi2c_.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c_.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c_.Init.OwnAddress2 = 0;
    hi2c_.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c_.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c_) != HAL_OK) return;
  }

  bool I2C_Interface::write(uint8_t address, uint8_t *data, uint8_t length)
  {
    if (HAL_I2C_Master_Transmit(&hi2c_, address << 1, data, length, HAL_MAX_DELAY) != HAL_OK) {
      return 1; // Ошибка передачи
    }

    return 0;
  }

  bool I2C_Interface::read(uint8_t address, uint8_t *data, uint8_t length)
  {
    if (HAL_I2C_Master_Receive(&hi2c_, address << 1, data, length, HAL_MAX_DELAY) != HAL_OK) {
      return 1; // Ошибка приема
    }

    return 0;
  }

  bool I2C_Interface::write_register(uint8_t address, uint8_t reg, uint8_t *data, uint8_t length)
  {
    if (HAL_I2C_Mem_Write(&hi2c_, address << 1, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY) != HAL_OK) {
      return 1; // Ошибка записи в регистр
    }
    return 0;
  }

  bool I2C_Interface::read_register(uint8_t address, uint8_t reg, uint8_t *data, uint8_t length)
  {
    if (HAL_I2C_Mem_Read(&hi2c_, address << 1, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY) != HAL_OK) {
      return 1; // Ошибка чтения регистра
    }
    return 0;
  }
}