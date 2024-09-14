#include <gtest/gtest.h>
#include "Animation.h"
#include "Stream.h"

namespace AnimationTests
{
	TEST(AnimationCreateAndFreeTests, BasicCreateAndFree)
	{
		Animation* animation = AnimationCreate();
		ASSERT_NE(animation, nullptr);

		AnimationFree(&animation);
		ASSERT_EQ(animation, nullptr);
	}

	TEST(AnimationCreateAndFreeTests, NullFree)
	{
		Animation* animation = nullptr;
		AnimationFree(&animation);
		ASSERT_EQ(animation, nullptr);
	}

	TEST(AnimationCreateAndFreeTests, DoubleFree)
	{
		Animation* animation = AnimationCreate();
		AnimationFree(&animation);
		AnimationFree(&animation);
		ASSERT_EQ(animation, nullptr);
	}

	/*TEST(AnimationReadTests, BasicRead)
	{
		Animation* animation = AnimationCreate();
		ASSERT_NE(animation, nullptr);

		Stream stream = StreamOpen("TestData/AnimationRead_data.txt");
		ASSERT_NE(stream, nullptr);

		AnimationRead(animation, stream);

		StreamClose(&stream);
		ASSERT_EQ(stream, nullptr);
		AnimationFree(&animation);
		ASSERT_EQ(animation, nullptr);
	}*/

	/*
	TEST(AnimationPlayTests, PlayAndUpdateOneFrame)
	{
		Animation* animation = AnimationCreate();
		ASSERT_NE(animation, nullptr);

		AnimationPlay(animation, 1, 1.0f, false);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.9f);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.2f);
		ASSERT_EQ(AnimationIsDone(animation), true);

		AnimationUpdate(animation, 0.2f);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationFree(&animation);
		ASSERT_EQ(animation, nullptr);
	}

	TEST(AnimationPlayTests, PlayAndUpdateTwoFrames)
	{
		Animation* animation = AnimationCreate();
		ASSERT_NE(animation, nullptr);

		AnimationPlay(animation, 2, 1.0f, false);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.9f);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.2f);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.8f);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.2f);
		ASSERT_EQ(AnimationIsDone(animation), true);

		AnimationUpdate(animation, 0.2f);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationFree(&animation);
		ASSERT_EQ(animation, nullptr);
	}
	*/
}