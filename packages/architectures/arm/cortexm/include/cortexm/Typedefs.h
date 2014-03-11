//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef CORTEXM_TYPEDEFS_H_
#define CORTEXM_TYPEDEFS_H_

#include <stdint.h>

namespace cortexm
{
  // General definitions, should probably be moved to a higher header
  typedef uint32_t registerAddress_t;
  typedef uint32_t address_t;
  typedef uint32_t registerMask_t;
  typedef uint32_t bitNumber_t; // 0-31
  typedef uint32_t index_t;

  typedef uint32_t reg32_t;
  typedef uint16_t reg16_t;
  typedef uint8_t reg8_t;
} // namespace cortexm

#endif // CORTEXM_TYPEDEFS_H_
