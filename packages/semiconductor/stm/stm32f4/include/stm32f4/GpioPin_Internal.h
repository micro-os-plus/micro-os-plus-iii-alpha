//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef STM32F4_GPIO_PIN_INTERNAL_H_

#include "stm32f4/GpioPort.h"
#include "cortexm/BitBand.h"

namespace stm32f4
{
  namespace gpio
  {
    // ------------------------------------------------------------------------

    // GPIO pin specific definitions
    typedef uint32_t portBitNumber_t;

    // 16 bit!
    typedef uint16_t portBitMask_t;

    using bitValue_t = cortexm::bitband::bitValue_t;

    // ------------------------------------------------------------------------

    // Port bits definitions
    enum class PortBit
      : portBitNumber_t
        {

          _0 = 0u,
      _1,
      _2,
      _3,
      _4,
      _5,
      _6,
      _7,
      _8,
      _9,
      _10,
      _11,
      _12,
      _13,
      _14,
      _15,
      MAX = _15
    };

    // ------------------------------------------------------------------------

    typedef uint32_t mode_t;

    /// \brief Port modes (2 bits/pin).
    enum class Mode
      : mode_t
        {
          Input = 0u, //
      Output = 1u,
      Alternate = 2u,
      Analog = 3u
    };

    /// \brief Mask to isolate the port mode bits.
    constexpr mode_t MODE_MASK = 0x3u;

    // ------------------------------------------------------------------------

    typedef uint32_t outputType_t;

    /// \brief Output type (1 bit/pin).
    enum class OutputType
      : outputType_t
        {
          PushPull = 0u, //
      OpenDrain = 1u
    };

    constexpr outputType_t OUTPUT_TYPE_MASK = 0x1u;

    // ------------------------------------------------------------------------

    typedef uint32_t outputSpeed_t;

    /// \brief Output Speed (2 bits/pin).
    enum class OutputSpeed
      : outputSpeed_t
        {
          Low_2MHz = 0u, //
      Medium_25MHz = 1u,
      Fast_50MHz = 2u,
      High_100MHz = 3u
    };

    /// \brief Mask to isolate the port output speed bits.
    constexpr outputSpeed_t OUTPUT_SPEED_MASK = 0x3u;

    // ------------------------------------------------------------------------

    typedef uint32_t resistors_t;

    /// \brief Pull up/Pull down resistors (2 bits/pin).
    enum class Resistors
      : resistors_t
        {
          None = 0, //
      PullUp = 1,
      PullDown = 2
    };

    /// \brief Mask to isolate the port pull up/pull down bits.
    constexpr resistors_t RESISTORS_MASK = 0x3u;

    // ------------------------------------------------------------------------

    typedef uint32_t alternateFunction_t;

    /// \brief Alternate functions (4 bits/pin).
    enum class AlternateFunction
      : alternateFunction_t
        {
          AF0 = 0, //
      AF1,
      AF2,
      AF3,
      AF4,
      AF5,
      AF6,
      AF7,
      AF8,
      AF9,
      AF10,
      AF11,
      AF12,
      AF13,
      AF14,
      AF15
    };

    /// \brief Mask to isolate the alternate function bits.
    static constexpr alternateFunction_t ALTERNATE_FUNCTION_MASK = 0xFu;

  // ----------------------------------------------------------------------
  }// namespace gpio
} // namespace stm32f4

namespace stm32f4
{
  // ----------------------------------------------------------------------

  template<cortexm::registerAddress_t ADDRESS_T,
      cortexm::registerAddress_t OFFSET_T>
    class TGpioPin
    {
    private:
      static constexpr cortexm::registerAddress_t BASE_ADDRESS = ADDRESS_T;
      static constexpr cortexm::registerAddress_t OFFSET = OFFSET_T;

      /// \name Private members
      /// @{

      // Define local numeric versions of the template enums parameters.
      /// \brief The port number, as given when instantiating the template.
      const gpio::portNumber_t m_portNumber;

      /// \brief The bit number, as given when instantiating the template.
      const gpio::portBitNumber_t m_portBitNumber;

      /// \brief The single bit mask, corresponding to the bit number.
      ///
      /// \details
      /// This value is
      /// intentionally 16-bit, to trigger an error if m_bitNumber>16.
      const gpio::portBitMask_t m_portBitMask;

      /// \brief The address of the port hardware registers.
      ///
      /// \details
      /// This value is computed based on the
      /// peripheral base address, the port number and the port offset.
      /// For convenient access, it is represented as an unsigned.
      const cortexm::registerAddress_t m_gpioAddress;

