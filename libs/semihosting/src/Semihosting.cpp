//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M semihosting definitions.

#include "semihosting/Semihosting.h"

namespace os
{
  namespace arm
  {

    // ======================================================================
    int
    Semihosting::callHost(OperationNumber op, void* p1, void* p2)
    {
#if defined(__thumb__)
      register int r0 asm("r0");
      register int r1 asm("r1") __attribute__((unused));
      register int r2 asm("r2") __attribute__((unused));

      r0 = static_cast<int>(op);
      r1 = (int) p1;
      r2 = (int) p2;

      asm volatile(

          " bkpt 0xAB \n"

          : "=r"(r0)
          :
          :
      );
      return r0;
#else
#error "not implemented"
#endif
    }

  // ========================================================================

  }// namespace arm
} // namespace os

