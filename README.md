# mpfr.NET
A .NET wrapper for the mpfr C library

### libmpfr-4.dll using MinGW 

It is pretty straightforward to build a C++ CLR consumable .dll of mpfr library.

1) Install MinGW and fetch all required packages for building C/C++ applications

2) From MSys console build mpfr (make)
    Here I encountered a little hiccup, some forking of processes failed, bud
    retry solved it.
    
3) Use MS utility lib to create .lib file for libmpfr-4.dll and .def files.

4) Copy libmpfr-4.dll, libmpfr-4.lib and also mpfr.h, gmp.h (maybe gmpxx.h) to the intended destination.

5) Once having the libmpfr-4.dll and libmpfr-4.lib files link them in C++ CLR project.
    Properties -> Configuration Properties | C/C++ | General | Additional Include Directories - add a directory with .h header files
    Properties -> Configuration Properties | Linker | Input | Additional Dependencies - add a path to the .lib file                                                                                                                                
