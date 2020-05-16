/* -----------------------------------------------------------------------------
FILE NAME:         Matrix.cpp
DESCRIPTION:       implementation file
USAGE:             ./matrix_math
COMPILER:          GNU g++ compiler on Linux / g++ -std=c++11 -Wall -Wextra -pedantic
NOTES:			   Matrix base class

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Peter Akala        2018-04-18         1.0 - created Matrix.cpp file
Peter Akala		   2018-04-28		  2.0 - defined constructors, destructors, and member functions
Peter Akala		   2018-04-29		  3.0 - defined member functions
Peter Akala		   2018-04-30		  4.0 - debugging modifications + added Matrix_ops objects to some member functions
Peter Akala		   2018-05-01		  5.0 - debugging modifications
Peter Akala		   2018-05-02		  6.0 - debugging modifications
Peter Akala		   2018-05-03		  7.0 - implemented help menu + added constructor/destructor test ability + ability to test extraction operator
Peter Akala		   2018-05-03		  8.0 - added ability to test the creation of Matrix objects of any data type
Peter Akala		   2018-05-03		  9.0 - final testing
----------------------------------------------------------------------------- */

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "Matrix.h"
#include "Matrix_ops.h"

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Matrix()
PURPOSE:           create and initialize a Matrix object
RETURNS:           Nothing
NOTES:             default constructor
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix()
{
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Matrix()
PURPOSE:           create and initialize a Matrix object
RETURNS:           Nothing
NOTES:             overloaded constructor
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(const int argc, char** argv)
{
	InputCommandlineArguments(argc, argv);
	ExecuteCommand();
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Matrix()
PURPOSE:           create and initialize a Matrix object by making a deep copy of another Polynomial object
RETURNS:           Nothing
NOTES:             copy constructor
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(const Matrix& right)
{
	CopyAttributes(right);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     ~Matrix()
PURPOSE:           performs shutdown procedures when Matrix object goes out of existence
RETURNS:           Nothing
NOTES:             destructor
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::~Matrix()
{
	if (_isDefaultConstructor)
	{
		std::cout << std::endl << "a Matrix object was created using the default constructor, and has a 2 x 2 matrix with all of the values being '999' and is now being processed by the destructor" << std::endl;
	}

	if (_isDestructObject)
	{
		std::cout << std::endl << "Destructor in base class successfully executed on object with a 1 x 1 matrix with the value 99";
	}

	DestroyMatrix();
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     InputCommandlineArguments()
PURPOSE:           gets the number of commandline arguments and converts the arguments to stl strings
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::InputCommandlineArguments(const int argc, char* argv[])
{
	_argc = argc;

	for (int ix = 0; ix < _argc; ++ix)
	{
		_argv[ix] = std::string(argv[ix]);
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     ValidateArguments()
PURPOSE:           determines whether the command-line arguments are valid and which operation should be performed
RETURNS:           int
NOTES:			   number of commandline parameters is valid for 2, 3, 4, 5, or 6 parameters
----------------------------------------------------------------------------- */
template <class T>
int Matrix<T>::ValidateArguments()
{
	std::string exceptionArgumentNumber = "\nError: invalid number of arguments, run the program with command '-h' to access the help menu\n";
	std::string exceptionArgument = "\nError: invalid arguments, run the program with command '-h' to access the help menu\n";

	if (_argc != 2 && _argc != 3 && _argc != 4 && _argc != 5 && _argc != 6)
	{
		throw exceptionArgumentNumber;
	}

	std::string argumentOne;
	std::string argumentTwo;
	std::string argumentThree;
	std::string argumentFour;
	std::string argumentFive;

	if (_argc >= 2)
	{
		argumentOne = _argv[1];
	}
	if (_argc >= 3)
	{
		argumentTwo = _argv[2];
	}
	if (_argc >= 4)
	{
		argumentThree = _argv[3];
	}
	if (_argc >= 5)
	{
		argumentFour = _argv[4];
	}
	if (_argc >= 6)
	{
		argumentFive = _argv[5];
	}

	// help
	if (_argc == 2 && argumentOne != "-h")
	{
		throw exceptionArgumentNumber;
	}
	else if (_argc == 2)
	{
		return HELP_CMD;
	}

	// read + transpose + inverse + determinant + solve
	if (_argc == 3 && argumentOne != "-inp" && argumentOne != "-T" && argumentOne != "-1" && argumentOne != "-det" && argumentOne != "-solve")
	{
		throw exceptionArgument;
	}
	else if (_argc == 3)
	{
		_filenameOne = argumentTwo;
		_isFilenameOneSet = true;

		if (argumentOne == "-inp") return READ_CMD;
		if (argumentOne == "-T") return TRANSPOSE_CMD;
		if (argumentOne == "-1") return INVERSE_CMD;
		if (argumentOne == "-det") return DETERMINANT_CMD;
		if (argumentOne == "-solve") return SOLVE_CMD;
	}

	// add + sub + mul + equality
	if (_argc == 4 && argumentOne != "-add" && argumentOne != "-sub" && argumentOne != "-mul" && argumentOne != "-eq")
	{
		throw exceptionArgument;
	}
	else if (_argc == 4)
	{
		_filenameOne = argumentTwo;
		_filenameTwo = argumentThree;
		_isFilenameOneSet = true;
		_isFilenameTwoSet = true;

		if (argumentOne == "-add") return ADD_CMD;
		if (argumentOne == "-sub") return SUBTRACT_CMD;
		if (argumentOne == "-mul") return MULTIPLY_CMD;
		if (argumentOne == "-eq") return EQUALITY_CMD;
	}

	// read + transpose + inverse + determinant + solve && output file
	if (_argc == 5 && argumentOne != "-inp" && argumentOne != "-T" && argumentOne != "-1" && argumentOne != "-det" && argumentOne != "-solve" && argumentThree != "-out")
	{
		throw exceptionArgument;
	}
	else if (_argc == 5)
	{
		_filenameOne = argumentTwo;
		_outputFilename = argumentFour;
		_isFilenameOneSet = true;
		_isOutputFileSet = true;

		if (argumentOne == "-inp") return READ_CMD;
		if (argumentOne == "-T") return TRANSPOSE_CMD;
		if (argumentOne == "-1") return INVERSE_CMD;
		if (argumentOne == "-det") return DETERMINANT_CMD;
		if (argumentOne == "-solve") return SOLVE_CMD;
	}

	// add + sub + mul + equality && output file
	if (_argc == 6 && argumentOne != "-add" && argumentOne != "-sub" && argumentOne != "-mul" && argumentOne != "-eq" && argumentFour != "out")
	{
		throw exceptionArgument;
	}
	else if (_argc == 6)
	{
		_filenameOne = argumentTwo;
		_filenameTwo = argumentThree;
		_outputFilename = argumentFive;
		_isFilenameOneSet = true;
		_isFilenameTwoSet = true;
		_isOutputFileSet = true;

		if (argumentOne == "-add") return ADD_CMD;
		if (argumentOne == "-sub") return SUBTRACT_CMD;
		if (argumentOne == "-mul") return MULTIPLY_CMD;
		if (argumentOne == "-eq") return EQUALITY_CMD;
	}

	throw exceptionArgument;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     SetCommand()
PURPOSE:           sets the command that should be performed
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::SetCommand(int command)
{
	_command = command;
}

template <class T>
void Matrix<T>::ExecuteCommand()
{
	Matrix_ops<T> matrixOne;
	Matrix_ops<T> matrixTwo;
	Matrix_ops<T> result;

	int rows;
	int cols;

	int determinant{0};

	SetCommand(ValidateArguments());
	ValidateInputFiles();
	ValidateMatrices(matrixOne, matrixTwo);

	// will test the destructor and extraction operator
	if (_matrix && _matrix[0][0] == DESTRUCTOR_TEST)
	{
		_isDestructObject = true;

		Matrix<T> testObject;

		testObject._isDefaultConstructor = true;

		std::stringstream ss;

		std::string inputStr = "2 2 999 999 999 999";

		std::cout << std::endl << "The string \"2 2 999 999 999 999\" will be inserted into a Matrix object using the extraction operator;" << std::endl;

		ss << inputStr;

		ss >> testObject;
	}

	if (_matrix && _matrix[0][0] == TEMPLATE_TEST)
	{
		double exceptionDouble = 3.0;
		throw exceptionDouble;
	}

	std::string exceptionOperationNotImplemented = "\nError: selected operation has not been implemented (ran out of time...hey, can't win them all)\n";
	std::string exceptionUnknownError = "\nError: unidentified error occurred in ExecuteCommand function, contact programmer\n";

	// number of commandline parameters is valid for 2, 3, 4, 5, or 6 parameters
	switch (_command)
	{
		case 1:
			// display help screen (2 parameters)
			DisplayHelp();
			break;
		case 2:
			// read file and display it to the screen (3+2 parameters)
			result = matrixOne;
			std::cout << std::endl << "Read and Display Matrix:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << result;
			break;
		case 3:
			// add - read and add 2 matrix files and display results (4+2 parameters)
			result = matrixOne + matrixTwo;
			std::cout << std::endl << "Addition:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << matrixOne;
			std::cout << "Matrix " << _filenameTwo << " = " << std::endl << matrixTwo;
			std::cout << "Matrix " << _filenameOne << " + Matrix " << _filenameTwo << " = " << std::endl << result;
			break;
		case 4:
			// subtract - read and subtract 2 matrix files and display results (4+2 parameters)
			result = matrixOne - matrixTwo;
			std::cout << std::endl << "Subtraction:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << matrixOne;
			std::cout << "Matrix " << _filenameTwo << " = " << std::endl << matrixTwo;
			std::cout << "Matrix " << _filenameOne << " - Matrix " << _filenameTwo << " = " << std::endl << result;
			break;
		case 5:
			// multiply - read and multiply 2 matrix files and display results (4+2 parameters)
			result = matrixOne * matrixTwo;
			std::cout << std::endl << "Multiplication:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << matrixOne;
			std::cout << "Matrix " << _filenameTwo << " = " << std::endl << matrixTwo;
			std::cout << "Matrix " << _filenameOne << " x Matrix " << _filenameTwo << " = " << std::endl << result;
			break;
		case 6:
			// equality - read 2 matrix files and test for equality (4+2 parameters)
			result = matrixOne;
			result.SetEquality(matrixOne == matrixTwo);
			std::cout << std::endl << "Equality:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << matrixOne;
			std::cout << "Matrix " << _filenameTwo << " = " << std::endl << matrixTwo;
			std::cout << "Matrix " << _filenameOne << " is equal to Matrix " << _filenameTwo << ": " << std::boolalpha << result.GetEquality();
			break;
		case 7:
			// do the transpose of matrix (3+2 parameters)
			result = matrixOne;
			result.trans();
			std::cout << std::endl << "Transpose:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << matrixOne;
			std::cout << "the transpose of matrix " << _filenameOne << " = " << std::endl << result;
			break;
		case 8:
			// do the inverse of a matrix (3+2 arguments)
			result = matrixOne;
			rows = result._rows;
			cols = result._cols;

			if (rows != cols)
			{
				std::string exceptionMatrixNotSquare = "\nError: non-square matrices cannot be inverted\n";
				throw exceptionMatrixNotSquare;
			}

			std::cout << std::endl << "Inverse:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << matrixOne;
			result.inv();
			break;
		case 9:
			// calculate the determinant of a matrix (3+2 arguments)
			result = matrixOne;
			rows = result._rows;
			cols = result._cols;

			if (rows != cols)
			{
				std::string exceptionMatrixNotSquare = "\nError: non-square matrices do not have determinants\n";
				throw exceptionMatrixNotSquare;
			}

			// create copy of array instead of using this.->_matrix ~ more complicated ~ have to keep track of more stuff
			T** determinantArray;
			determinantArray = new T*[rows];
			for (int ix = 0; ix < rows; ++ix)
			{
				determinantArray[ix] = new T[cols];
			}
			for (int row = 0; row < rows; ++row)
			{
				for (int col = 0; col < cols; ++col)
				{
					determinantArray[row][col] = result._matrix[row][col];
				}
			}

			determinant = result.det(determinantArray, rows);
			//determinant = result.det2(determinantArray, rows);

			std::cout << std::endl << "Determinant:" << std::endl;
			std::cout << "Matrix " << _filenameOne << " = " << std::endl << result;
			std::cout << "the determinant of matrix " << _filenameOne << " = " << determinant;

			// release dynamic array memory
			if (determinantArray != nullptr)
			{
				for (int ix = 0; ix < rows; ++ix)
				{
					delete [] determinantArray[ix];
					determinantArray[ix] = nullptr;
				}
				delete [] determinantArray;
				determinantArray = nullptr;
			}
			break;
		case 10:
			// solve a system of equations using Cramer's Rule
			std::cout << std::endl << "Solve a system of equations using Cramer's Rule:" << std::endl;
			throw exceptionOperationNotImplemented;
			break;
		default:
			// shouldn't be able to get here
			throw exceptionUnknownError;
			break;
	}

	if (_isOutputFileSet)
	{
		WriteToFile(result);
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     OpenInputFile()
PURPOSE:           opens a file for reading
RETURNS:           Nothing (void function)
NOTES:             throws an exception if file does not exist
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::OpenInputFile(std::string filename, std::ifstream& file)
{
	if (file.is_open())
	{
		file.close();
	}

	filename = filename + ".mtx";

	file.open(filename);

	if (!file)
	{
		std::string exceptionStr = "\nError: could not find or open a file named '" + filename + "'\n";
		throw exceptionStr;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     CloseInputFile()
PURPOSE:           closes an input file
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::CloseInputFile(std::ifstream &file)
{
	if (file.is_open())
	{
		file.close();
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     ValidateInputFiles()
PURPOSE:           checks for valid filename and then checks whether file exists
RETURNS:           Nothing (void function)
NOTES:			   throws
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::ValidateInputFiles()
{
	std::ifstream file;

	if (_isFilenameOneSet)
	{
		OpenInputFile(_filenameOne, file);
		CloseInputFile(file);
	}

	if (_isFilenameTwoSet)
	{
		OpenInputFile(_filenameTwo, file);
		CloseInputFile(file);
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     ValidateMatrices()
PURPOSE:           verifies that the matrix data files contain valid data
RETURNS:           Nothing (void function)
NOTES:             ReadDataIntoMatrix will throw an exception if data is invalid
----------------------------------------------------------------------------- */

template <class T>
void Matrix<T>::ValidateMatrices(Matrix_ops<T>& matrixOne, Matrix_ops<T>& matrixTwo)
{
	if (_isFilenameOneSet)
	{
		ReadDataIntoMatrix(_filenameOne);
		matrixOne.CopyAttributes(*this);
	}

	if (_isFilenameTwoSet)
	{
		ReadDataIntoMatrix(_filenameTwo);
		matrixTwo.CopyAttributes(*this);
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     ReadDataIntoMatrix()
PURPOSE:           reads the data from a matrix data file into a matrix object
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::ReadDataIntoMatrix(const std::string filename)
{
	std::string exceptionInvalidDimensions = "\nError: invalid dimensions\n";
	std::ifstream infile;
	OpenInputFile(filename, infile);

	std::string dimensionsStr;
	std::getline(infile, dimensionsStr);

	if (dimensionsStr.empty())
	{
		std::string exceptionEmpty = "\nError: empty file, no data to read\n";
		throw exceptionEmpty;
	}

	std::stringstream dimensionSS;
	dimensionSS << dimensionsStr;

	int rowSize;
	dimensionSS >> rowSize;

	if (!dimensionSS || rowSize <= 0)
	{
		throw exceptionInvalidDimensions;
	}

	std::string buffer;
	dimensionSS >> buffer;

	int colSize;
	dimensionSS >> colSize;

	if (!dimensionSS || colSize <= 0)
	{
		throw exceptionInvalidDimensions;
	}

	DestroyMatrix();

	_matrix = new T*[rowSize];

	for (int row = 0; row < rowSize; ++row)
	{
		_matrix[row] = new T[colSize];
	}

	for (int row = 0; row < rowSize; ++row)
	{
		std::string inputStr;
		std::getline(infile, inputStr);
		std::stringstream inputSS;
		inputSS << inputStr;

		for (int col = 0; col < colSize; ++col)
		{
			inputSS >> _matrix[row][col];

			if (!inputSS)
			{
				std::string exceptionBadData = "\nError: invalid data in file.\n";
				throw exceptionBadData;
			}
		}
	}

	_rows = rowSize;
	_cols = colSize;

	CloseInputFile(infile);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     DisplayMatrix()
PURPOSE:           outputs the matrix to the screen
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::DisplayMatrix() const
{
	if (_matrix == nullptr)
	{
		std::string exceptionMatrixNotSet = "\nError: matrix is not set, cannot display it.\n";
		throw exceptionMatrixNotSet;
	}

	for (int row = 0; row < _rows; ++row)
	{
		std::cout << "|";
		for (int col = 0; col < _cols; ++col)
		{
			std::cout << std::setw(5) << _matrix[row][col] << " ";
		}

		std::cout << "|";
		std::cout << std::endl;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     WriteToFile()
PURPOSE:           outputs the matrix to a file
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::WriteToFile(const Matrix_ops<T>& result)
{
	if (!_isOutputFileSet)
	{
		std::string exceptionOutputNotSet = "\nError: no output file was specified\n";
		throw exceptionOutputNotSet;
	}

	_outputFilename = _outputFilename + ".mtx";

	std::ofstream outfile(_outputFilename);

	if (_command == 6)
	{
		outfile << "Matrix " << _filenameOne << " is equal to Matrix " << _filenameTwo << ": " << std::boolalpha << result.GetEquality();
		return;
	}

	outfile << _rows << " X " << _cols << std::endl;

	WriteMatrixToFile(result, outfile);

	outfile.close();
}

template <class T>
void Matrix<T>::WriteMatrixToFile(const Matrix_ops<T> matrix, std::ofstream& outfile)
{
	for (int row = 0; row < matrix._rows; ++row)
	{
		for (int col = 0; col < matrix._cols; ++col)
		{
			outfile << matrix._matrix[row][col];

			if (col != matrix._cols - 1)
			{
				outfile << " ";
			}
		}

		if (row != matrix._rows - 1)
		{
			outfile << std::endl;
		}
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     operator=()
PURPOSE:           overloads the assignment operator
RETURNS:           reference to const Matrix
NOTES:             performs a deep copy of the Matrix object
----------------------------------------------------------------------------- */
template <class T>
const Matrix<T>& Matrix<T>::operator=(const Matrix<T>& right)
{
	if (this != &right)
	{
		CopyAttributes(right);
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     DestroyMatrix()
PURPOSE:           releases dynamically allocated memory
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::DestroyMatrix()
{
	if (_matrix != nullptr)
	{
		for (int ix = 0; ix < _rows; ++ix)
		{
			delete [] _matrix[ix];
			_matrix[ix] = nullptr;
		}

		delete [] _matrix;
		_matrix = nullptr;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     CopyAttributes()
PURPOSE:           copy the attributes from one Matrix object to another Matrix object
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::CopyAttributes(const Matrix &right)
{
	_argc = right._argc;
	std::copy(right._argv, right._argv + right._argc, _argv);
	_command = right._command;
	_filenameOne = right._filenameOne;
	_filenameTwo = right._filenameTwo;
	_outputFilename = right._outputFilename;
	_isFilenameOneSet = right._isFilenameOneSet;
	_isFilenameTwoSet = right._isFilenameTwoSet;
	_isOutputFileSet = right._isOutputFileSet;

	CopyMatrix(right);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     CopyMatrix()
PURPOSE:           copies the matrix from one Matrix object to another Matrix object
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::CopyMatrix(const Matrix &right)
{
	DestroyMatrix();

	_rows = right._rows;
	_cols = right._cols;

	_matrix = new T*[_rows];

	for (int row = 0; row < _rows; ++row)
	{
		_matrix[row] = new T[_cols];
	}

	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			_matrix[row][col] = right._matrix[row][col];
		}
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     DisplayHelp()
PURPOSE:           displays the help menu which explains how to use the program
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::DisplayHelp() const
{
	std::cout << std::endl << "***** BEGIN HELP MENU *****";
	std::cout << std::endl << "How to use this program:" << std::endl;
	std::cout << std::endl << "This program has no interactive mode that can be accessed from the command line." << std::endl;
	std::cout << std::endl << "Type './matrix_math -h' to access the help menu (you already know how to do this!)";
	std::cout << std::endl << "Type './matrix_math cmd1 cmd2 etc etc' to perform operations" << std::endl;
	std::cout << std::endl << "The available command options are the following:" << std::endl;
	std::cout << std::endl << "-h ~ displays the help menu";
	std::cout << std::endl << "-inp ~ reads in a matrix from a .mtx file and displays the matrix to the scree";
	std::cout << std::endl << "-out ~ outputs the matrix to a .mtx file with the specified name";
	std::cout << std::endl << "-add ~ reads in two matrices and adds them together";
	std::cout << std::endl << "-sub ~ reads in two matrices and subtracts one from the other";
	std::cout << std::endl << "-mul ~ reads in two matrices and finds the product";
	std::cout << std::endl << "-eq ~ reads in two matrices and determines whether they have equivalent values";
	std::cout << std::endl << "-T ~ reads in a matrix and transposes the matrix";
	std::cout << std::endl << "-1 ~ (symbol = 'minus one') reads in a matrix and calculates the inverse of the matrix if one exists";
	std::cout << std::endl << "-det ~ reads in a matrix and calculates its determinant";
	std::cout << std::endl << "-solve ~ reads in a matrix and solves a system of equations using Cramer's Rule" << std::endl;
	std::cout << std::endl << "Examples of valid commands:" << std::endl;
	std::cout << std::endl << "./matrix_math -inp A";
	std::cout << std::endl << "./matrix_math -inp A -out C";
	std::cout << std::endl << "./matrix_math -add A B";
	std::cout << std::endl << "./matrix_math -sub A B";
	std::cout << std::endl << "./matrix_math -mul A B";
	std::cout << std::endl << "./matrix_math -eq A B";
	std::cout << std::endl << "./matrix_math -T A";
	std::cout << std::endl << "./matrix_math -1 A";
	std::cout << std::endl << "./matrix_math -det A";
	std::cout << std::endl << "";
	std::cout << std::endl << "Examples of invalid commands:" << std::endl;
	std::cout << std::endl << "./matrix_math";
	std::cout << std::endl << "./matrix_math -n";
	std::cout << std::endl << "./matrix_math -Inp";
	std::cout << std::endl << "./matrix_math -inp not_a_real_filename";
	std::cout << std::endl << "./matrix_math -add A";
	std::cout << std::endl << "***** END OF HELP MENU *****" << std::endl << std::endl;
}