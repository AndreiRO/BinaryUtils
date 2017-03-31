Binary files utils programs
===========================

BinaryDump (bd) is a program that takes
arguments in the form of printf and outputs
them in a binary file.

BinaryLoad (bl) is a program that takes
arguments in the form of printf and reads
the varables with the given modifiers from
a binary files ad outputs them n text mode to
stdout.

Modifiers:
* %d -> an integer
* %c ->  a character
* %h ->  a short (16bit)
* %f -> a float
* %s ->  a string
* %b -> a boolean value(in the form true/false)
* %lf -> double
* %ld -> long
* %Lf -> long double
* %Ld -> long long

The string written also contains '\0'.
Thu, whea reading, the size doesn't have
to be known.

Tutorial
========

###First compile them.

`andrei@pc-$: make
andrei@pc-$: make install` to instal them
to /usr/local/bin

### BinaryDump

`bd -f test.bin %s some_string %d 123 %f 3.14156 %b true %b false`

Where some_string musn't contain spaces. If it does contain,
escape it using "some_string".

### BinaryLoad

`bl [-l]  -f test.bin -s ' ' %s %d %f %b %b`

Where some_string musn't contain spaces. If it does contain,
escape it using "some_string". Noice, if the separator is '\t' or
'\n', it's special meaning isn't used.


##Notice
If -f isn't given, stdout/stdin is used instead.
-l is for loop mode. That means that it will read
data in that format untill the end of the file is reached.

Further work
============

Implement mode for:
	* short
	* signed/unsigned
	* precision handling

LICENSE
=======

Use it however you like, modify it in any way.
If you improved it make a PR.
