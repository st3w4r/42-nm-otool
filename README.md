# NM OTOOL

[![Build Status](https://travis-ci.org/st3w4r/42-nm-otool.svg?branch=master)](https://travis-ci.org/st3w4r/42-nm-otool)

## Project

Re write the programs `nm` and `otool -t`.

Display the symbols of an object file, a binary, an archive and a dynamic library.

The programs can handle the architectures 32 and 64 bits.

## Build

To build the program:

	make

The binaries `ft_nm` and `ft_otool` will be created.

## Test

Some tests are available into the `test/automated` directory.
To run the test you can build this one with `make` and run with `make test`

## NM

To run the program: `ft_nm [options] [file_name ...]`
	
Some options are available for the nm program:

	-g     Display only global (external) symbols.
	-j     Just display the symbol names (no value or type).
	-u     Display only undefined symbols.
	-U     Don't display undefined symbols.
	-x     Display the symbol table entry's fields  in  hexadecimal,  along

## OTOOL

To run the program: `ft_otool [file_name ...]`
