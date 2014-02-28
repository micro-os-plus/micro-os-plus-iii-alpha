//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef STM32F4_LED_ACTIVE_HIGH_H_
#define STM32F4_LED_ACTIVE_HIGH_H_

// In the first pass include the entire class definition.
#include "stm32f4/LedActiveHigh_Internal.h"

namespace stm32f4
{
  using LedActiveHigh = TLedActiveHigh<stm32f4::GpioPin>;
}

namespace stm32f4
{
  template<typename GpioPin_T>
    class TLedActiveHighConst
    {
    private:
      using GpioPin = GpioPin_T;

      // Normally this object has no members, it is fully static, we use
      // it here as a more flexible method to access the member functions.
      GpioPin m_gpioPin;

    public:
      TLedActiveHighConst() = default;

// In the second pass, include only the method definitions, the
// class definitions are skipped using preprocessor tricks.
#include "stm32f4/LedActiveHigh_Internal.h"

      };
    } // na
  mespace stm
  32f4

#en
dif// STM32F4_LED_ACTIVE_HIGH_H_
