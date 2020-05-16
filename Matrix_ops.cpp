/* -----------------------------------------------------------------------------
FILE NAME:         Matrix_ops.cpp
DESCRIPTION:       implementation file
USAGE:             ./matrix_math
COMPILER:          GNU g++ compiler on Linux / g++ -std=c++11 -Wall -Wextra -pedantic
NOTES:			   Matrix_ops derived class

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Peter Akala        2018-04-18         1.0 - created Matrix_ops.cpp file
Peter Akala		   2018-04-30		  2.0 - defined member functions + operator overloads
Peter Akala		   2018-05-01		  3.0 - debugging modifications
Peter Akala		   2018-05-02		  4.0 - debugging modifications
Peter Akala		   2018-05-03		  5.0 - final testing
----------------------------------------------------------------------------- */

#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include "Matrix.h"
#include "Matrix_ops.h"

/* -----------------------------------------------------------------------------
FUNCTION NAME:     operator+()
PURPOSE:           overloads the addition operator
RETURNS:           Matrix_ops
NOTES:             adds two Matrix_ops objects together
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T> Matrix_ops<T>::operator+(const Matrix_ops<T>& right) const
{
		int rows = this->_rows;
		int cols = this->_cols;

		if (rows == right._rows && cols == right._cols)
		{
			Matrix_ops result = right;

			for (int row = 0; row < rows; ++row)
			{
				for (int col = 0; col < cols; ++col)
				{
					result._matrix[row][col] = this->_matrix[row][col] + right._matrix[row][col];
				}
			}

			return result;
		}
		else
		{
			std::string exceptionStr = "\nError: number of rows and number of columns did not match for the matrices being added\n";
			throw exceptionStr;
		}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     operator-()
PURPOSE:           overloads the subtraction operator
RETURNS:           Matrix_ops
NOTES:             subtracts one Matrix_ops object from another Matrix_ops object
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T> Matrix_ops<T>::operator-(const Matrix_ops<T>& right) const
{
	int rows = this->_rows;
	int cols = this->_cols;

	if (rows == right._rows && cols == right._cols)
	{
		Matrix_ops result = right;

		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < cols; ++col)
			{
				result._matrix[row][col] = this->_matrix[row][col] - right._matrix[row][col];
			}
		}

		return result;
	}
	else
	{
		std::string exceptionStr = "\nError: number of rows and number of columns did not match for the matrices being subtracted\n";
		throw exceptionStr;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     operator*()
PURPOSE:           overloads the multiplication operator
RETURNS:           Matrix_ops
NOTES:             calculates the product of two Matrix_ops objects
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T> Matrix_ops<T>::operator*(const Matrix_ops<T>& right) const
{
	int rows = this->_rows;
	int cols = this->_cols;

	if (cols == right._rows)
	{
		cols = right._cols;

		Matrix_ops result = *this;

		result.DestroyMatrix();

		result._rows = rows;
		result._cols = cols;

		result._matrix = new T*[rows];

		for (int row = 0; row < rows; ++row)
		{
			result._matrix[row] = new T[cols];
		}

		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < cols; ++col)
			{
				result._matrix[row][col] = 0;
			}
		}

		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < cols; ++col)
			{
				for (int ix = 0; ix < cols; ++ix)
				{
					result._matrix[row][col] += this->_matrix[row][ix] * right._matrix[ix][col];
				}
			}
		}

		return result;
	}
	else
	{
		std::string exceptionStr = "\nError: the number of columns of the first matrix does not match the number of rows of the second matrix for the matrices being multiplied\n";
		throw exceptionStr;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     operator==()
PURPOSE:           overloads the equality operator
RETURNS:           bool
RETURNS:           Nothing (void function)
NOTES:             determines whether two Matrix_ops object have equivalent values for their respective matrix values
----------------------------------------------------------------------------- */
template <class T>
bool Matrix_ops<T>::operator==(const Matrix_ops<T>& right) const
{
	int rows = this->_rows;
	int cols = this->_cols;

	try
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < cols; ++col)
			{
				if (this->_matrix[row][col] != right._matrix[row][col])
				{
					int exceptionInt = -999;
					throw exceptionInt;
				}
			}
		}
	}
	catch (int)
	{
		return false;
	}

	return true;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     SetEquality()
