#include <gtest/gtest.h>
#include "Matrix2D.h"
#include "DGL.h"

namespace
{
	// Helper function to check if two matrices are equal.
	bool AreMatricesEqual(const Matrix2D* mat1, const Matrix2D* mat2)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (Matrix2DRowCol(mat1, i, j) != Matrix2DRowCol(mat2, i, j))
				{
					return false;
				}
			}
		}
		return true;
	}

	// Helper function to get the identity matrix.
	Matrix2D GetIdentityMatrix()
	{
		Matrix2D matrix;

		Matrix2DRowCol(&matrix, 0, 0) = 1;
		Matrix2DRowCol(&matrix, 0, 1) = 0;
		Matrix2DRowCol(&matrix, 0, 2) = 0;
		Matrix2DRowCol(&matrix, 0, 3) = 0;

		Matrix2DRowCol(&matrix, 1, 0) = 0;
		Matrix2DRowCol(&matrix, 1, 1) = 1;
		Matrix2DRowCol(&matrix, 1, 2) = 0;
		Matrix2DRowCol(&matrix, 1, 3) = 0;

		Matrix2DRowCol(&matrix, 2, 0) = 0;
		Matrix2DRowCol(&matrix, 2, 1) = 0;
		Matrix2DRowCol(&matrix, 2, 2) = 1;
		Matrix2DRowCol(&matrix, 2, 3) = 0;

		Matrix2DRowCol(&matrix, 3, 0) = 0;
		Matrix2DRowCol(&matrix, 3, 1) = 0;
		Matrix2DRowCol(&matrix, 3, 2) = 0;
		Matrix2DRowCol(&matrix, 3, 3) = 1;

		return matrix;
	}
}


namespace Matrix2DTests
{
	TEST(Matrix2DTests, Matrix2DIdentity)
	{
		Matrix2D matrix;
		Matrix2DIdentity(&matrix);

		ASSERT_TRUE(AreMatricesEqual(&matrix, &GetIdentityMatrix()));
	}

	// Test case 1: Concatenation of identity matrices
	TEST(Matrix2DConcatTest, ConcatenateIdentityMatrices)
	{
		Matrix2D mtx0, mtx1, result;
		Matrix2DIdentity(&mtx0);
		Matrix2DIdentity(&mtx1);

		Matrix2DConcat(&result, &mtx0, &mtx1);

		ASSERT_TRUE(AreMatricesEqual(&result, &GetIdentityMatrix()));
	}

	// Test case 2: Result pointer is the same as one of the input matrices
	TEST(Matrix2DConcatTest, ResultPointerSameAsInput)
	{
		Matrix2D mtx0, mtx1;
		Matrix2DIdentity(&mtx0);
		Matrix2DIdentity(&mtx1);

		Matrix2DConcat(&mtx0, &mtx0, &mtx1);

		ASSERT_TRUE(AreMatricesEqual(&mtx0, &GetIdentityMatrix()));
	}

	// Test case 3: Multiplication of two different matrices
	TEST(Matrix2DConcatTest, MultiplyTwoMatrices)
	{
		Matrix2D mtx0 = { {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}} };
		Matrix2D mtx1 = { {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} };
		Matrix2D expectedResult = mtx0; // Multiplying by identity matrix should return the same matrix.
		Matrix2D result;

		Matrix2DConcat(&result, &mtx0, &mtx1);

		ASSERT_TRUE(AreMatricesEqual(&result, &expectedResult));
	}

	// Test case 5: Multiplication of two non-identity matrices
	TEST(Matrix2DConcatTest, MultiplyTwoNonIdentityMatrices)
	{
		Matrix2D mtx0 = { {{2, 3, 4, 1}, {5, 6, 7, 2}, {8, 9, 10, 3}, {1, 2, 3, 4}} };
		Matrix2D mtx1 = { {{1, 0, 2, 0}, {0, 1, 0, 3}, {4, 0, 1, 0}, {0, 3, 0, 1}} };

		Matrix2D expectedResult = { {{18, 6, 8, 10}, {33, 12, 17, 20}, {48, 18, 26, 30}, {13, 14, 5, 10}} };
		Matrix2D result;

		Matrix2DConcat(&result, &mtx0, &mtx1);

		ASSERT_TRUE(AreMatricesEqual(&result, &expectedResult));
	}


	// Test case 4: Nullptr handling
	TEST(Matrix2DConcatTest, NullptrHandling)
	{
		Matrix2D mtx0, mtx1;
		Matrix2DIdentity(&mtx0);
		Matrix2DIdentity(&mtx1);

		// Expect no crashes or exceptions
		ASSERT_NO_THROW(Matrix2DConcat(nullptr, &mtx0, &mtx1));
	}

}