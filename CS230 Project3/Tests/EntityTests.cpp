#include <gtest/gtest.h>
#include "Entity.h"
//#include "Animation.h"
#include "Physics.h"
#include "Sprite.h"
#include "Transform.h"

namespace EntityTests
{
	TEST(EntityTests, EntityCreateAndFree)
	{
		Entity* entity = EntityCreate();
		ASSERT_NE(entity, nullptr);

		//EXPECT_EQ(EntityGetAnimation(entity), nullptr);
		EXPECT_EQ(EntityGetPhysics(entity), nullptr);
		EXPECT_EQ(EntityGetSprite(entity), nullptr);
		EXPECT_EQ(EntityGetTransform(entity), nullptr);
		//EXPECT_EQ(EntityGetName(entity), nullptr);

		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);
	}

	TEST(EntityTests, EntityFree_Null)
	{
		Entity* entity = nullptr;
		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);
	}

	TEST(EntityTests, EntityFree_Double)
	{
		Entity* entity = EntityCreate();
		ASSERT_NE(entity, nullptr);

		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);

		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);
	}

	TEST(EntityTests, EntityAddGetPhysics)
	{
		Entity* entity = EntityCreate();
		ASSERT_NE(entity, nullptr);

		Physics* physics = PhysicsCreate();
		ASSERT_NE(physics, nullptr);

		EntityAddPhysics(entity, physics);
		ASSERT_EQ(EntityGetPhysics(entity), physics);

		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);
	}

	TEST(EntityTests, EntityAddGetPhysics_NullEntity)
	{
		Physics* physics = PhysicsCreate();
		ASSERT_NE(physics, nullptr);

		ASSERT_NO_THROW(EntityAddPhysics(nullptr, physics));
		ASSERT_NO_THROW(EntityGetPhysics(nullptr));
		ASSERT_EQ(EntityGetPhysics(nullptr), nullptr);
	}

	TEST(EntityTests, EntityAddGetSprite)
	{
		Entity* entity = EntityCreate();
		ASSERT_NE(entity, nullptr);

		Sprite* sprite = SpriteCreate();
		ASSERT_NE(sprite, nullptr);

		EntityAddSprite(entity, sprite);
		ASSERT_EQ(EntityGetSprite(entity), sprite);

		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);
	}

	TEST(EntityTests, EntityAddGetTransform)
	{
		Entity* entity = EntityCreate();
		ASSERT_NE(entity, nullptr);

		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		EntityAddTransform(entity, transform);
		ASSERT_EQ(EntityGetTransform(entity), transform);

		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);
	}

	TEST(EntityTests, EntitySetName)
	{
		Entity* entity = EntityCreate();
		ASSERT_NE(entity, nullptr);

		const char* name = "TestName";
		EntitySetName(entity, name);
		EXPECT_STREQ(EntityGetName(entity), name);

		EntityFree(&entity);
		ASSERT_EQ(entity, nullptr);
	}
}

