#ifndef I2C_MOTOR_HPP__
#define I2C_MOTOR_HPP__

#include <cstdint>

namespace motors
{
  class I2C_Motor
  {
    public:
    /* Регистры модуля */
    enum class MotorRegisters : uint8_t{
      REG_FLAGS_0           = 0x00,
      REG_BITS_0            = 0x01,
      REG_FLAGS1            = 0x02,
      REG_BITS1             = 0x03,
      REG_MODEL             = 0x04,
      REG_VERSION           = 0x05,
      REG_ADDRESS           = 0x06,
      REG_CHIP_ID           = 0x07,
      REG_MOT_FREQUENCY_L   = 0x08,
      REG_MOT_FREQUENCY_H   = 0x09,
      REG_MOT_MAX_RPM_DEV   = 0x0A,
      REG_MOT_FLG           = 0x10,
      REG_MOT_MAGNET        = 0x11,
      REG_MOT_REDUCER_L     = 0x12,
      REG_MOT_REDUCER_C     = 0x13,
      REG_MOT_REDUCER_H     = 0x14,
      REG_MOT_SET_PWM_L     = 0x15,
      REG_MOT_SET_PWM_H     = 0x16,
      REG_MOT_SET_RPM_L     = 0x17,
      REG_MOT_SET_RPM_H     = 0x18,
      REG_MOT_GET_RPM_L     = 0x19,
      REG_MOT_GET_RPM_H     = 0x1A,
      REG_MOT_GET_REV_L     = 0x1B,
      REG_MOT_GET_REV_C     = 0x1C,
      REG_MOT_GET_REV_H     = 0x1D,
      REG_MOT_STOP_REV_L    = 0x1E,
      REG_MOT_STOP_REV_C    = 0x1F,
      REG_MOT_STOP_REV_H    = 0x20,
      REG_MOT_STOP_TMR_L    = 0x21,
      REG_MOT_STOP_TMR_C    = 0x22,
      REG_MOT_STOP_TMR_H    = 0x23,
      REG_MOT_STOP          = 0x24,
      REG_BITS_2            = 0x25,
      REG_MOT_VOLTAGE       = 0x26,
      REG_MOT_NOMINAL_RPM_L = 0x27,
      REG_MOT_NOMINAL_RPM_H = 0x28,
    };

    /* Позиции битов и флагов */
    enum : uint8_t {
      MOT_FLG_RPM_EN    = 0x80,
      MOT_FLG_RPM_ERR   = 0x20,
      MOT_FLG_DRV_ERR   = 0x10,
      MOT_FLG_STOP      = 0x02,
      MOT_FLG_NEUTRAL   = 0x01,
      MOT_BIT_STOP      = 0x02,
      MOT_BIT_NEUTRAL   = 0x01,
      MOT_BIT_DIR_CKW   = 0x04,
      MOT_BIT_INV_RDR   = 0x02,
      MOT_BIT_INV_PIN   = 0x01,
    };

  };
}

#endif // I2C_MOTOR_HPP__