      /// @} end of name Private members

    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Construct a GPIO pin object.
      ///
      /// \par Parameters
      ///    None.
      inline
      TGpioPin(gpio::Port port, gpio::PortBit portBit) :
          m_portNumber(static_cast<gpio::portNumber_t>(port)), //
          m_portBitNumber(static_cast<gpio::portBitNumber_t>(portBit)), //
          m_portBitMask(1u << m_portBitNumber), //
          m_gpioAddress(BASE_ADDRESS + gpio::MEMORY_OFFSET * (m_portNumber))
      {

      }

      /// @} end of name Constructors/destructor

#endif

      inline gpio::Port
      __attribute__((always_inline))
      getPort(void) const
      {
        return static_cast<gpio::Port>(m_portNumber);
      }

      inline gpio::PortBit
      __attribute__((always_inline))
      getPortBit(void) const
      {
        return static_cast<gpio::PortBit>(m_portBitNumber);
      }

      // ----- Configuration functions ----------------------------------------
      /// \name Configuration functions
      /// @{

      /// \brief Configure the mode bits.
      ///
      /// \param [in] value An enumeration value with the mode.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use read/modify/write to change the 2 configuration bits.
      /// \warning Non atomic, the caller must use critical sections.
      inline void
      //__attribute__((always_inline))
      configureMode(gpio::Mode value) const
      {
#if 0
        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->MODER &=
        ~(gpio::MODE_MASK << (m_portBitNumber * 2));

        gpio::mode_t mode = static_cast<gpio::mode_t>(value) & gpio::MODE_MASK;

        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->MODER |= ((mode)
            << (m_portBitNumber * 2));
#else
        gpio::modeRegister.writeBits(
            m_gpioAddress, //
            gpio::MODE_MASK, static_cast<gpio::mode_t>(value),
            (m_portBitNumber * 2));
#endif
      }

      /// \brief Retrieve the mode bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current pin mode.
      ///
      /// \details
      /// Read the register and return the 2 configuration bits.
      inline gpio::Mode
      //__attribute__((always_inline))
      retrieveMode(void) const
      {
        return static_cast<gpio::Mode>(gpio::modeRegister.readBits(
            m_gpioAddress, //
            gpio::MODE_MASK, (m_portBitNumber * 2)));
      }

      /// \brief Configure the output type bits.
      ///
      /// \param [in] value An enumeration value with the output type.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use bit-banding to write the single configuration bit.
      inline void
      //__attribute__((always_inline))
      configureOutputType(gpio::OutputType value) const
      {
#if 0
        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->OTYPER &=
        ~((gpio::OUTPUT_TYPE_MASK) << (m_portBitNumber));

        gpio::outputType_t outputType = static_cast<gpio::outputType_t>(value)
        & gpio::OUTPUT_TYPE_MASK;

        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->OTYPER |=
        ((outputType) << (m_portBitNumber));
#elif 0
        gpio::outputTypeRegister.writeBits(
            m_gpioAddress, //
            gpio::OUTPUT_TYPE_MASK, (static_cast<gpio::outputType_t>(value)),
            m_portBitNumber);
#else
        gpio::bitValue_t newValue = static_cast<gpio::bitValue_t>(value);

        cortexm::BitBand::writePeripheralBitValue(
            m_gpioAddress + gpio::OTYPER_OFFSET, m_portBitNumber, newValue);
#endif
      }

      /// \brief Retrieve the output type bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current output type.
      inline gpio::OutputType
      //__attribute__((always_inline))
      retrieveOutputType(void) const
      {
#if 0
        return static_cast<gpio::OutputType>(gpio::outputTypeRegister.readBits(
                m_gpioAddress, //
                gpio::OUTPUT_TYPE_MASK, m_portBitNumber));
#else
        return static_cast<gpio::OutputType>(cortexm::BitBand::readPeripheralBitValue(
            m_gpioAddress + gpio::OTYPER_OFFSET, m_portBitNumber));
#endif
      }

