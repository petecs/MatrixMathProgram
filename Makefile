# ------------------------------------------------------------------------------
#
# FILE NAME:       Makefile2
#
# DESCRIPTION:     Makefile for a C++ program
#
# PURPOSE:         Build a program executable on Linux
#
# COMPILATION:     For use with the GNU toolset
#
# NOTES:           http://www.linuxforu.com/2012/06/gnu-make-in-detail-for-beginners/
#                  http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#                  http://www.cplusplus.com/forum/unices/12499/
#                  http://stackoverflow.com/questions/13745645/makefile-clock-skew-detected
#                  http://superuser.com/questions/112316/what-is-the-shell-command-to-display-contents-of-a-file
#                  http://www.tldp.org/HOWTO/Keyboard-and-Console-HOWTO-4.html
#
# MODIFICATION HISTORY:
#
# Author              Date          Modification(s)
# ----------------    ----------    ---------------
# Peter Akala		  2018-02-02    Version 0001
# Peter Akala		  2018-02-02    Version 0002 - added compiler flags for compatibility with C++11 standard
# Peter Akala		  2018-02-19    Version 0003 - added ability to build files with dependencies
# Peter Akala		  2018-02-24    Version 0004 - changes for Lab4
# Peter Akala		  2018-03-05    Version 0005 - changes for Project 01
# Peter Akala		  2018-03-30    Version 0006 - changes for Project 02
# Peter Akala		  2018-04-18    Version 0007 - changes for Project 03
# ------------------------------------------------------------------------------
# Usage: make
# or
# Usage: make matrix_math
# or
# Usage: make -f Makefile matrix_math

.cpp:
	g++ -o $* $*.cpp Matrix.cpp Matrix_ops.cpp -std=c++11 -Wall -Wextra -pedantic

matrix_math: Matrix.cpp Matrix_ops.cpp
