#include <gtest/gtest.h>
#include "Matrix2D.h"
#include "DGL.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace
{
	// Helper function to check if two matrices are equal.
	bool AreMatricesEqual(const Matrix2D* mat1, const Matrix2D* mat2)
	{
		for (int r = 0; r < 4; ++r)
		{
			for (int c = 0; c < 4; ++c)
			{
				if (Matrix2DRowCol(mat1, r, c) != Matrix2DRowCol(mat2, r, c))
				{
					return false;
				}
			}
		}
		return true;
	}

	// Helper function to check if two matrices are almost equal within a certain epsilon
	bool AreMatricesAlmostEqual(const Matrix2D* mat1, const Matrix2D* mat2, float epsilon)
	{
		for (int r = 0; r < 4; ++r)
		{
			for (int c = 0; c < 4; ++c)
			{
				if (fabs(Matrix2DRowCol(mat1, r, c) - Matrix2DRowCol(mat2, r, c)) > epsilon)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool AreVectorsEqual(const Vector2D* vec1, const Vector2D* vec2)
	{
		return (vec1->x == vec2->x && vec1->y == vec2->y);
	}

	// Helper function to get the identity matrix.
	Matrix2D GetIdentityMatrix()
	{
		Matrix2D matrix = { {{1, 0, 0, 0},
						 {0, 1, 0, 0},
						 {0, 0, 1, 0},
						 {0, 0, 0, 1}} };

		return matrix;
	}

	// Helper function to create a sample matrix
	Matrix2D CreateSampleMatrix()
	{
		Matrix2D mat = { {{1, 2, 3, 4},
						 {5, 6, 7, 8},
						 {9, 10, 11, 12},
						 {13, 14, 15, 16}} };
		return mat;
	}
}


namespace Matrix2DTests
{
	TEST(Matrix2DIdentityTest, Matrix2DIdentity)
	{
		Matrix2D matrix;
		Matrix2DIdentity(&matrix);

		ASSERT_TRUE(AreMatricesEqual(&matrix, &GetIdentityMatrix()));
	}

	TEST(Matrix2DIdentityTest, NullResultPointer)
	{
		ASSERT_NO_THROW(Matrix2DIdentity(nullptr));
	}

	TEST(Matrix2DConcatTest, MultiplyTwoMatrices)
	{
		Matrix2D mtx0 = { {{2, 3, 4, 1}, {5, 6, 7, 2}, {8, 9, 10, 3}, {1, 2, 3, 4}} };
		Matrix2D mtx1 = { {{1, 0, 2, 0}, {0, 1, 0, 3}, {4, 0, 1, 0}, {0, 3, 0, 1}} };

		Matrix2D expectedResult = { {{18, 6, 8, 10}, {33, 12, 17, 20}, {48, 18, 26, 30}, {13, 14, 5, 10}} };
		Matrix2D result;

		Matrix2DConcat(&result, &mtx0, &mtx1);

		ASSERT_TRUE(AreMatricesEqual(&result, &expectedResult));
	}

	TEST(Matrix2DConcatTest, MultiplyWithIdentityMatrix)
	{
		Matrix2D mtx0 = { {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}} };
		Matrix2D mtx1 = GetIdentityMatrix();
		Matrix2D expectedResult = mtx0; // Multiplying by identity matrix should return the same matrix.
		Matrix2D result;

		Matrix2DConcat(&result, &mtx0, &mtx1);

		ASSERT_TRUE(AreMatricesEqual(&result, &expectedResult));
	}

	TEST(Matrix2DConcatTest, ResultPointerSameAsInput)
	{
		Matrix2D mtx0 = { {{2, 3, 4, 1}, {5, 6, 7, 2}, {8, 9, 10, 3}, {1, 2, 3, 4}} };
		Matrix2D mtx1 = { {{1, 0, 2, 0}, {0, 1, 0, 3}, {4, 0, 1, 0}, {0, 3, 0, 1}} };
		Matrix2D expectedResult = { {{18, 6, 8, 10}, {33, 12, 17, 20}, {48, 18, 26, 30}, {13, 14, 5, 10}} };

		Matrix2DConcat(&mtx0, &mtx0, &mtx1);

		ASSERT_TRUE(AreMatricesEqual(&mtx0, &expectedResult));
	}

	TEST(Matrix2DConcatTest, NullResultPointer)
	{
		Matrix2D mtx0 = GetIdentityMatrix();
		Matrix2D mtx1 = GetIdentityMatrix();

		ASSERT_NO_THROW(Matrix2DConcat(nullptr, &mtx0, &mtx1));
	}

	TEST(Matrix2DTransposeTest, BasicTranspose)
	{
		Matrix2D mtx = CreateSampleMatrix();
		Matrix2D result;
		Matrix2D expectedResult = { {{1, 5, 9, 13},
									{2, 6, 10, 14},
									{3, 7, 11, 15},
									{4, 8, 12, 16}} };

		Matrix2DTranspose(&result, &mtx);

		// Expect the result to be the transpose of the original matrix
		ASSERT_TRUE(AreMatricesEqual(&result, &expectedResult));
	}

	TEST(Matrix2DTransposeTest, InPlaceTranspose)
	{
		Matrix2D mtx = CreateSampleMatrix();
		Matrix2D expectedResult = { {{1, 5, 9, 13},
									{2, 6, 10, 14},
									{3, 7, 11, 15},
									{4, 8, 12, 16}} };

		// Perform in-place transpose
		Matrix2DTranspose(&mtx, &mtx);

		// Expect the matrix to be transposed in place
		ASSERT_TRUE(AreMatricesEqual(&mtx, &expectedResult));
	}

	TEST(Matrix2DTransposeTest, NullResultPointer)
	{
		Matrix2D mtx = CreateSampleMatrix();

		ASSERT_NO_THROW(Matrix2DTranspose(nullptr, &mtx));
	}

	TEST(Matrix2DTranslateTest, BasicTranslate)
	{
		Matrix2D result;
		Matrix2D expectedResult = { {{1, 0, 0, 5},
									{0, 1, 0, 10},
									{0, 0, 1, 0},
									{0, 0, 0, 1}} };

		Matrix2DTranslate(&result, 5, 10);

		// Expect the result to be a translation matrix
		ASSERT_TRUE(AreMatricesEqual(&result, &expectedResult));
	}

	TEST(Matrix2DTranslateTest, NullResultPointer)
	{
		ASSERT_NO_THROW(Matrix2DTranslate(nullptr, 5, 10));
	}

	TEST(Matrix2DScaleTest, BasicScale)
	{
		Matrix2D result;
		Matrix2D expectedResult = { {{2, 0, 0, 0},
									{0, 3, 0, 0},
									{0, 0, 1, 0},
									{0, 0, 0, 1}} };

		Matrix2DScale(&result, 2, 3);

		// Expect the result to be a scaling matrix
		ASSERT_TRUE(AreMatricesEqual(&result, &expectedResult));
	}

	TEST(Matrix2DScaleTest, NullResultPointer)
	{
		ASSERT_NO_THROW(Matrix2DScale(nullptr, 2, 3));
	}

	TEST(Matrix2DRotDegTest, BasicRotation)
	{
		Matrix2D result;
		Matrix2D expectedResult = { {{0, -1, 0, 0},
									{1, 0, 0, 0},
									{0, 0, 1, 0},
									{0, 0, 0, 1}} };

		Matrix2DRotDeg(&result, 90);

		// Expect the result to be a rotation matrix
		ASSERT_TRUE(AreMatricesAlmostEqual(&result, &expectedResult, 0.0001f));
	}

	TEST(Matrix2DRotDegTest, NullResultPointer)
	{
		ASSERT_NO_THROW(Matrix2DRotDeg(nullptr, 90));
	}

	TEST(Matrix2DRotRadTest, BasicRotation)
	{
		Matrix2D result;
		Matrix2D expectedResult = { {{0, -1, 0, 0},
									{1, 0, 0, 0},
									{0, 0, 1, 0},
									{0, 0, 0, 1}} };

		Matrix2DRotRad(&result, ((float)M_PI / 2.0f));

		// Expect the result to be a rotation matrix
		ASSERT_TRUE(AreMatricesAlmostEqual(&result, &expectedResult, 0.0001f));
	}

	TEST(Matrix2DRotRadTest, NullResultPointer)
	{
		ASSERT_NO_THROW(Matrix2DRotRad(nullptr, (float)(M_PI / 2)));
	}

	/*
	TEST(Matrix2DMultVecTest, BasicMultiplication)
	{
		Matrix2D mtx = { {{1, 2, 3, 4},
						{5, 6, 7, 8},
						{9, 10, 11, 12},
						{13, 14, 15, 16}} };
		Vector2D vec = { 1, 2 };
		Vector2D result;
		Vector2D expectedResult = { 30, 70 };

		Matrix2DMultVec(&result, &mtx, &vec);

		// Expect the result to be the multiplication of the matrix and vector
		ASSERT_TRUE(AreVectorsEqual(&result, &expectedResult));
	}

	TEST(Matrix2DMultVecTest, InPlaceMultiplication)
	{
		Matrix2D mtx = { {{1, 2, 3, 4},
						{5, 6, 7, 8},
						{9, 10, 11, 12},
						{13, 14, 15, 16}} };
		Vector2D vec = { 1, 2 };
		Vector2D expectedResult = { 30, 70 };

		// Perform in-place multiplication
		Matrix2DMultVec(&vec, &mtx, &vec);

		// Expect the vector to be the result of the multiplication
		ASSERT_TRUE(AreVectorsEqual(&vec, &expectedResult));
	}
	*/

	TEST(Matrix2DMultVecTest, NullResultPointer)
	{
		Matrix2D mtx = { {{1, 2, 3, 4},
						{5, 6, 7, 8},
						{9, 10, 11, 12},
						{13, 14, 15, 16}} };
		Vector2D vec = { 1, 2 };

		ASSERT_NO_THROW(Matrix2DMultVec(nullptr, &mtx, &vec));
	}

	/*
	TEST(Matrix2DMultVecTest, NullMatrixPointer)
	{
		Vector2D result;
		Vector2D vec = { 1, 2 };

		ASSERT_NO_THROW(Matrix2DMultVec(&result, nullptr, &vec));
	}
	*/

	/*
	*TEST(Matrix2DMultVecTest, NullVectorPointer)
	{
		Vector2D result;
		Matrix2D mtx = { {{1, 2, 3, 4},
						{5, 6, 7, 8},
						{9, 10, 11, 12},
						{13, 14, 15, 16}} };

		ASSERT_NO_THROW(Matrix2DMultVec(&result, &mtx, nullptr));
	}
	*/
}