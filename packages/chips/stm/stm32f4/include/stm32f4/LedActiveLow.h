//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef STM32F4_LED_ACTIVE_LOW_H_
#define STM32F4_LED_ACTIVE_LOW_H_

// In the first pass include the entire class definition.
#include "stm32f4/LedActiveLow_Internal.h"

namespace stm32f4
{
  using LedActiveLow = TLedActiveLow<stm32f4::GpioPin>;
}

namespace stm32f4
{
  template<typename GpioPin_T>
    class TLedActiveLowConst
    {
    private:
      using GpioPin = GpioPin_T;

      // Normally this object has no members, it is fully static, we use
      // it here as a more flexible method to access the member functions.
      GpioPin m_gpioPin;

    public:
      TLedActiveLowConst() = default;

// In the second pass, include only the method definitions, the
// class definitions are skipped using preprocessor tricks.
#include "stm32f4/LedActiveLow_Internal.h"

      };
    } //
  namespac
  e stm32f4

#endif // STM32F4_LED_ACTIVE_LOW_H_
