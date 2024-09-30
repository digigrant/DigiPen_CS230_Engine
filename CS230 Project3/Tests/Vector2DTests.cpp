#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include "Vector2D.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Vector2DTests
{
	TEST(Vector2DUnitTests, Vector2DZero)
	{
		Vector2D v;
		Vector2DZero(&v);
		EXPECT_FLOAT_EQ(0.0f, v.x);
		EXPECT_FLOAT_EQ(0.0f, v.y);
	}

	TEST(Vector2DUnitTests, Vector2DSet)
	{
		Vector2D v;
		Vector2DSet(&v, 1.0f, 2.0f);
		EXPECT_FLOAT_EQ(1.0f, v.x);
		EXPECT_FLOAT_EQ(2.0f, v.y);
	}

	RC_GTEST_PROP(Vector2DPropertyTests, Vector2DSetRandom, (float x, float y))
	{
		Vector2D v;
		Vector2DSet(&v, x, y);
		RC_ASSERT(v.x == x);
		RC_ASSERT(v.y == y);
	}

	TEST(Vector2DUnitTests, Vector2DNeg)
	{
		Vector2D v = { 1.0f, 2.0f };
		Vector2DNeg(&v, &v);
		EXPECT_FLOAT_EQ(-1.0f, v.x);
		EXPECT_FLOAT_EQ(-2.0f, v.y);
	}

	RC_GTEST_PROP(Vector2DPropertyTests, Vector2DNegRandom, (float x, float y))
	{
		Vector2D v = { x, y };
		Vector2DNeg(&v, &v);
		RC_ASSERT(v.x == -x);
		RC_ASSERT(v.y == -y);
	}

	TEST(Vector2DUnitTests, Vector2DAdd)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2D vout;
		Vector2DAdd(&vout, &v1, &v2);
		EXPECT_FLOAT_EQ(4.0f, vout.x);
		EXPECT_FLOAT_EQ(6.0f, vout.y);
	}

	RC_GTEST_PROP(Vector2DPropertyTests, Vector2DAddRandom, (float x1, float y1, float x2, float y2))
	{
		Vector2D v1 = { x1, y1 };
		Vector2D v2 = { x2, y2 };
		Vector2D vout;
		Vector2DAdd(&vout, &v1, &v2);
		RC_ASSERT(vout.x == x1 + x2);
		RC_ASSERT(vout.y == y1 + y2);
	}

	TEST(Vector2DUnitTests, AddVectorsInPlace)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2DAdd(&v1, &v1, &v2);
		EXPECT_FLOAT_EQ(4.0f, v1.x);
		EXPECT_FLOAT_EQ(6.0f, v1.y);
	}

	TEST(Vector2DUnitTests, Vector2DSub)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 10.0f, 15.0f };
		Vector2D vout;
		Vector2DSub(&vout, &v1, &v2);
		EXPECT_FLOAT_EQ(-9.0f, vout.x);
		EXPECT_FLOAT_EQ(-13.0f, vout.y);
	}

	RC_GTEST_PROP(Vector2DPropertyTests, Vector2DSubRandom, (float x1, float y1, float x2, float y2))
	{
		Vector2D v1 = { x1, y1 };
		Vector2D v2 = { x2, y2 };
		Vector2D vout;
		Vector2DSub(&vout, &v1, &v2);
		RC_ASSERT(vout.x == x1 - x2);
		RC_ASSERT(vout.y == y1 - y2);
	}

	TEST(Vector2DUnitTests, Vector2DNormalize)
	{
		Vector2D vin = { 10.0f, 20.0f };
		Vector2D vout;
		Vector2DNormalize(&vout, &vin);
		EXPECT_FLOAT_EQ(0.4472136f, vout.x);
		EXPECT_FLOAT_EQ(0.8944272f, vout.y);
	}

	/*
	RC_GTEST_PROP(Vector2DPropertyTests, Vector2DNormalizeRandom, (float x, float y))
	{
		Vector2D vin = { x, y };
		Vector2D vout;
		Vector2DNormalize(&vout, &vin);
		float length = sqrtf(x * x + y * y);
		RC_ASSERT(vout.x == x / length);
		RC_ASSERT(vout.y == y / length);
	}
	*/

	TEST(Vector2DUnitTests, Vector2DScale)
	{
		Vector2D v = { 1.0f, 2.0f };
		Vector2D vout;
		Vector2DScale(&vout, &v, 2.0f);
		EXPECT_FLOAT_EQ(2.0f, vout.x);
		EXPECT_FLOAT_EQ(4.0f, vout.y);
	}

	RC_GTEST_PROP(Vector2DPropertyTests, Vector2DScaleRandom, (float x, float y))
	{
		Vector2D v = { x, y };
		Vector2D vout;
		float scale = *rc::gen::nonNegative<float>();

		std::cout << "x: " << x << " y: " << y << " scale: " << scale << std::endl;

		Vector2DScale(&vout, &v, scale);
		RC_ASSERT(vout.x == x * scale);
		RC_ASSERT(vout.y == y * scale);
	}

	TEST(Vector2DUnitTests, Vector2DScaleAdd)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2D vout;
		Vector2DScaleAdd(&vout, &v1, 2.0f, &v2);
		EXPECT_FLOAT_EQ(5.0f, vout.x);
		EXPECT_FLOAT_EQ(8.0f, vout.y);
	}

	TEST(Vector2DUnitTests, Vector2DScaleSub)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		Vector2D vout;
		Vector2DScaleSub(&vout, &v1, 2.0f, &v2);
		EXPECT_FLOAT_EQ(-1.0f, vout.x);
		EXPECT_FLOAT_EQ(0.0f, vout.y);
	}

	TEST(Vector2DUnitTests, Vector2DLength)
	{
		Vector2D v = { 1.0f, 2.0f };
		float length = Vector2DLength(&v);
		EXPECT_FLOAT_EQ(2.236068f, length);
	}

	TEST(Vector2DUnitTests, Vector2DSquareLength)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		float lengthSquared = Vector2DSquareLength(&v1);
		EXPECT_FLOAT_EQ(5.0f, lengthSquared);
	}

	TEST(Vector2DUnitTests, Vector2DDistance)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		float distance = Vector2DDistance(&v1, &v2);
		EXPECT_FLOAT_EQ(2.828427f, distance);
	}

	TEST(Vector2DUnitTests, Vector2DSquareDistance)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		float distanceSquared = Vector2DSquareDistance(&v1, &v2);
		EXPECT_FLOAT_EQ(8.0f, distanceSquared);
	}

	TEST(Vector2DUnitTests, Vector2DDotProduct)
	{
		Vector2D v1 = { 1.0f, 2.0f };
		Vector2D v2 = { 3.0f, 4.0f };
		float dotProduct = Vector2DDotProduct(&v1, &v2);
		EXPECT_FLOAT_EQ(11.0f, dotProduct);
	}

	TEST(Vector2DUnitTests, Vector2DFromAngleDeg)
	{
		Vector2D v;
		Vector2DFromAngleDeg(&v, 30.0f);
		EXPECT_FLOAT_EQ(0.8660254f, v.x);
		EXPECT_FLOAT_EQ(0.5f, v.y);
	}

	TEST(Vector2DUnitTests, Vector2DFromAngleRad)
	{
		Vector2D v;
		Vector2DFromAngleRad(&v, M_PI / 6.0f);
		EXPECT_FLOAT_EQ(0.8660254f, v.x);
		EXPECT_FLOAT_EQ(0.5f, v.y);
	}

	TEST(Vector2DUnitTests, Vector2DToAngleRad)
	{
		Vector2D v = { 0.8660254f, 0.5f };
		float angle = Vector2DToAngleRad(&v);
		EXPECT_FLOAT_EQ(0.5235988f, angle);
	}
}