PURPOSE:           sets the status of an equality comparison between two Matrix_ops objects
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix_ops<T>::SetEquality(bool isEqual)
{
	_isEqual = isEqual;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     name-of-function()
PURPOSE:           retrieves the status of the comparison between two Matrix_ops objects
RETURNS:           bool
NOTES:
----------------------------------------------------------------------------- */
template <class T>
bool Matrix_ops<T>::GetEquality() const
{
	return _isEqual;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     trans()
PURPOSE:           transposes a matrix
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix_ops<T>::trans()
{
	int rows = this->_cols;
	int cols = this->_rows;

	Matrix_ops result = *this;

	result.DestroyMatrix();
	result._rows = rows;
	result._cols = cols;

	result._matrix = new T*[rows];

	for (int row = 0; row < rows; ++row)
	{
		result._matrix[row] = new T[cols];
	}

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			result._matrix[row][col] = this	->_matrix[col][row];
		}
	}

	*this = result;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     det()
PURPOSE:           calculates the determinant of a matrix
RETURNS:           int
NOTES:
----------------------------------------------------------------------------- */
template <class T>
int Matrix_ops<T>::det(T**& matrixOriginal, int order)
{
	if (order == 1)
	{
		return matrixOriginal[0][0];
	}
	else if (order == 2)
	{
		return matrixOriginal[0][0] * matrixOriginal[1][1] - matrixOriginal[0][1] * matrixOriginal[1][0];
	}
	else
	{
		int determinant{0};

		for (int ix = 0; ix < order; ++ix)
		{
			T** temp;
			temp = new T*[order - 1];
			for (int ix = 0; ix < order - 1; ++ix)
			{
				temp[ix] = new T[order - 1];
			}

			int rowTemp = 0;
			int colTemp = 0;

			for (int row = 0; row < order; ++row, ++rowTemp)
			{
				if (row != 0)
				{
					colTemp = 0;

					for (int col = 0; col < order; ++col)
					{
						if (col != ix)
						{
							temp[rowTemp][colTemp] = matrixOriginal[row][col];
							++colTemp;
						}
					}
				}
				else
				{
					--rowTemp;
				}
			}

			int sign{1};

			if (ix % 2 == 0)
			{
				sign = -1;
			}

			determinant += sign * matrixOriginal[0][ix] * det(temp, order - 1);
		}

		if (matrixOriginal != nullptr)
		{
			// release dynamic array memory
			for (int ix = 0; ix < order; ++ix)
			{
				delete [] matrixOriginal[ix];
				matrixOriginal[ix] = nullptr;
			}
			delete [] matrixOriginal;
			matrixOriginal = nullptr;
		}

		return determinant;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     det2()
PURPOSE:           calculates the determinant of a matrix
RETURNS:           int
NOTES:             not used in program, wanted to compare performance between different -det() functions, ran out of time to get a final answer
----------------------------------------------------------------------------- */
template <class T>
int Matrix_ops<T>::det2(T**& matrixOriginal, int order)
{
	int rows = this->_rows;
	int cols = this->_cols;

	if (order == 1)
	{
		return matrixOriginal[0][0];
	}
	else if (order == 2)
	{
		return matrixOriginal[0][0] * matrixOriginal[1][1] - matrixOriginal[0][1] * matrixOriginal[1][0];
	}
	else
	{
		int determinant{0};

		for (int ix = 0; ix < order; ++ix)
		{
			int rowTemp{0};
			int colTemp{0};

			T** temp;
			temp = new T*[rows];
			for (int row = 0; row < rows; ++row)
			{
				temp[row] = new T[cols];
			}

			for (int rowOriginal = 1; rowOriginal < order; ++rowOriginal)
			{
				for (int colOriginal=0; colOriginal < order; ++colOriginal)
				{
					if (colOriginal == ix)
					{
						continue;
					}

					temp[rowTemp][colTemp] = matrixOriginal[rowOriginal][colOriginal];
					++colTemp
							;
					if (colTemp == order - 1)
					{
						++rowTemp;
						colTemp = 0;
					}
				}
			}

			int sign{1};

			if (ix % 2 == 0)
			{
				sign = -1;
			}

			determinant += sign * matrixOriginal[0][ix] * pow(-1, ix) * det(temp, order-1);
		}

	if (matrixOriginal != nullptr)
	{
		// release dynamic array memory
		for (int ix = 0; ix < order; ++ix)
		{
			delete [] matrixOriginal[ix];
			matrixOriginal[ix] = nullptr;
		}
		delete [] matrixOriginal;
		matrixOriginal = nullptr;
	}

	return determinant;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     inv()
PURPOSE:           calculates the inverse of a matrix
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
template <class T>
void Matrix_ops<T>::inv()
{
	int rows = this->_rows;
	int cols = this->_cols;
	int order = rows;

	// columns should be twice the size of original matrix in order to fit identity matrix
	double** augmentedArray;
	augmentedArray = new double*[order];
	for (int ix =  0; ix < order; ++ix)
	{
		augmentedArray[ix] = new double[order * 2];
	}

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
			determinantArray[row][col] = this->_matrix[row][col];
			augmentedArray[row][col] = this->_matrix[row][col];
		}
	}

	// print out the entire augmented array
	/*std::cout << std::endl << std::endl << "ENTIRE AUGMENTED ARRAY = " << std::endl;
	for (int row = 0; row < order; ++row)
	{
		for (int col = 0; col < order * 2; ++col)
		{
			std::cout << augmentedArray[row][col] << " ";
		}

		std::cout << std::endl;
	}*/

	// print out identity part augmented array
	/*std::cout << std::endl << std::endl << "IDENTITY PART OF AUG ARRAY = " << std::endl;
	for (int row = 0; row < order; ++row)
	{
		for (int col = order; col < order * 2; ++col)
		{
			std::cout << augmentedArray[row][col] << " ";
		}

		std::cout << std::endl;
	}*/


	int determinant = this->det(determinantArray, rows);

	if (determinant == 0)
	{
		std::string exceptionDeterminantEqualsZero = "\nError: a singular matrix does not have an inverse\n";
		throw exceptionDeterminantEqualsZero;
	}

	/* calculate inverse using gauss-jordan method
	 * http://www.mathsisfun.com/algebra/matrix-inverse.html
	 * https://www.mathsisfun.com/algebra/matrix-inverse-row-operations-gauss-jordan.html
	 * http://matrix.reshish.com/inverse.php
	*/

	// add identity matrix to augmented matrix
	for (int row = 0; row < order; ++row)
	{
		for (int col = order; col < order * 2; ++col)
		{
			if (row == col - order)
			{
				augmentedArray[row][col] = 1;
			}
			else
			{
				augmentedArray[row][col] = 0;
			}
		}
	}

	// print out identity part augmented array
	/*std::cout << std::endl << std::endl << "IDENTITY PART OF AUG ARRAY = " << std::endl;
	for (int row = 0; row < order; ++row)
	{
		for (int col = order; col < order * 2; ++col)
		{
			std::cout << augmentedArray[row][col] << " ";
		}

		std::cout << std::endl;
	}*/

	// add proper values to identity part of augmented array
	for (int row = 0; row < order; ++row)
	{
		double value = augmentedArray[row][row];

		for (int col = row; col < order * 2; ++col)
		{
			augmentedArray[row][col] = augmentedArray[row][col] / value;
		}

		for (int rowAugment = 0; rowAugment < order; ++rowAugment)
		{
			if (row != rowAugment)
			{
				value = augmentedArray[rowAugment][row];

				for (int colAugment = 0; colAugment < order * 2; ++colAugment)
				{
					augmentedArray[rowAugment][colAugment] = augmentedArray[rowAugment][colAugment] - value * augmentedArray[row][colAugment];
				}
			}
		}
	}

	std::cout << "the inverse of matrix " << this->_filenameOne << " = " << std::endl;

	for (int row = 0; row < rows; ++row)
	{
		std::cout << "|";

		for (int col = order; col < order * 2; ++col)
		{
			//result._matrix[row][row] = augmentedArray[row][col];
			std::cout << std::setw(10) << augmentedArray[row][col] << " ";
		}

		std::cout << "|";
		std::cout << std::endl;
	}

	if (augmentedArray != nullptr)
	{
		// release dynamic array memory
		for (int ix = 0; ix < order; ++ix)
		{
			delete [] augmentedArray[ix];
			augmentedArray[ix] = nullptr;
		}
		delete [] augmentedArray;
		augmentedArray = nullptr;
	}

	if (determinantArray != nullptr)
	{
		// release dynamic array memory
		for (int ix = 0; ix < order; ++ix)
		{
			delete [] determinantArray[ix];
			determinantArray[ix] = nullptr;
		}
		delete [] determinantArray;
		determinantArray = nullptr;
	}
}
