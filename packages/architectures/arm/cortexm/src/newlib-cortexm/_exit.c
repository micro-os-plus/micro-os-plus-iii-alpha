//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include "cmsis_device.h"

// Usually main() doesn't return, but if it does, we use the NVIC to restart.
// On Debug we just enter an infinite loop, to be used as landmark when halting
// the debugger.
//
// It can be redefined in the application, if more functionality
// is required.

void
__attribute__((weak))
_exit(int code __attribute__((unused)))
{
#if !defined(DEBUG)
  // TODO: write on trace
  NVIC_SystemReset();
#endif

  // TODO: write on trace
  while (1)
    ;
}

// ----------------------------------------------------------------------------

