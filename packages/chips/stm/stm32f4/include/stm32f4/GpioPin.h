//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef STM32F4_GPIO_PIN_H_
#define STM32F4_GPIO_PIN_H_

#if 0
#include "stm32f4xx.h"
#endif

// In the first pass include the entire class definition.
#include "stm32f4/GpioPin_Internal.h"

namespace stm32f4
{
  using GpioPin = TGpioPin<gpio::MEMORY_BASE_ADDRESS, gpio::MEMORY_OFFSET>;
}

namespace stm32f4
{
  // \headerfile Gpio.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Gpio.h"
  /// \ingroup stm32f4_gpio
  /// \nosubgrouping
  ///
  /// \brief GPIO pin class template (static inline version).
  ///
  /// \details
  /// This class template provides full control of a STM32F4 GPIO pin.
  /// It is intended for most common cases when both the port number
  /// and the bit number are constants known at compile time.
  ///
  /// For performance reasons, all member functions are inline and very
  /// simple, performing just the required memory access(es).
  ///
  /// Using it is typical for static classes, although a default
  /// constructor is provided, so you can instantiate it as well.
  ///
  /// \code{.cpp}
  /// template class stm32f4::TGpioPinConst<XPORT, XBIT>;
  /// using XGPIO = class stm32f4::TGpioPin<XPORT, XBIT>;
  ///
  /// XGPIO myGpio;
  /// myGpio.setHigh();
  /// \endcode

  template<const gpio::Port PORT_T, const gpio::PortBit PORT_BIT_T>
    class TGpioPinConst
    {
    private:
      // Validate template constant parameters
      static_assert(PORT_T <= gpio::Port::MAX, "Port number too high");
      static_assert(PORT_BIT_T <= gpio::PortBit::MAX, "Port bit number too high");

      /// \name Private members
      /// @{

      // Define local numeric versions of the template enums parameters.
      /// \brief The port number, as given when instantiating the template.
      static constexpr gpio::portNumber_t m_portNumber =
          static_cast<gpio::portNumber_t>(PORT_T);

      /// \brief The bit number, as given when instantiating the template.
      static constexpr gpio::portBitNumber_t m_portBitNumber =
          static_cast<gpio::portBitNumber_t>(PORT_BIT_T);

      /// \brief The single bit mask, corresponding to the bit number.
      ///
      /// \details
      /// This value is
      /// intentionally 16-bit, to trigger an error if m_bitNumber>16.
      static constexpr gpio::portBitMask_t m_portBitMask = (1u
          << m_portBitNumber);

      /// \brief The address of the port hardware registers.
      ///
      /// \details
      /// This value is computed based on the
      /// peripheral base address, the port number and the port offset.
      /// For convenient access, it is represented as an unsigned.
      static constexpr cortexm::registerAddress_t m_gpioAddress =
          (gpio::MEMORY_BASE_ADDRESS + gpio::MEMORY_OFFSET * (m_portNumber));

      /// @} end of name Private members

    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Construct a GPIO pin object.
      ///
      /// \par Parameters
      ///    None.
      TGpioPinConst() = default;

      /// @} end of name Constructors/destructor

// In the second pass, include only the method definitions, the
// class definitions are skipped using preprocessor tricks.
#include "stm32f4/GpioPin_Internal.h"

      // ----------------------------------------------------------------------
    };
}
#endif // STM32F4_GPIO_PIN_H_
