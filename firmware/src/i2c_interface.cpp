#include "i2c_interface.hpp"

namespace i2c
{
  void I2C_Interface::init(uint32_t i2c_periph, uint32_t speed)
  {
    i2c_periph_ = i2c_periph;
    speed_ = speed;

    // Включение тактирования переферии
    switch (i2c_periph) {
      case I2C1:
        rcc_periph_clock_enable(RCC_I2C1);
        rcc_periph_clock_enable(RCC_GPIOB);
      break;
      
      case I2C2:
        rcc_periph_clock_enable(RCC_I2C2);
        rcc_periph_clock_enable(RCC_GPIOA);
      break;

      default:
      break;
    }

    // Настройка пинов
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
      GPIO_I2C1_SCL | GPIO_I2C1_SDA);
    
    // Настройка I2C
    i2c_set_standard_mode(I2C1);
    i2c_set_clock_frequency(I2C1, I2C_CR2_FREQ_36MHZ);
    i2c_set_ccr(I2C1, 180);
    i2c_set_trise(I2C1, 37);
    i2c_peripheral_enable(I2C1);
  }

  /* Запись битов по адресу */
  void I2C_Interface::write(uint8_t address, uint8_t * data, uint8_t length)
  {
    i2c_transfer7(i2c_periph_, address, data, length, NULL, 0);
  }

  /* Чтение битов по адресу */
  void I2C_Interface::read(uint8_t address, uint8_t * data, uint8_t length)
  {
    i2c_transfer7(i2c_periph_, address, NULL, 0, data, length);
  }

  /* Запись битов в определенный регистр ведомого */
  void I2C_Interface::write_register(uint8_t address, uint8_t reg, uint8_t * data, uint8_t length)
  {
    uint8_t buffer[length + 1];
    buffer[0] = reg;

    for (uint8_t i = 0; i < length; i++) {
      buffer[i + 1] = data[i];
    }

    i2c_transfer7(i2c_periph_, address, buffer, length + 1, NULL, 0);
  }

  /* Чтение битов из определенного регистра ведомого */
  void I2C_Interface::read_register(uint8_t address, uint8_t reg, uint8_t * data, uint8_t length)
  {
    /* Запись адреса регистра*/
    i2c_transfer7(i2c_periph_, address, &reg, 1, NULL, 0);
    /* Чтение из регистра */
    i2c_transfer7(i2c_periph_, address, NULL, 0, data, length);
  }

}