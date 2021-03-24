# boost_regex

This example is from the boost documentation and the main purpose was to establish
the basics of creating an application using a boost binary library.


# source

The source code consists on only the main function which creates a boost regex expression
pattern and searches for the pattern in content provided on stdin.


# build

A Makefile is provided to build the application and provides an example of using make
to build c++ applications with external libraries.


# libraries

The application relies on the boost regex library which is loaded dynamically. It is
assumed that the boost libraries are not globally installed on the host system and a
BASH script, *main.sh* provides a method of defining the location of the boost libraries
and then executing the main binary.
