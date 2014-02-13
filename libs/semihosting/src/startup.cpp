//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#include "semihosting/Semihosting.h"

// ----------------------------------------------------------------------------

#define OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE       80
#define OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE         10

// ----------------------------------------------------------------------------

// 5.1.2.2.1 Program startup

// The implementation declares no prototype for this function.
// The parameters argc and argv and the strings pointed to by the argv
// array shall be modifiable by the program (no const)
extern "C" int
main(int argc, char* argv[]);

// ----------------------------------------------------------------------------

extern "C" void
initialise_monitor_handles();

extern "C" void
__os_semihosting_initialise_args(int* p_argc, char*** p_argv);

void
__os_semihosting_initialise_args(int* p_argc, char*** p_argv)
{
  // Array of chars to receive the command line from the host
  static char args_buf[OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE];

  // Array of pointers to store the final argv pointers (pointing
  // in the above array).
  static char* argv_buf[OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE];

  int argc = 0;
  bool isInArgument = false;

  os::arm::Semihosting::CommandLineBlock cmdBlock;
  cmdBlock.pCommandLine = args_buf;
  cmdBlock.size = sizeof(args_buf) - 1;

  int ret = os::arm::Semihosting::getCommandLine(&cmdBlock);
  if (ret == 0)
    {
      // The command line is a null terminated string
      char* p = cmdBlock.pCommandLine;

      char delim = '\0';
      char ch;

      while ((ch = *p) != '\0')
        {
          if (!isInArgument)
            {
              if (!isblank(ch))
                {
                  if (argc
                      >= (int) ((sizeof(argv_buf) / sizeof(argv_buf[0])) - 1))
                    break;

                  if (ch == '"' || ch == '\'')
                    {
                      // Remember the delimiter to search for the
                      // corresponding terminator
                      delim = ch;
                      ++p; // skip the delimiter
                      ch = *p;
                    }
                  // Remember the arg beginning address
                  argv_buf[argc++] = p;
                  isInArgument = true;
                }
            }
          else
            {
              if ((ch == delim) || isblank(ch))
                {
                  delim = '\0';
                  *p = '\0';
                  isInArgument = false;
                }
            }
          ++p;
        }
    }

  if (argc == 0)
    {
      // No args found in string, return a single empty name.
      args_buf[0] = '\0';
      argv_buf[0] = &args_buf[0];
      ++argc;
    }

  // Must end the array with a null pointer.
  argv_buf[argc] = nullptr;

  *p_argc = argc;
  *p_argv = &argv_buf[0];

  // temporary here
  initialise_monitor_handles();

  return;
}

#if !defined(__DOXYGEN__)
extern "C" void
__attribute__((alias("__os_semihosting_initialise_args")))
__os_initialise_args(int* p_argc, char*** p_argv);
#endif

// ----------------------------------------------------------------------------

extern "C" void
__os_semihosting_dump_args(int argc, char* argv[]);

void
__os_semihosting_dump_args(int argc, char* argv[])
{
  printf("main(argc=%d, argv=[", argc);
  for (int i = 0; i < argc; ++i)
    {
      if (i != 0)
        {
          printf(", ");
        }
      printf("\"%s\"", argv[i]);
    }
  printf("]);\n");
}

#if !defined(__DOXYGEN__)
extern "C" void
__attribute__((alias("__os_semihosting_dump_args")))
os_dump_args(int argc, char* argv[]);
#endif

// ----------------------------------------------------------------------------

#if 0
// This function is required since the one included in newlib seems buggy
// and the startup files crash when using the semihosting configuration.
// The problem requires further investigations, but in the meantime
// considering that embedded applications rarely return from main,
// it is patched to return -1.

int
__register_exitproc(int type, void (*fn) (void), void *arg, void *d)
  {
    type=type;
    fn=fn;
    arg=arg;
    d=d;
    return -1;
  }

#endif
