//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

/// \file
/// \brief ARM semihosting declarations.

#ifndef OS_ARM_SEMIHOSTING_PUBLIC_SEMIHOSTING_H_
#define OS_ARM_SEMIHOSTING_PUBLIC_SEMIHOSTING_H_

#include <unistd.h>
#include <stdint.h>

namespace os
{
  namespace arm
  {
    // ======================================================================

    /// \headerfile Semihosting.h "hal/architecture/arm/cortexm/diagnostics/include/SemiHosting.h"
    /// \ingroup arm
    /// \nosubgrouping
    ///
    /// \brief The standard semihosting interface.
    ///
    /// \details
    /// This class defines
    /// the semihosting interface, as specified in
    ///  ARM Compiler toolchain Version 5.03 - Developing Software for ARM Processors
    ///  DUI 0471I, Chapter 8 - Semihosting
    class Semihosting
    {

    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      Semihosting(void) = delete;

      /// \brief Deleted destructor.
      ~Semihosting(void) = delete;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief SYS_WRITE0 Write a string to the debug channel.
      ///
      /// \param pString         Pointer to null terminated string.
      /// \par Returns
      ///    Nothing.
      static void
      writeString(const char* pString);

      /// \brief SYS_WRITEC Write a character to the debug channel.
      ///
      /// \param ch         Character to write.
      /// \par Returns
      ///    Nothing.
      static void
      writeChar(char ch);

      typedef struct
      {
        char* pCommandLine;
        int size;
      } CommandLineBlock;

      /// \brief SYS_GET_CMDLINE Return the command line.
      ///
      /// \param pBlock         Pointer to a two word data block to
      /// be used for returning the command string and its length:
      /// - word 1 a pointer to a buffer of at least the size
      ///     specified in word two
      /// - word 2 the length of the buffer in bytes.
      /// \retval 0           The call is successful.
      /// \retval -1          The call is not successful.
      static int
      getCommandLine(CommandLineBlock* pBlock);

      static unsigned int
      getTimeCentiseconds(void);

      static unsigned int
      getTimeSeconds(void);

      static unsigned int
      getTickFrequency(void);

      /// @} end of Public member functions

    protected:

      typedef uint32_t operationNumber_t;

      enum class OperationNumber
        : operationNumber_t
          {
            angel_SWIreason_EnterSVC = 0x17,
        angel_SWIreason_ReportException = 0x18,
        SYS_CLOSE = 0x02,
        SYS_CLOCK = 0x10,
        SYS_ELAPSED = 0x30,
        SYS_ERRNO = 0x13,
        SYS_FLEN = 0x0C,
        SYS_GET_CMDLINE = 0x15,
        SYS_HEAPINFO = 0x16,
        SYS_ISERROR = 0x08,
        SYS_ISTTY = 0x09,
        SYS_OPEN = 0x01,
        SYS_READ = 0x06,
        SYS_READC = 0x07,
        SYS_REMOVE = 0x0E,
        SYS_RENAME = 0x0F,
        SYS_SEEK = 0x0A,
        SYS_SYSTEM = 0x12,
        SYS_TICKFREQ = 0x31,
        SYS_TIME = 0x11,
        SYS_TMPNAM = 0x0D,
        SYS_WRITE = 0x05,
        SYS_WRITEC = 0x03,
        SYS_WRITE0 = 0x04,
      };

    protected:
      /// \name Protected member functions
      /// @{

      static int
      callHost(OperationNumber op, void* p1 = nullptr, void* p2 = nullptr);

      /// @} end of Protected member functions

    };

    /// \details
    /// Write a character byte, to the debug channel.
    /// When executed under an ARM
    /// debugger, the character appears on the host debugger console.
    inline void
    __attribute__((always_inline))
    Semihosting::writeChar(char ch)
    {
      // Pass the address of the character
      callHost(OperationNumber::SYS_WRITEC, (void*) &ch);
    }

    /// \details
    /// Write a null-terminated string to the debug channel.
    /// When executed under an ARM debugger,
    /// the characters appear on the host debugger console.
    inline void
    __attribute__((always_inline))
    Semihosting::writeString(const char* pString)
    {
      callHost(OperationNumber::SYS_WRITE0, (void*) pString);
    }

    /// \details
    /// Returns the command line used for the call to the executable,
    /// that is, argc and argv.
    ///
    /// On exit the two-word data block contains
    /// - word 1 a pointer to null-terminated string of the command line
    /// - word 2 the length of the string.
    ///
    /// The debug agent might impose limits on the maximum length of
    /// the string that can be transferred. However, the agent
    /// must be able to transfer a command line of at least 80 bytes.
    inline int
    __attribute__((always_inline))
    Semihosting::getCommandLine(CommandLineBlock* pBlock)
    {
      return callHost(OperationNumber::SYS_GET_CMDLINE, (void*) pBlock);
    }

    inline unsigned int
    __attribute__((always_inline))
    Semihosting::getTimeCentiseconds(void)
    {
      return callHost(OperationNumber::SYS_CLOCK);
    }

    inline unsigned int
    __attribute__((always_inline))
    Semihosting::getTimeSeconds(void)
    {
      return callHost(OperationNumber::SYS_TIME);
    }

    inline unsigned int
    __attribute__((always_inline))
    Semihosting::getTickFrequency(void)
    {
      return callHost(OperationNumber::SYS_TICKFREQ);
    }

  // ========================================================================

  }// namespace arm
} // namespace os

#endif // OS_ARM_SEMIHOSTING_PUBLIC_SEMIHOSTING_H_
