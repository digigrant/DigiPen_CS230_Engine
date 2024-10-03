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

	/*
	TEST(AnimationReadTests, BasicRead)
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
	}
	*/
}

// ------------------------------------------------------------------------------

#include "Entity.h"
#include "Sprite.h"
#include "SpriteSource.h"

namespace
{
	class AnimationOnEntityTest : public testing::Test
	{
	protected:
		Entity* entity;
		Sprite* sprite;
		SpriteSource* sprite_source;
		Animation* animation;

		AnimationOnEntityTest() : entity(nullptr), sprite(nullptr), sprite_source(nullptr), animation(nullptr) {}

		void SetUp() override
		{
			entity = EntityCreate();
			sprite = SpriteCreate();
			sprite_source = SpriteSourceCreate();
			animation = AnimationCreate();

			SpriteSetSpriteSource(sprite, sprite_source);
			EntityAddSprite(entity, sprite);
			EntityAddAnimation(entity, animation);
		}

		void TearDown() override
		{
			SpriteSourceFree(&sprite_source);
			EntityFree(&entity);	// Frees sprite and animation
			// For some reason freeing sprite and animation separately caused a heap corruption (memory at freed location would be 0xfeeefeee)
		}
	};
}

namespace AnimationOnEntityTests
{
	TEST_F(AnimationOnEntityTest, AnimationOnEntityCreateAndFree)
	{
		ASSERT_NE(entity, nullptr);
		ASSERT_NE(sprite, nullptr);
		ASSERT_NE(sprite_source, nullptr);
		ASSERT_NE(animation, nullptr);
	}

	TEST_F(AnimationOnEntityTest, AnimationOnEntityPlayOneFrame)
	{
		AnimationPlay(animation, 1, 1.0f, false);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.9f);
		ASSERT_EQ(AnimationIsDone(animation), false);

		AnimationUpdate(animation, 0.2f);
		ASSERT_EQ(AnimationIsDone(animation), true);

		AnimationUpdate(animation, 0.2f);
		ASSERT_EQ(AnimationIsDone(animation), false);
	}

	/* TODO - Fix this test - requires loading a sprite source from a file, which means DGL has to be initialized first
	TEST_F(AnimationOnEntityTest, AnimationOnEntityPlayTwoFrames)
	{
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
	}
	*/
}