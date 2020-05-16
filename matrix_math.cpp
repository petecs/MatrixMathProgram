/* -----------------------------------------------------------------------------
FILE NAME:         matrix_math.cpp
DESCRIPTION:       Project 3 - Matrix Math Program
USAGE:             ./matrix_math
COMPILER:          GNU g++ compiler on Linux / g++ -std=c++11 -Wall -Wextra -pedantic
NOTES:

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Peter Akala        2018-04-18         1.0 - created matrix_math.cpp, Matrix.h, Matrix.cpp, Matrix_ops.h, & Matrix_ops.cpp files + created outline of program specifications
Peter Akala		   2018-04-28		  2.0 - added exception handling
Peter Akala		   2018-04-29		  3.0 - added test code + debugging
Peter Akala		   2018-04-30		  4.0 - removed test code
Peter Akala		   2018-05-02		  5.0 - added catch-all exception
Peter Akala		   2018-05-03		  6.0 - added ability to test the creation of Matrix objects of any data type
----------------------------------------------------------------------------- */

// matrix data file format
// .mtx file extension
/*
 *  3 x 4
 *  1  2 -3  -2
 *  1  2  3   1
 * -2  7  4 -10
 */

// command-line mode
// ./matrix_math -h - help screen
// ./matrix_math cmd1 cmd2 ...
// -h ~ help menu

// X-inp ~ read in a matrix file and display it to the screen
// X-add ~ addition
// X-sub ~ subtract
// X-mul ~ multiply
// X-eq ~ test for equality
// X-out ~ output file
// X-T ~ transpose the matrix trans()
// X-1 ~ calculate the inverse of a matrix inv()
// X-det ~ calculate the determinant of a matrix det()
// -solve ~ solve a system of equations using Cramer's rule solve()

// X-inp A - read in the A.mtx file and display it to the screen
// X... -out C - write result to name output file (C.mtx)
// X-add A B
// X-sub A B
// X-mul A B
// X-eq A B
// X-T A
// X-1 A
// X-det A
// -solve
// Xerror - too few arguments + invalid dimensions

// Xmatrix.h - Matrix header - class definition
// Xmatrix.cpp - Matrix implementation - constructors, destructors, member functions
// Xtemplate class
// X2-d dynamic array
// Xread data from a file
// Xdisplay the matrix
// Xwrite matrix to file
// Xdefault constructor
// Xoverloaded constructor
// Xcopy constructor
// Xdestructor
// Xoverload <<
// Xoverload >>
// Xoverload =

// Xmatrix_ops - derived class
// Xaddition
// Xsubtraction
// Xmultiplication
// Xoverload ==

// screenshots file
// Xexecutable
// Xsource files
// Xtest script files
// Xmakefile
// XProj3 directory
// Xproj3.tgz file

#include <sstream>
#include <exception>
#include <string>
#include <iostream>
#include "Matrix.h"
#include "Matrix.cpp"
#include "Matrix_ops.h"
#include "Matrix_ops.cpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

// global constants
const char PROGRAMMER_NAME[] = "Peter Akala";

// function prototypes
void DemonstrateTemplateClass();

/* -----------------------------------------------------------------------------
FUNCTION NAME:     main
PURPOSE:           main program function
RETURNS:           0
NOTES:             required function for all c++ programs
// 					int argc - number of parameters on the command line
// 					char* argv[] - an array of pointers to C-strings (an array of char pointers)
----------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
	try
	{
		Matrix<int> masterMatrixParametized(argc, argv);
	}
	catch (const double& ex)
	{
		DemonstrateTemplateClass();
	}
	catch (const string& ex)
	{
		cout << ex;
	}
	catch (const int& ex)
	{
		cout << endl << "An integer exception occurred (int value = " << ex << ")" << endl;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
	catch (...)
	{
		cout << endl << "An unidentified error occurred, contact the programmer" << endl;
	}

	cout << endl;

	// outro
	cout << endl;
	cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
	cout << __DATE__ << "  " __TIME__ << endl;
	cout << endl;

	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     DemonstrateTemplateClass()
PURPOSE:           creates a Matrix object of the string type when a specific matrix is read into the program
RETURNS:           Nothing (void function)
NOTES:             demonstrates that the template class is indeed capable of creating Matrix objects that use any data type
----------------------------------------------------------------------------- */
void DemonstrateTemplateClass()
{
	Matrix<string> masterStringTest;
	std::cout << std::endl << "Template Class Demonstration:" << std::endl;
	std::cout << std::endl << "Successfully initialized a Matrix object of the string type. Strings will be now added to the object to show this." << std::endl;
	std::stringstream ss;
	ss << "1 7 this matrix object uses the string type";
	ss >> masterStringTest;
}