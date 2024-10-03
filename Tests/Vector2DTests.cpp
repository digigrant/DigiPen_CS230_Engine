#include <gtest/gtest.h>
#include "Vector2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Vector2DTests
{
	TEST(Vector2DTests, Vector2DZero)
	{
		Vector2D v;
		Vector2DZero(&v);
		EXPECT_FLOAT_EQ(0.0f, v.x);
		EXPECT_FLOAT_EQ(0.0f, v.y);
	}

	TEST(Vector2DTests, Vector2DSet)
	{
		Vector2D v;
		Vector2DSet(&v, 1.0f, 2.0f);
		EXPECT_FLOAT_EQ(1.0f, v.x);
		EXPECT_FLOAT_EQ(2.0f, v.y);
	}

	TEST(Vector2DTests, Vector2DNeg)
	{
		Vector2D v = { 1.0f, 2.0f };
		Vector2DNeg(&v, &v);
		EXPECT_FLOAT_EQ(-1.0f, v.x);
		EXPECT_FLOAT_EQ(-2.0f, v.y);
	}

	TEST(Vector2DTests, Vector2DAdd)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2D vout;
		Vector2DAdd(&vout, &v1, &v2);
		EXPECT_FLOAT_EQ(4.0f, vout.x);
		EXPECT_FLOAT_EQ(6.0f, vout.y);
	}

	TEST(Vector2DTests, AddVectorsInPlace)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2DAdd(&v1, &v1, &v2);
		EXPECT_FLOAT_EQ(4.0f, v1.x);
		EXPECT_FLOAT_EQ(6.0f, v1.y);
	}

	TEST(Vector2DTests, Vector2DSub)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 10.0f, 15.0f };
		Vector2D vout;
		Vector2DSub(&vout, &v1, &v2);
		EXPECT_FLOAT_EQ(-9.0f, vout.x);
		EXPECT_FLOAT_EQ(-13.0f, vout.y);
	}

	TEST(Vector2DTests, Vector2DNormalize)
	{
		Vector2D vin = { 10.0f, 20.0f };
		Vector2D vout;
		Vector2DNormalize(&vout, &vin);
		EXPECT_FLOAT_EQ(0.4472136f, vout.x);
		EXPECT_FLOAT_EQ(0.8944272f, vout.y);
	}

	TEST(Vector2DTests, Vector2DScale)
	{
		Vector2D v = { 1.0f, 2.0f };
		Vector2D vout;
		Vector2DScale(&vout, &v, 2.0f);
		EXPECT_FLOAT_EQ(2.0f, vout.x);
		EXPECT_FLOAT_EQ(4.0f, vout.y);
	}

	TEST(Vector2DTests, Vector2DScaleAdd)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2D vout;
		Vector2DScaleAdd(&vout, &v1, 2.0f, &v2);
		EXPECT_FLOAT_EQ(5.0f, vout.x);
		EXPECT_FLOAT_EQ(8.0f, vout.y);
	}

	TEST(Vector2DTests, Vector2DScaleSub)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2D vout;
		Vector2DScaleSub(&vout, &v1, 2.0f, &v2);
		EXPECT_FLOAT_EQ(-1.0f, vout.x);
		EXPECT_FLOAT_EQ(0.0f, vout.y);
	}

	TEST(Vector2DTests, Vector2DLength)
	{
		Vector2D v = { 1.0f, 2.0f };
		float length = Vector2DLength(&v);
		EXPECT_FLOAT_EQ(2.236068f, length);
	}

	TEST(Vector2DTests, Vector2DSquareLength)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		float lengthSquared = Vector2DSquareLength(&v1);
		EXPECT_FLOAT_EQ(5.0f, lengthSquared);
	}

	TEST(Vector2DTests, Vector2DDistance)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		float distance = Vector2DDistance(&v1, &v2);
		EXPECT_FLOAT_EQ(2.828427f, distance);
	}

	TEST(Vector2DTests, Vector2DSquareDistance)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		float distanceSquared = Vector2DSquareDistance(&v1, &v2);
		EXPECT_FLOAT_EQ(8.0f, distanceSquared);
	}

	TEST(Vector2DTests, Vector2DDotProduct)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		float dotProduct = Vector2DDotProduct(&v1, &v2);
		EXPECT_FLOAT_EQ(11.0f, dotProduct);
	}

	TEST(Vector2DTests, Vector2DFromAngleDeg)
	{
		Vector2D v;
		Vector2DFromAngleDeg(&v, 30.0f);
		EXPECT_FLOAT_EQ(0.8660254f, v.x);
		EXPECT_FLOAT_EQ(0.5f, v.y);
	}

	TEST(Vector2DTests, Vector2DFromAngleRad)
	{
		Vector2D v;
		Vector2DFromAngleRad(&v, M_PI / 6.0f);
		EXPECT_FLOAT_EQ(0.8660254f, v.x);
		EXPECT_FLOAT_EQ(0.5f, v.y);
	}

	TEST(Vector2DTests, Vector2DToAngleRad)
	{
		Vector2D v = { 0.8660254f, 0.5f };
		float angle = Vector2DToAngleRad(&v);
		EXPECT_FLOAT_EQ(0.5235988f, angle);
	}
}