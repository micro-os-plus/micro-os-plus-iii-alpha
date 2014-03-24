//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#if defined(TRACE)

#include <stdio.h>
#include <stdarg.h>
#include "diag/Trace.h"
#include "string.h"

// ----------------------------------------------------------------------------

int
trace_printf(const char* format, ...)
{
  int ret;
  va_list ap;

  va_start (ap, format);

  // TODO: optimise even further, to avoid the file descriptor
  ret =  vdprintf(OS_INTEGER_TRACE_FILE_DESCRIPTOR, format, ap);
  va_end (ap);
  return ret;
}

int
trace_puts(const char *s)
{
  trace_write(s, strlen(s));
  return trace_write("\n", 1);
}

int
trace_putchar(int c)
{
  trace_write((const char*)&c, 1);
  return c;
}

void
trace_dump_args(int argc, char* argv[])
{
  trace_printf("main(argc=%d, argv=[", argc);
  for (int i = 0; i < argc; ++i)
    {
      if (i != 0)
        {
          trace_printf(", ");
        }
      trace_printf("\"%s\"", argv[i]);
    }
  trace_printf("]);\n");
}

// ----------------------------------------------------------------------------

#endif // TRACE
