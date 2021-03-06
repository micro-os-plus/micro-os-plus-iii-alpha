This project generates a static library containing the Google C++ Testing
Framework (gtest and gmock).

It is based on the sources in the gMock repository, which include the
gTest sources via a repository link.

https://code.google.com/p/googletest/
https://code.google.com/p/googlemock/

The initial version is based on
- revision 677 of gTest
- revision 468 of gMock

Copy
- include/gmock -> include/gmock
- gtest/include/gtest -> include/gtest
- src -> gmock/src
- gtest/src -> gtest/src

Define includes
- include
- gtest

Define sources
- gtest
- gmock

Exclude from build
- gtest/src/gtest-all.cc
- gtest/src/gtes-all.cc
- gmock/src/gmock-all.cc

===============================================================================

To build the libraries with OS X clang, generally use the default options:

clang++ -I../include -I../gtest -O3 -fsigned-char -emit-llvm -std=c++11 -g3 -Wall -c -fmessage-length=0 -m64

To build the libraries with arm-none-eabi, use:

arm-none-eabi-g++ -march=armv7e-m -mthumb -mfloat-abi=soft -Os \
-fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall \
-Wextra -g -I../include -I../gtest -std=gnu++11 -fno-exceptions -fno-rtti 

Other considered option, but finally not used, since they break the build:
-DGTEST_LANG_CXX11=1 
-DGTEST_HAS_POSIX_RE=0 
-DGTEST_HAS_PTHREAD=0 
-DGTEST_HAS_TR1_TUPLE=0

===============================================================================

For ARM Cortex-M, there are currently two configurations:

- armv7m_Library for Cortex-M3
- armv7em_soft_Library for Cortex-M4 with soft FP

Test projects should add 
- a reference to '3rd-party_googletest'
- new include path '3rd-party_googletest/include'

===============================================================================

Sample tests:


===============================================================================

To create a new Eclipse test project (STM32F4):

- create new C++ Project
	enter name
	select Executable -> STM32F4xx C/C++ Project
	Content: Empty
	Use system calls: Semihosting
	Trace: ARM ITM (semihosting might be used as well)
	...

- assign device (STM32F407)
- build
- create a debug configuration and test

- add a reference to 3rd-party_googletest
- add /3rd-party_googletest/include to includes
- exclude main.cpp (ResourceConfigurations -> Exclude from build)
- build 
- test

SEGGER J-Link GDB Server V4.90c - Terminal output channel

Running main(1, [""]) from gmock_main.cc.
Compiled with 4.8.4 20140725 (release) [ARM/embedded-4_8-branch revision 213147].

[==========] Running 0 tests from 0 test cases.
[==========] 0 tests from 0 test cases ran. (0 ms total)
[  PASSED  ] 0 tests.

Return 0 (PASS).
Connection closed by the GDB server.      

------------

To create a new Eclipse test project (QEMU):

- create new C++ Project
	enter name
	select Executable -> Hello Workd ARM Cortex-M C/C++ Project
	Use system calls: Semihosting
	Trace: semihosting debug
	...

- assign device (STM32F407)
- use "--specs=nano.specs -u _printf_float"
- build
- create a debug configuration and test

- add a reference to 3rd-party_googletest
- add /3rd-party_googletest/include to includes
- exclude main.cpp & Timer.cpp (ResourceConfigurations -> Exclude from build)
- build 
- test

----

QEMU

-append "0 --gtest_output=xml:t.xml" 
(relative file saved in cwd of QEMU)

J-Link

monitor setargs 0 --gtest_output=xml:t.xml
(relative file saved in cwd of J-Link)


