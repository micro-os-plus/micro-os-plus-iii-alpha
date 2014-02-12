//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include <stdio.h>
#include <stddef.h>

#define OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE       100
#define OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE         10

int
__main(void);

// 5.1.2.2.1 Program startup

// The implementation declares no prototype for this function.
// The parameters argc and argv and the strings pointed to by the argv
// array shall be modifiable by the program (no const)
int
main(int argc, char* argv[]);

#if 0

// This should be the default implementation to be used in the startup code

int
__attribute__((weak))
__main(void)
  {
    // By the time we reach here, the data and bss should have been initialised.

    // The strings pointed to by the argv
    // array shall be modifiable by the program, and retain their last-stored
    // values between program startup and program termination.
    static char name[] = "";

    // The string pointed to by
    // argv[0] represents the program name; argv[0][0] shall be the null
    // character if the program name is not available from the host environment.
    // argv[argc] shall be a null pointer.
    static char* argv[2] =
      { name, NULL};

    return main(1, argv);
  }

#else

int
__main(void)
{
  static char args_buf[OS_INTEGER_SEMIHOSTING_CMDARGS_ARRAY_SIZE];
  static char* argv_buf[OS_INTEGER_SEMIHOSTING_ARGVS_ARRAY_SIZE];

  int argc;
  argc = 1;

  // Empty name.
  args_buf[0] = '\0';
  argv_buf[0] = &args_buf[0];

  // Null pointer used as terminator.
  argv_buf[argc] = NULL;

  return main(argc, &argv_buf[0]);
}

#endif

void
dump_args(int argc, char* argv[])
{
  printf("%s, argc=%d, argv=[", argv[0], argc);
  for (int i = 0; i < argc; ++i)
    {
      if (i != 0)
        {
          printf(", ");
        }
      printf("%s", argv[i + 1]);
    }
  printf("]\n");
}
