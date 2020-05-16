/* -----------------------------------------------------------------------------
FILE NAME:         Matrix_ops.h
DESCRIPTION:       specification file
USAGE:             ./matrix_math
COMPILER:          GNU g++ compiler on Linux / g++ -std=c++11 -Wall -Wextra -pedantic
NOTES:			   Matrix_op derived class

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Peter Akala        2018-04-18         1.0 - created Matrix_ops.h file
Peter Akala		   2018-04-30		  2.0 - declared attributes, member functions, and operator overloads
Peter Akala		   2018-05-02		  3.0 - removed unused attributes and functions
----------------------------------------------------------------------------- */

#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include "Matrix.h"

// forward declaration
template <class T> class Matrix;

template <class T>
class Matrix_ops : protected Matrix<T>
{
	private:
		bool _isEqual{false};

	protected:
	public:
		void SetEquality(bool isEqual);
		bool GetEquality() const;
		void trans();
		int det(T**& matrixOriginal, int order);
		int det2(T**& matrixOriginal,int order);
		void inv();
		void solve();

		// operator overloads
		Matrix_ops operator+(const Matrix_ops& right) const;
		Matrix_ops operator-(const Matrix_ops& right) const;
		Matrix_ops operator*(const Matrix_ops& right) const;
		bool operator==(const Matrix_ops& right) const;
};

#endif //MATRIX_OPS_H
