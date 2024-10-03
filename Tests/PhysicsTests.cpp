#include <gtest/gtest.h>
#include "Physics.h"
#include "Vector2D.h"
#include "Stream.h"

namespace PhysicsTests
{
	TEST(PhysicsCreateAndFreeTests, BasicCreateAndFree)
	{
		Physics* physics = PhysicsCreate();
		ASSERT_NE(physics, nullptr);

		const Vector2D* oldTranslation = PhysicsGetOldTranslation(physics);
		ASSERT_NE(oldTranslation, nullptr);
		EXPECT_EQ(oldTranslation->x, 0.0f);
		EXPECT_EQ(oldTranslation->y, 0.0f);

		const Vector2D* acceleration = PhysicsGetAcceleration(physics);
		ASSERT_NE(acceleration, nullptr);
		EXPECT_EQ(acceleration->x, 0.0f);
		EXPECT_EQ(acceleration->y, 0.0f);

		const Vector2D* velocity = PhysicsGetVelocity(physics);
		ASSERT_NE(velocity, nullptr);
		EXPECT_EQ(velocity->x, 0.0f);
		EXPECT_EQ(velocity->y, 0.0f);

		PhysicsFree(&physics);
		ASSERT_EQ(physics, nullptr);
	}

	TEST(PhysicsCreateAndFreeTests, NullFree)
	{
		Physics* physics = nullptr;
		PhysicsFree(&physics);
		ASSERT_EQ(physics, nullptr);
	}

	TEST(PhysicsCreateAndFreeTests, DoubleFree)
	{
		Physics* physics = PhysicsCreate();
		PhysicsFree(&physics);
		PhysicsFree(&physics);
		ASSERT_EQ(physics, nullptr);
	}

	TEST(PhysicsReadTests, ReadPhysics)
	{
		Physics* physics = PhysicsCreate();
		ASSERT_NE(physics, nullptr);

		Stream stream = StreamOpen("TestData/PhysicsRead_data.txt");
		ASSERT_NE(stream, nullptr);

		PhysicsRead(physics, stream);

		const Vector2D* acceleration = PhysicsGetAcceleration(physics);
		ASSERT_NE(acceleration, nullptr);
		EXPECT_EQ(acceleration->x, 1.0f);
		EXPECT_EQ(acceleration->y, 2.0f);

		const Vector2D* velocity = PhysicsGetVelocity(physics);
		ASSERT_NE(velocity, nullptr);
		EXPECT_EQ(velocity->x, 3.0f);
		EXPECT_EQ(velocity->y, 4.0f);

		PhysicsFree(&physics);
		StreamClose(&stream);
	}

	TEST(PhysicsMemberTests, SetAllAndGet)
	{
		Physics* physics = PhysicsCreate();
		ASSERT_NE(physics, nullptr);

		// Set the values
		Vector2D acceleration = { 1.0f, 2.0f };
		PhysicsSetAcceleration(physics, &acceleration);
		const Vector2D* accelerationResult = PhysicsGetAcceleration(physics);

		Vector2D velocity = { 3.0f, 4.0f };
		PhysicsSetVelocity(physics, &velocity);
		const Vector2D* velocityResult = PhysicsGetVelocity(physics);

		// Check if the values are set correctly
		EXPECT_NE(accelerationResult, nullptr);
		if (accelerationResult)
		{
			EXPECT_EQ(accelerationResult->x, 1.0f);
			EXPECT_EQ(accelerationResult->y, 2.0f);
		}

		EXPECT_NE(velocityResult, nullptr);
		if (velocityResult)
		{
			EXPECT_EQ(velocityResult->x, 3.0f);
			EXPECT_EQ(velocityResult->y, 4.0f);
		}

		PhysicsFree(&physics);
		ASSERT_EQ(physics, nullptr);
	}

	TEST(PhysicsMemberTests, GetAccelerationNull)
	{
		const Vector2D* acceleration = PhysicsGetAcceleration(nullptr);
		EXPECT_EQ(acceleration, nullptr);
	}

	TEST(PhysicsMemberTests, GetVelocityNull)
	{
		const Vector2D* velocity = PhysicsGetVelocity(nullptr);
		EXPECT_EQ(velocity, nullptr);
	}

	TEST(PhysicsMemberTests, GetOldTranslationNull)
	{
		const Vector2D* oldTranslation = PhysicsGetOldTranslation(nullptr);
		EXPECT_EQ(oldTranslation, nullptr);
	}
}

// ------------------------------------------------------------------------------

#include "Transform.h"

namespace PhysicsWithTransformTests
{
	class PhysicsWithTransformTest : public ::testing::Test
	{
	protected:
		Physics* physics;
		Transform* transform;

		void SetUp() override
		{
			physics = PhysicsCreate();
			transform = TransformCreate();
		}

		void TearDown() override
		{
			PhysicsFree(&physics);
			TransformFree(&transform);
		}
	};

	TEST_F(PhysicsWithTransformTest, UpdatePhysics)
	{
		Vector2D acceleration = { 1.0f, 2.0f };
		PhysicsSetAcceleration(physics, &acceleration);

		// Tick 1
		PhysicsUpdate(physics, transform, 1.0f);

		const Vector2D* oldTranslation = PhysicsGetOldTranslation(physics);
		ASSERT_NE(oldTranslation, nullptr);
		EXPECT_EQ(oldTranslation->x, 0.0f);
		EXPECT_EQ(oldTranslation->y, 0.0f);

		const Vector2D* translation = TransformGetTranslation(transform);
		ASSERT_NE(translation, nullptr);
		EXPECT_EQ(translation->x, 1.0f);
		EXPECT_EQ(translation->y, 2.0f);

		const Vector2D* velocity = PhysicsGetVelocity(physics);
		ASSERT_NE(velocity, nullptr);
		EXPECT_EQ(velocity->x, 1.0f);
		EXPECT_EQ(velocity->y, 2.0f);

		// Tick 2
		PhysicsUpdate(physics, transform, 1.0f);

		oldTranslation = PhysicsGetOldTranslation(physics);
		ASSERT_NE(oldTranslation, nullptr);
		EXPECT_EQ(oldTranslation->x, 1.0f);
		EXPECT_EQ(oldTranslation->y, 2.0f);

		translation = TransformGetTranslation(transform);
		ASSERT_NE(translation, nullptr);
		EXPECT_EQ(translation->x, 3.0f);
		EXPECT_EQ(translation->y, 6.0f);

		velocity = PhysicsGetVelocity(physics);
		ASSERT_NE(velocity, nullptr);
		EXPECT_EQ(velocity->x, 2.0f);
		EXPECT_EQ(velocity->y, 4.0f);
	}
}