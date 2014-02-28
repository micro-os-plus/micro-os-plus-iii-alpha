//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef STM32F4_LED_ACTIVE_HIGH_INTERNAL_H_

namespace stm32f4
{
  template<typename GpioPin_T>
    class TLedActiveHigh
    {
    private:
      using GpioPin = GpioPin_T;

      // Normally this object has no members, it is fully static, we use
      // it here as a more flexible method to access the member functions.
      GpioPin& m_gpioPin;

    public:
      TLedActiveHigh(GpioPin& gpioPin) :
          m_gpioPin(gpioPin)
      {
      }

#endif

      void
      powerUp(void) const
      {
        m_gpioPin.configureMode(gpio::Mode::Output);
        m_gpioPin.configureOutputType(gpio::OutputType::PushPull);
        m_gpioPin.configureOutputSpeed(gpio::OutputSpeed::High_100MHz);
        m_gpioPin.configureResistors(gpio::Resistors::None);

        m_gpioPin.setLow();
      }

      void
      powerDown(void) const
      {
        m_gpioPin.configureMode(gpio::Mode::Input);
      }

      inline void
      __attribute__((always_inline))
      turnOn(void) const
      {
        m_gpioPin.setHigh();
      }

      inline void
      __attribute__((always_inline))
      turnOff(void) const
      {
        m_gpioPin.setLow();
      }

      inline void
      __attribute__((always_inline))
      toggle(void) const
      {
        m_gpioPin.toggle();
      }

      inline bool
      __attribute__((always_inline))
      isOn(void) const
      {
        return m_gpioPin.isHigh();
      }

#ifndef STM32F4_LED_ACTIVE_HIGH_INTERNAL_H_

    };
} // namespace stm32f4

#endif

#ifndef STM32F4_LED_ACTIVE_HIGH_INTERNAL_H_
#define STM32F4_LED_ACTIVE_HIGH_INTERNAL_H_
#endif // STM32F4_LED_ACTIVE_HIGH_INTERNAL_H_
