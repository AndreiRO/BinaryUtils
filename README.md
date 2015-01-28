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
%d -> an integer
%c ->  a character
%f -> a float
%s ->  a string
%b -> a boolean value(in the form true/false)

The string written also contains '\0'.
Thu, whea reading, the size doesn't have
to be known.

Tutorial
========

###First compile them.

`andrei@pc-$: make`
`andrei@pc-$: make install` to instal them
to /usr/local/bin

### BinaryDump

`bd -f test.bin %s some_string %d 123 %f 3.14156 %b true %b false`

Where some_string musn't contain spaces. If it does contain,
escape it using "some_string".

### BinaryLoad

`bl -f test.bin -s ' ' %s %d %f %b %b`

Where some_string musn't contain spaces. If it does contain,
escape it using "some_string". Noice, if the separator is '\t' or
'\n', it's special meaning isn't used.


##Notice
If -f isn't given, stdout/stdin is used instead.

Further work
============

Implement mode for:
	*long
	*double
	*short
	*signed/unsigned
	*precision handling

LICENCE
=======

Use it however you like, modify it in any way.
If you imporved it make a PR.