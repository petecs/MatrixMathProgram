/* -----------------------------------------------------------------------------
FILE NAME:         Matrix.h
DESCRIPTION:       specification file
USAGE:             ./matrix_math
COMPILER:          GNU g++ compiler on Linux / g++ -std=c++11 -Wall -Wextra -pedantic
NOTES:			   Matrix base class

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Peter Akala        2018-04-18         1.0 - created Matrix.h file
Peter Akala		   2018-04-28		  2.0 - declared constructors, destructor, attributes, member functions
Peter Akala		   2018-04-29		  3.0 - added operator overloads and friend functions
Peter Akala		   2018-05-03		  4.0 - added help menu + constructor/destructor test ability
----------------------------------------------------------------------------- */

/*
 * ~base class
 * gets commands
 * validates commands
 * gets filenames
 * validates files
 * checks data
 *
 * ~derived class
 * all math on verified and validated data
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iomanip>
#include <iostream>
#include "Matrix_ops.h"

template <class T>
class Matrix
{
	protected:
		// constants
		static const int MAX_COMMANDLINE_NUMBER{6};
		static const int HELP_CMD{1};
		static const int READ_CMD{2};
		static const int ADD_CMD{3};
		static const int SUBTRACT_CMD{4};
		static const int MULTIPLY_CMD{5};
		static const int EQUALITY_CMD{6};
		static const int TRANSPOSE_CMD{7};
		static const int INVERSE_CMD{8};
		static const int DETERMINANT_CMD{9};
		static const int SOLVE_CMD{10};
		static const int DESTRUCTOR_TEST{99};
		static const int TEMPLATE_TEST{100};

		// attributes
		bool _isDefaultConstructor{false};
		bool _isDestructObject{false};
		int _argc{0};
		std::string _argv[MAX_COMMANDLINE_NUMBER];
		int _command{0};
		std::string _filenameOne{""};
		std::string _filenameTwo{""};
		std::string _outputFilename{""};
		bool _isFilenameOneSet{false};
		bool _isFilenameTwoSet{false};
		bool _isOutputFileSet{false};
		int _rows{0};
		int _cols{0};
		T** _matrix{nullptr};

		// member functions
		void OpenInputFile(std::string filename, std::ifstream& file);
		void CloseInputFile(std::ifstream& file);
		void ReadDataIntoMatrix(const std::string filename);
		void DisplayHelp() const;

	public:
		// member functions
		void InputCommandlineArguments(const int argc, char* argv[]);
		int ValidateArguments();
		void SetCommand(int command);
		void ValidateInputFiles();
		void ValidateMatrices(Matrix_ops<T>& matrixOne, Matrix_ops<T>& matrixTwo);
		void DisplayMatrix() const;
		void WriteToFile(const Matrix_ops<T>& result);
		void WriteMatrixToFile(const Matrix_ops<T> matrix, std::ofstream& outfile);
		void ExecuteCommand();
		void DestroyMatrix();
		void CopyAttributes(const Matrix& right);
		void CopyMatrix(const Matrix& right);

		// operator overloads
		const Matrix& operator=(const Matrix& right);

		// constructors
		Matrix();
		Matrix(const int argc, char* argv[]);

		// copy constructor
		Matrix(const Matrix& right);

		// destructor
		virtual ~Matrix();

		// operator overloads (friends / non-member)
		/* -----------------------------------------------------------------------------
		FUNCTION NAME:     operator<<()
		PURPOSE:           overloads the insertion operator
		RETURNS:           reference to ostream object
		NOTES:             allows the insertion operator to be used on a Matrix object /
		----------------------------------------------------------------------------- */
		friend std::ostream& operator<<(std::ostream& output, const Matrix<T>& right)
		{
			for (int row = 0; row < right._rows; ++row)
			{
				output << "|";
				for (int col = 0; col < right._cols; ++col)
				{
					std::cout << std::setw(5) << right._matrix[row][col] << " ";
				}

				std::cout << "|";
				std::cout << std::endl;
			}

			return output;
		}

		/* -----------------------------------------------------------------------------
		FUNCTION NAME:     operator>>()
		PURPOSE:           overloads the insertion operator
		RETURNS:           reference to istream object
		NOTES:             allows the extraction operator to be used on a Matrix object
		----------------------------------------------------------------------------- */
		friend std::istream& operator>>(std::istream& input, Matrix<T>& right)
		{
			std::string exceptionStr = "\nError: invalid data entered using '>>' operator\n";

			//std::cout << std::endl << "Enter number of rows: ";
			input >> right._rows;

			if (!input)
			{
				throw exceptionStr;
			}

			//std::cout << "Enter number of cols: ";
			input >> right._cols;

			if (!input)
			{
				throw exceptionStr;
			}

			//std::cout << std::endl << "Current number of rows = " << right._rows;
			//std::cout << std::endl << "Current number of columns = " << right._cols << std::endl;
			//std::cout << std::endl << "Current matrix values:" << std::endl << std::endl;

			if (right._matrix != nullptr)
			{
				std::cout << std::endl << "The matrix's current values before applying the extraction operator to the object:";
				right.DisplayMatrix();
			}
			else
			{
				std::cout << std::endl << "The matrix was not previously set, so there are no values to display before applying the extraction operator to the object." << std::endl;
			}

			//right.DestroyMatrix();
			right._matrix = new T*[right._rows];
			for (int ix = 0; ix < right._rows; ++ix)
			{
				right._matrix[ix] = new T[right._cols];
			}
			for (int row = 0; row < right._rows; ++row)
			{
				for (int col = 0; col < right._cols; ++col)
				{
					//std::cout << "Enter value for row #" << row << " col # " << col << ": ";
					input >> right._matrix[row][col];
				}
			}

			std::cout << std::endl << "Number of rows entered = " << right._rows;
			std::cout << std::endl << "Number of columns entered = " << right._cols << std::endl;
			std::cout << std::endl << "After applying the extraction operation on the object, the matrix now has the values:" << std::endl << std::endl;

			right.DisplayMatrix();

			return input;
		}
};

#endif //MATRIX_H
