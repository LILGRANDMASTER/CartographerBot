#ifndef I2C_INTERFACE_HPP__
#define I2C_INTERFACE_HPP__

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/i2c.h>
#include <cstdint>
#include <cstddef>

/*
* I2C_Interface - класс предоставляющий функции для
* приема/передачи данных по интерфейсу I2C
*/
namespace i2c
{
  class I2C_Interface
  {

    public:
    I2C_Interface() {};
    ~I2C_Interface() = default;
    
    // Инициализация нитерфейса i2c_periph
    void init(uint32_t i2c_periph, uint32_t speed=100000);

    // Чтение/запись data по адресу address
    bool write(uint8_t address, uint8_t * data, uint8_t length);
    bool read(uint8_t address, uint8_t * data, uint8_t length);

    // Чтение/запись data из/в регистр reg по адресу address
    bool write_register(uint8_t address, uint8_t reg, uint8_t * data, uint8_t length);
    bool read_register(uint8_t address, uint8_t reg, uint8_t * data, uint8_t length);

    private:
    uint32_t i2c_periph_;
    uint32_t speed_;

  };
}

#endif // I2C_INTERFACE_HPP__