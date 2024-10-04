#include <gtest/gtest.h>
#include "Sprite.h"
#include "Stream.h"

namespace SpriteTests
{
	TEST(SpriteCreateAndFreeTests, BasicCreateAndFree)
	{
		Sprite* sprite = SpriteCreate();
		ASSERT_NE(sprite, nullptr);

		float alpha = SpriteGetAlpha(sprite);
		EXPECT_EQ(alpha, 1.0f);

		SpriteFree(&sprite);
		ASSERT_EQ(sprite, nullptr);
	}

	TEST(SpriteCreateAndFreeTests, NullFree)
	{
		Sprite* sprite = nullptr;
		SpriteFree(&sprite);
		ASSERT_EQ(sprite, nullptr);
	}

	TEST(SpriteCreateAndFreeTests, DoubleFree)
	{
		Sprite* sprite = SpriteCreate();
		SpriteFree(&sprite);
		SpriteFree(&sprite);
		ASSERT_EQ(sprite, nullptr);
	}

	TEST(SpriteReadTests, ReadSprite)
	{
		Sprite* sprite = SpriteCreate();
		ASSERT_NE(sprite, nullptr);

		Stream stream = StreamOpen("TestData/SpriteRead_data.txt");
		ASSERT_NE(stream, nullptr);

		SpriteRead(sprite, stream);
		float alpha = SpriteGetAlpha(sprite);
		EXPECT_EQ(alpha, 0.3f);

		StreamClose(&stream);
		ASSERT_EQ(stream, nullptr);
		SpriteFree(&sprite);
		ASSERT_EQ(sprite, nullptr);
	}

	TEST(SpriteAlphaTests, SetAlphaAndGet)
	{
		Sprite* sprite = SpriteCreate();
		ASSERT_NE(sprite, nullptr);

		SpriteSetAlpha(sprite, 0.5f);
		float alpha = SpriteGetAlpha(sprite);
		EXPECT_EQ(alpha, 0.5f);

		SpriteFree(&sprite);
		ASSERT_EQ(sprite, nullptr);
	}
}