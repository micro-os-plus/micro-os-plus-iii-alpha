//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#include "Semihosting.h"
#include "CallHost.h"

namespace os
{
  namespace arm
  {
    template class TSemihosting<CallHost> ;
    using Semihosting = TSemihosting<CallHost>;
  }
}

// ----------------------------------------------------------------------------

#if !defined(OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE)
#define OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE       80
#endif

#if !defined(OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE)
#define OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE         10
#endif

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

namespace os
{
  namespace arm
  {

    template<typename Semihosting_T, int args_T, int argv_T>
      class TArgs
      {
      private:
        using Host = Semihosting_T;
        static constexpr int ARGS_BUF_ARRAY_SIZE = args_T;
        static constexpr int ARGV_BUF_ARRAY_SIZE = argv_T;

      public:

        static void
        initialise(int* p_argc, char*** p_argv);

        static void
        dump(int argc, char* argv[]);
      };

    template<typename Semihosting_T, int args_T, int argv_T>
      inline
      void
      __attribute__((always_inline))
      TArgs<Semihosting_T, args_T, argv_T>::initialise(int* p_argc,
          char*** p_argv)
      {

        // Array of chars to receive the command line from the host
        static char args_buf[ARGS_BUF_ARRAY_SIZE];

        // Array of pointers to store the final argv pointers (pointing
        // in the above array).
        static char* argv_buf[ARGV_BUF_ARRAY_SIZE];

        int argc = 0;
        bool isInArgument = false;

        semihosting::CommandLineBlock cmdBlock;
        cmdBlock.pCommandLine = args_buf;
        cmdBlock.size = sizeof(args_buf) - 1;

        int ret = Host::getCommandLine(&cmdBlock);
        if (ret == 0)
          {

            // In case the host send more than we can chew, limit the
            // string to our buffer.
            args_buf[ARGS_BUF_ARRAY_SIZE-1] = '\0';

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
                            >= (int) ((sizeof(argv_buf) / sizeof(argv_buf[0]))
                                - 1))
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

    template<typename Semihosting_T, int args_T, int argv_T>
      inline
      void
      __attribute__((always_inline))
      TArgs<Semihosting_T, args_T, argv_T>::dump(int argc, char* argv[])
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

    // Explicit instantiation
    template
    class TArgs<os::arm::Semihosting,
    OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE,
    OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE> ;

    // Alias
    using Args = class TArgs<os::arm::Semihosting,
    OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE,
    OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE>;
  }
}

// ----------------------------------------------------------------------------

extern "C" void
__os_initialise_args(int* p_argc, char*** p_argv);

void
__os_initialise_args(int* p_argc, char*** p_argv)
{
  return os::arm::Args::initialise(p_argc, p_argv);
}

// ----------------------------------------------------------------------------

extern "C" void
os_dump_args(int argc, char* argv[]);

void
os_dump_args(int argc, char* argv[])
{
  return os::arm::Args::dump(argc, argv);
}

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
