#include <gtest/gtest.h>
#include "Sprite.h"

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
}