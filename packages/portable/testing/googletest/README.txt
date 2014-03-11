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

