#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include "Random.h"
#include <iostream>

namespace RandomTests
{
	TEST(RandomUnitTests, RandomRange)
	{
		RandomInit();
		int rangeMin = 0;
		int rangeMax = 10;
		for (int i = 0; i < 10000; ++i)
		{
			int random = RandomRange(rangeMin, rangeMax);
			EXPECT_GE(random, rangeMin);
			EXPECT_LE(random, rangeMax);
		}

		rangeMin = -10;
		rangeMax = 0;
		for (int i = 0; i < 10000; ++i)
		{
			int random = RandomRange(rangeMin, rangeMax);
			EXPECT_GE(random, rangeMin);
			EXPECT_LE(random, rangeMax);
		}

		rangeMin = -1000;
		rangeMax = 1000;
		for (int i = 0; i < 10000; ++i)
		{
			int random = RandomRange(rangeMin, rangeMax);
			EXPECT_GE(random, rangeMin);
			EXPECT_LE(random, rangeMax);
		}

		rangeMin = 0;
		rangeMax = 0;
		for (int i = 0; i < 10000; ++i)
		{
			int random = RandomRange(rangeMin, rangeMax);
			EXPECT_EQ(random, rangeMin);
		}

		rangeMin = 0;
		rangeMax = 1;
	}

	TEST(RandomUnitTests, RandomRangeFloat)
	{
		RandomInit();
		float rangeMin = 0.0f;
		float rangeMax = 10.0f;
		for (int i = 0; i < 10000; ++i)
		{
			float random = RandomRangeFloat(rangeMin, rangeMax);
			EXPECT_GE(random, rangeMin);
			EXPECT_LE(random, rangeMax);
		}

		rangeMin = -10.0f;
		rangeMax = 0.0f;
		for (int i = 0; i < 10000; ++i)
		{
			float random = RandomRangeFloat(rangeMin, rangeMax);
			EXPECT_GE(random, rangeMin);
			EXPECT_LE(random, rangeMax);
		}

		rangeMin = -1000.0f;
		rangeMax = 1000.0f;
		for (int i = 0; i < 10000; ++i)
		{
			float random = RandomRangeFloat(rangeMin, rangeMax);
			EXPECT_GE(random, rangeMin);
			EXPECT_LE(random, rangeMax);
		}

		rangeMin = 0.0f;
		rangeMax = 0.0f;
		for (int i = 0; i < 10000; ++i)
		{
			float random = RandomRangeFloat(rangeMin, rangeMax);
			EXPECT_EQ(random, rangeMin);
		}

		rangeMin = 0.0f;
		rangeMax = 1.0f;
	}
}