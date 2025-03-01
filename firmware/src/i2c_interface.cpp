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

        gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
          GPIO_I2C1_SCL | GPIO_I2C1_SDA);

        gpio_set(GPIOB, GPIO_I2C1_SCL | GPIO_I2C1_SDA);

      break;
      
      case I2C2:
        rcc_periph_clock_enable(RCC_I2C2);
        rcc_periph_clock_enable(RCC_GPIOA);

        gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
          GPIO_I2C2_SCL | GPIO_I2C2_SDA);

        gpio_set(GPIOA, GPIO_I2C2_SCL | GPIO_I2C2_SDA);
      break;

      default:
      break;
    }
    
    // Настройка I2C
    i2c_peripheral_disable(i2c_periph_);

    i2c_set_standard_mode(i2c_periph_);
    i2c_set_clock_frequency(i2c_periph_, I2C_CR2_FREQ_36MHZ);
    i2c_set_ccr(i2c_periph_, 180);
    i2c_set_trise(i2c_periph_, 37);

    i2c_peripheral_enable(i2c_periph_);
  }

  /* Запись битов по адресу */
  bool I2C_Interface::write(uint8_t address, uint8_t * data, uint8_t length)
  {
    while (I2C_SR2(i2c_periph_) & I2C_SR2_BUSY);

    i2c_send_start(i2c_periph_);
    while (!(I2C_SR1(i2c_periph_) & I2C_SR1_SB));

    i2c_send_7bit_address(i2c_periph_, address, I2C_WRITE);

    /* Проверяем наличие устройства на шине */
    uint32_t timeout = 100000;
    while (!(I2C_SR1(i2c_periph_) & I2C_SR1_ADDR)) {
      if (--timeout == 0) {
        i2c_send_stop(i2c_periph_);
        return 0;
      }
    }

    (void)I2C_SR2(i2c_periph_);

    for (size_t i = 0; i < length; ++i) {
      i2c_send_data(i2c_periph_, data[i]);
      while (!(I2C_SR1(i2c_periph_) & (I2C_SR1_BTF)));
    }

    return 1;
  }

  /* Чтение битов по адресу */
  bool I2C_Interface::read(uint8_t address, uint8_t * data, uint8_t length)
  {
    i2c_enable_ack(i2c_periph_);

    while (I2C_SR2(i2c_periph_) & I2C_SR2_BUSY);

    i2c_send_start(i2c_periph_);
    while (!(I2C_SR1(i2c_periph_) & I2C_SR1_SB));

    i2c_send_7bit_address(i2c_periph_, address, I2C_WRITE);

    /* Проверяем наличие устройства на шине */
    uint32_t timeout = 100000;
    while (!(I2C_SR1(i2c_periph_) & I2C_SR1_ADDR)) {
      if (--timeout == 0) {
        i2c_send_stop(i2c_periph_);
        return 0;
      }
    }

    (void)I2C_SR2(i2c_periph_);

    for (size_t i = 0; i < length; ++i) {
      if (i == length - 1) i2c_disable_ack(i2c_periph_);

      while (!(I2C_SR1(i2c_periph_) & I2C_SR1_RxNE));
      data[i] = i2c_get_data(i2c_periph_);
    }

    i2c_send_stop(i2c_periph_);

    return 1;
  }

  /* Запись битов в определенный регистр ведомого */
  bool I2C_Interface::write_register(uint8_t address, uint8_t reg, uint8_t * data, uint8_t length)
  {
    uint8_t buffer[length + 1];
    buffer[0] = reg;

    for (uint8_t i = 0; i < length; i++) {
      buffer[i + 1] = data[i];
    }

    return write(address, buffer, length + 1);
  }

  /* Чтение битов из определенного регистра ведомого */
  bool I2C_Interface::read_register(uint8_t address, uint8_t reg, uint8_t * data, uint8_t length)
  {
    /* Запись адреса регистра*/
    if (!write(address, &reg, 1)) return 0;
    /* Чтение из регистра */
    return read(address, data, length);
  }

}