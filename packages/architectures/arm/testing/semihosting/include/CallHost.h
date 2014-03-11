/*
 * callHost.h
 *
 *  Created on: Feb 18, 2014
 *      Author: ilg
 */

#ifndef CALLHOST_H_
#define CALLHOST_H_

#include "Semihosting.h"
#include "arm.h"

/* Now the SWI numbers and reason codes for RDI (Angel) monitors.  */
#define AngelSWI_ARM                    0x123456
#ifdef __thumb__
#define AngelSWI                        0xAB
#else
#define AngelSWI                        AngelSWI_ARM
#endif
/* For thumb only architectures use the BKPT instruction instead of SWI.  */
#ifdef THUMB_V7M_V6M
#define AngelSWIInsn                    "bkpt"
#define AngelSWIAsm                     bkpt
#else
#define AngelSWIInsn                    "swi"
#define AngelSWIAsm                     swi
#endif

namespace os
{
  namespace arm
  {

    // Functor definition
    class CallHost
    {
    public:
      CallHost() = delete;

      int
      operator()(semihosting::OperationNumber op, void* arg = nullptr);
    };

    inline int
    __attribute__ ((always_inline))
    CallHost::operator()(semihosting::OperationNumber op, void* arg)
    {
      int value;
      asm volatile (

          " mov r0, %1  \n"
          " mov r1, %2  \n"
          " " AngelSWIInsn " %a3 \n"
          " mov %0, r0"

          : "=r" (value) /* Outputs */
          : "r" (op), "r" (arg), "i" (AngelSWI) /* Inputs */
          : "r0", "r1", "r2", "r3", "ip", "lr", "memory", "cc"
          /* Clobbers r0 and r1, and lr if in supervisor mode */
      );

      /* Accordingly to page 13-77 of ARM DUI 0040D other registers
       can also be clobbered.  Some memory positions may also be
       changed by a system call, so they should not be kept in
       registers. Note: we are assuming the manual is right and
       Angel is respecting the APCS.  */
      return value;
    }

  }
}

#endif /* CALLHOST_H_ */