      /// \brief Configure the output speed bits.
      ///
      /// \param [in] value An enumeration value with the output speed.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use read/modify/write to change the 2 configuration bits.
      /// \warning Non atomic, the caller must use critical sections.
      inline void
      //__attribute__((always_inline))
      configureOutputSpeed(gpio::OutputSpeed value) const
      {
#if 0
        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->OTYPER &=
        ~((gpio::OUTPUT_SPEED_MASK) << (m_portBitNumber));

        gpio::outputSpeed_t outputSpeed =
        static_cast<gpio::outputSpeed_t>(value) & gpio::OUTPUT_SPEED_MASK;

        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->OTYPER |=
        ((outputSpeed) << (m_portBitNumber * 2));
#else
        gpio::outputSpeedRegister.writeBits(
            m_gpioAddress, //
            gpio::OUTPUT_SPEED_MASK, static_cast<gpio::outputSpeed_t>(value),
            (m_portBitNumber * 2));
#endif
      }

      /// \brief Retrieve the output speed bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current output speed.
      ///
      /// \details
      /// Read the register and return the 2 configuration bits.
      inline gpio::OutputSpeed
      //__attribute__((always_inline))
      retrieveOutputSpeed(void) const
      {
        return static_cast<gpio::OutputSpeed>(gpio::modeRegister.readBits(
            m_gpioAddress, //
            gpio::OUTPUT_SPEED_MASK, (m_portBitNumber * 2)));
      }

      /// \brief Configure the pull-up/pull-down resistor bits.
      ///
      /// \param [in] value An enumeration value with the pull-up/pull-down resistors.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use read/modify/write to change the 2 configuration bits.
      /// \warning Non atomic, the caller must use critical sections.
      inline void
      //__attribute__((always_inline))
      configureResistors(gpio::Resistors value) const
      {
#if 0
        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->PUPDR &=
        ~(gpio::RESISTORS_MASK << (m_portBitNumber * 2));

        gpio::resistors_t resistors = static_cast<gpio::resistors_t>(value)
        & gpio::RESISTORS_MASK;

        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->PUPDR |= ((resistors)
            << (m_portBitNumber * 2));
#else
        gpio::pullUpPullDownRegister.writeBits(
            m_gpioAddress, //
            gpio::RESISTORS_MASK, static_cast<gpio::resistors_t>(value),
            (m_portBitNumber * 2));

#endif
      }

      /// \brief Retrieve the pull-up/pull-down bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current pull-up/pull-down resistors.
      ///
      /// \details
      /// Read the register and return the 2 configuration bits.
      inline gpio::Resistors
      //__attribute__((always_inline))
      retrieveResistors(void) const
      {
        return static_cast<gpio::Resistors>(gpio::pullUpPullDownRegister.readBits(
            m_gpioAddress, //
            gpio::RESISTORS_MASK, //
            (m_portBitNumber * 2)));
      }

      /// \brief Configure the alternate function bits.
      ///
      /// \param [in] value An enumeration value with the alternate function.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use read/modify/write to change the 4 configuration bits.
      /// The AFR registers are organised as an array of two words.
      /// Bits corresponding to pins 0-7 are stored in the first word,
      /// bits corresponding to pins 8-15 in the second word.
      /// \warning Non atomic, the caller must use critical sections.
      inline void
      //__attribute__((always_inline))
      configureAlternateFunction(gpio::AlternateFunction value) const
      {
        gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);

        // All computations are done by the compiler, so divisions
        // are accepted.
        gpio::index_t index = (m_portBitNumber / 8);
        gpio::portBitNumber_t bitNumber = (m_portBitNumber % 8);

#if 0
        gpio::reg32_t current = m_portRegisters.readAlternateFunction(index);
        current &= ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * bitNumber));

        newValue &= gpio::ALTERNATE_FUNCTION_MASK;
        newValue <<= (4 * bitNumber);
        newValue |= current;

        m_portRegisters.writeAlternateFunction(index, newValue);
#else
        gpio::alternateFunctionRegister.writeBits(
            m_gpioAddress, //
            index, gpio::ALTERNATE_FUNCTION_MASK,
            static_cast<gpio::alternateFunction_t>(newValue), (bitNumber * 4));
