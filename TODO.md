# TODO

- PosixPluginHandle and WindowsPluginHandle can be combined into a class templated on LibraryHandle. 

- better platform determinations using ${CMAKE_SYSTEM_NAME}
- using --stdlib=libc++ should only be clang on mac. clang on linux, it could cause issues.
- update AddLibrary to conditionally include source code in a src/platforms/ directory based on defined platform. E.g. if(POSIX) then src/platforms/posix/* would be included, if(UNIX) then src/platforms/unix/* would be include. If(WIN32) then src/platforms/win32/* would be include. Everything else should be ignored.

- implement the compiler/interface version checking.
- do windows specializations for plugin loader and plugin handle. 

