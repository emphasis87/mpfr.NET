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

### MSys2/mingw64

	in msys2 terminal:
	pacman -S base-devel mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain lzip

### x32 libmpfr-4.dll using MSys2/mingw64

	cd /c/download/

    tar --lzip -xvf gmp-*.tar.lz

	in msys2/mingw64 terminal:
	in gmp folder:
	./configure --prefix=/c/libs/x32 --enable-shared --disable-static
	make
	make check
	make install

	in mpfr folder:
    ./configure --prefix=/c/libs/x32 --enable-shared --disable-static --enable-thread-safe --with-gmp=/c/libs/x32
	make
	make check
	make install

### x64 libmpfr-4.dll using MSys2/mingw64

	in msys2 terminal:

	cd /c/download/

	in msys2/mingw64 terminal:
	in gmp folder:
	./configure --prefix=/c/libs/x64 --enable-shared --disable-static
	make
	make check
	make install

	in mpfr folder:
    ./configure --prefix=/c/libs/x64 --enable-shared --disable-static --enable-thread-safe --with-gmp=/c/libs/x64
	make
	make check
