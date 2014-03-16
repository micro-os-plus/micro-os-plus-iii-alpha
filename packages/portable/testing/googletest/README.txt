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