#endif
      }

      /// \brief Retrieve the alternate function bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current pull-up/pull-down resistors.
      ///
      /// \details
      /// Read the register and return the 4 configuration bits.
      /// The AFR registers are organised as an array of two words.
      /// Bits corresponding to pins 0-7 are stored in the first word,
      /// bits corresponding to pins 8-15 in the second word.
      inline gpio::AlternateFunction
      //__attribute__((always_inline))
      retrieveAlternateFunction(void) const
      {
        // All computations are done by the compiler, so divisions
        // are accepted.
        gpio::index_t const index = (m_portBitNumber / 8);
        gpio::portBitNumber_t const bitNumber = (m_portBitNumber % 8);

#if 0
        gpio::reg32_t current = m_portRegisters.readAlternateFunction(index);
        current >>= (4 * bitNumber);
        current &= gpio::ALTERNATE_FUNCTION_MASK;
#else
#endif
        return static_cast<gpio::AlternateFunction>(gpio::alternateFunctionRegister.readBits(
            m_gpioAddress, //
            index, gpio::ALTERNATE_FUNCTION_MASK, //
            (bitNumber * 4)));
      }

      // TODO: add configure lock

      /// @} end of name Configuration functions

      // ----- Pin member functions -------------------------------------------
      /// \name Pin member functions
      /// @{

      /// \brief Set the pin level to high.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use the lower half of the special BSSR register to set the pin high.
      inline void
      __attribute__((always_inline))
      setHigh(void) const
      {
        // Set a bit in the set register.
#if 0
        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->BSRRL = m_portBitMask;
#else
        gpio::bitSetRegister.write(m_gpioAddress, m_portBitMask);
#endif
      }

      /// \brief Set the pin level to low.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use the upper half of the special BSSR register to set the pin low.
      inline void
      __attribute__((always_inline))
      setLow(void) const
      {
        // Set a bit in the clear register.
#if 0
        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->BSRRH = m_portBitMask;
#else
        gpio::bitResetRegister.write(m_gpioAddress, m_portBitMask);
#endif
      }

      /// \brief Toggle the pin level.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      ///
      /// \details
      /// Use bit-banding to read the corresponding ODR bit,
      /// reverse its value and write it back.
      /// \warning Non atomic, the caller must use critical sections.
      inline void
      __attribute__((always_inline))
      toggle(void) const
      {
#if 0
        (reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->ODR =
        ((reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->IDR
            ^ m_portBitMask);
#else
        gpio::bitValue_t oldValue = cortexm::BitBand::readPeripheralBitValue(
            m_gpioAddress + gpio::ODR_OFFSET, m_portBitNumber);

        gpio::bitValue_t newValue = ~oldValue;
        cortexm::BitBand::writePeripheralBitValue(
            m_gpioAddress + gpio::ODR_OFFSET, m_portBitNumber, newValue);

#endif
      }

      /// \brief Check if the pin level is high.
      ///
      /// \par Parameters
      ///    None.
      /// \return true if the pin level is high.
      ///
      /// \details
      /// Use bit-banding to read the corresponding IDR bit and test it.
      inline bool
      __attribute__((always_inline))
      isHigh(void) const
      {
        // Test if bit in input register is 1.
#if 0
        return (((reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->IDR
                & m_portBitMask) != 0);
#elif 0
        return ((gpio::inputDataRegister.read(m_gpioAddress) & m_portBitMask)
            != 0);
#else
        return (cortexm::BitBand::readPeripheralBitValue(
            m_gpioAddress + gpio::IDR_OFFSET, m_portBitNumber) != 0);
#endif
      }

      /// \brief Check if the pin level is low.
      ///
      /// \par Parameters
      ///    None.
      /// \return true if the pin level is low.
      ///
      /// \details
      /// Use bit-banding to read the corresponding IDR bit and test it.
      inline bool
      __attribute__((always_inline))
      isLow(void) const
      {
        // Test if bit in input register is 0.
#if 0
        return (((reinterpret_cast<GPIO_TypeDef*>(m_gpioAddress))->IDR
                & m_portBitMask) == 0);
#elif 0
        return ((gpio::inputDataRegister.read(m_gpioAddress) & m_portBitMask)
            == 0);
#else
        return (cortexm::BitBand::readPeripheralBitValue(
            m_gpioAddress + gpio::IDR_OFFSET, m_portBitNumber) == 0);
#endif
      }

      /// \brief Read the pin level.
      ///
      /// \par Parameters
      ///    None.
      /// \retval 1 The pin level is high.
      /// \retval 0 The pin level is low.
      ///
      /// \details
      /// Use bit-banding to read the corresponding IDR bit and return it.
      inline gpio::bitValue_t
      __attribute__((always_inline))
      read(void)
      {
        return cortexm::BitBand::readPeripheralBitValue(
            m_gpioAddress + gpio::IDR_OFFSET, m_portBitNumber);
      }

      /// @} end of name Pin member functions

#ifndef STM32F4_GPIO_PIN_INTERNAL_H_
    };
} // namespace stm32f4
#endif

#ifndef STM32F4_GPIO_PIN_INTERNAL_H_
#define STM32F4_GPIO_PIN_INTERNAL_H_
#endif // STM32F4_GPIO_PIN_INTERNAL_H_
