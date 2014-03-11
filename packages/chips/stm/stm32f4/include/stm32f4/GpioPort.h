//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef STM32F4_GPIO_PORT_H_
#define STM32F4_GPIO_PORT_H_

#include "cortexm/Typedefs.h"
#include "stm32f4/MemoryMap.h"
#include "cortexm/RegisterAccess.h"

namespace stm32f4
{
  namespace gpio
  {
    // GPIO port specific definitions
    typedef uint32_t portNumber_t;
    typedef cortexm::index_t index_t;

    typedef cortexm::reg16_t reg16_t;
    typedef cortexm::reg32_t reg32_t;

    // ------------------------------------------------------------------------

    // Port definitions
    enum class Port
      : portNumber_t
        {
          A = 0u, //
      B,
      C,
      D,
      E,
      F,
      G,
      H,
      I,
      MAX = I
    };

    // ------------------------------------------------------------------------

    /// \brief Base address of the device.
    constexpr cortexm::registerAddress_t MEMORY_BASE_ADDRESS =
        MemoryMap::GPIOA_BASE_ADDRESS;
    constexpr cortexm::registerAddress_t MEMORY_OFFSET = MemoryMap::GPIO_OFFSET;

    // Port registers offsets.
    constexpr cortexm::registerAddress_t MODER_OFFSET = 0x0000U;
    constexpr cortexm::registerAddress_t OTYPER_OFFSET = 0x0004U;
    constexpr cortexm::registerAddress_t OSPEEDR_OFFSET = 0x0008U;
    constexpr cortexm::registerAddress_t PUPDR_OFFSET = 0x000CU;
    constexpr cortexm::registerAddress_t IDR_OFFSET = 0x0010U;
    constexpr cortexm::registerAddress_t ODR_OFFSET = 0x0014U;

    constexpr cortexm::registerAddress_t BSRR_OFFSET = 0x0018U;
    constexpr cortexm::registerAddress_t BSRRL_OFFSET = 0x0018U; // little endian
    constexpr cortexm::registerAddress_t BSRRH_OFFSET = 0x001AU;

    constexpr cortexm::registerAddress_t LCKR_OFFSET = 0x001CU;

    constexpr cortexm::registerAddress_t AFR_OFFSET = 0x0020U;
    constexpr cortexm::registerAddress_t AFR_0_OFFSET = 0x0020U;
    constexpr cortexm::registerAddress_t AFR_1_OFFSET = 0x0024U;

    // Port registers definitions.
    extern cortexm::TReadWrite<uint32_t, MODER_OFFSET> modeRegister;
    extern cortexm::TReadWrite<uint32_t, OTYPER_OFFSET> outputTypeRegister;
    extern cortexm::TReadWrite<uint32_t, OSPEEDR_OFFSET> outputSpeedRegister;
    extern cortexm::TReadWrite<uint32_t, PUPDR_OFFSET> pullUpPullDownRegister;
    extern cortexm::TReadOnly<uint32_t, IDR_OFFSET> inputDataRegister;
    extern cortexm::TReadWrite<uint32_t, ODR_OFFSET> outputDataRegister;
    extern cortexm::TReadWrite<uint16_t, BSRRL_OFFSET> bitSetRegister;
    extern cortexm::TReadWrite<uint16_t, BSRRH_OFFSET> bitResetRegister;
    extern cortexm::TReadOnly<uint32_t, LCKR_OFFSET> lockCheckRegister;
    extern cortexm::TReadWriteArray<uint32_t, AFR_OFFSET, 2> alternateFunctionRegister;

  // --------------------------------------------------------------------------

  }// namespace gpio
} // namespace stm32f4

#endif // STM32F4_GPIO_PORT_H_
