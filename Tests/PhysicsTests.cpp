#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include "Physics.h"
#include "Vector2D.h"
#include "Stream.h"

namespace PhysicsTests
{
	TEST(PhysicsUnitTests, CreateAndFree)
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

	TEST(PhysicsUnitTests, NullFree)
	{
		Physics* physics = nullptr;
		PhysicsFree(&physics);
		ASSERT_EQ(physics, nullptr);
	}

	TEST(PhysicsUnitTests, DoubleFree)
	{
		Physics* physics = PhysicsCreate();
		PhysicsFree(&physics);
		PhysicsFree(&physics);
		ASSERT_EQ(physics, nullptr);
	}

	TEST(PhysicsUnitTests, ReadPhysics)
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

	TEST(PhysicsUnitTests, SetAllAndGet)
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

	RC_GTEST_PROP(PhysicsPropertyTests, PhysicsSetRandom, (bool setAcceleration, bool setVelocity, bool setRotationalVelocity))
	{
		Physics* physics = PhysicsCreate();
		RC_ASSERT(physics);

		Vector2D acceleration, velocity;
		float rotationalVelocity;
		if (setAcceleration)
		{
			acceleration = { *rc::gen::arbitrary<float>(), *rc::gen::arbitrary<float>() };
			PhysicsSetAcceleration(physics, &acceleration);
		}

		if (setVelocity)
		{
			velocity = { *rc::gen::arbitrary<float>(), *rc::gen::arbitrary<float>() };
			PhysicsSetVelocity(physics, &velocity);
		}

		if (setRotationalVelocity)
		{
			rotationalVelocity = *rc::gen::arbitrary<float>();
			PhysicsSetRotationalVelocity(physics, rotationalVelocity);
		}

		const Vector2D* accelerationResult = PhysicsGetAcceleration(physics);
		RC_ASSERT(accelerationResult);
		RC_ASSERT(accelerationResult->x == (setAcceleration ? acceleration.x : 0.0f));
		RC_ASSERT(accelerationResult->y == (setAcceleration ? acceleration.y : 0.0f));

		const Vector2D* velocityResult = PhysicsGetVelocity(physics);
		RC_ASSERT(velocityResult);
		RC_ASSERT(velocityResult->x == (setVelocity ? velocity.x : 0.0f));
		RC_ASSERT(velocityResult->y == (setVelocity ? velocity.y : 0.0f));

		float rotationalVelocityResult = PhysicsGetRotationalVelocity(physics);
		RC_ASSERT(rotationalVelocityResult == (setRotationalVelocity ? rotationalVelocity : 0.0f));

		PhysicsFree(&physics);
		RC_ASSERT(!physics);
	}

	TEST(PhysicsUnitTests, GetAccelerationNull)
	{
		const Vector2D* acceleration = PhysicsGetAcceleration(nullptr);
		EXPECT_EQ(acceleration, nullptr);
	}

	TEST(PhysicsUnitTests, GetVelocityNull)
	{
		const Vector2D* velocity = PhysicsGetVelocity(nullptr);
		EXPECT_EQ(velocity, nullptr);
	}

	TEST(PhysicsUnitTests, GetOldTranslationNull)
	{
		const Vector2D* oldTranslation = PhysicsGetOldTranslation(nullptr);
		EXPECT_EQ(oldTranslation, nullptr);
	}

	TEST(PhysicsUnitTests, GetRotationalVelocityNull)
	{
		float rotationalVelocity = PhysicsGetRotationalVelocity(nullptr);
		EXPECT_FLOAT_EQ(rotationalVelocity, 0.0f);
	}

	TEST(PhysicsUnitTests, Clone)
	{
		Physics* physics = PhysicsCreate();
		ASSERT_NE(physics, nullptr);

		Vector2D acceleration = { 1.0f, 2.0f };
		Vector2D velocity = { 3.0f, 4.0f };
		float rotationalVelocity = 5.0f;
		PhysicsSetAcceleration(physics, &acceleration);
		PhysicsSetVelocity(physics, &velocity);
		PhysicsSetRotationalVelocity(physics, rotationalVelocity);

		Physics* clone = PhysicsClone(physics);
		ASSERT_NE(clone, nullptr);
		EXPECT_EQ(PhysicsGetAcceleration(clone)->x, acceleration.x);
		EXPECT_EQ(PhysicsGetAcceleration(clone)->y, acceleration.y);
		EXPECT_EQ(PhysicsGetVelocity(clone)->x, velocity.x);
		EXPECT_EQ(PhysicsGetVelocity(clone)->y, velocity.y);
		EXPECT_FLOAT_EQ(PhysicsGetRotationalVelocity(clone), rotationalVelocity);

		Vector2D newAcceleration_original = { 6.0f, 7.0f };
		Vector2D newVelocity_original = { 8.0f, 9.0f };
		float newRotationalVelocity_original = 10.0f;
		Vector2D newAcceleration_clone = { 11.0f, 12.0f };
		Vector2D newVelocity_clone = { 13.0f, 14.0f };
		float newRotationalVelocity_clone = 15.0f;

		PhysicsSetAcceleration(physics, &newAcceleration_original);
		PhysicsSetVelocity(physics, &newVelocity_original);
		PhysicsSetRotationalVelocity(physics, newRotationalVelocity_original);

		PhysicsSetAcceleration(clone, &newAcceleration_clone);
		PhysicsSetVelocity(clone, &newVelocity_clone);
		PhysicsSetRotationalVelocity(clone, newRotationalVelocity_clone);

		EXPECT_EQ(PhysicsGetAcceleration(physics)->x, newAcceleration_original.x);
		EXPECT_EQ(PhysicsGetAcceleration(physics)->y, newAcceleration_original.y);
		EXPECT_EQ(PhysicsGetVelocity(physics)->x, newVelocity_original.x);
		EXPECT_EQ(PhysicsGetVelocity(physics)->y, newVelocity_original.y);
		EXPECT_FLOAT_EQ(PhysicsGetRotationalVelocity(physics), newRotationalVelocity_original);

		EXPECT_EQ(PhysicsGetAcceleration(clone)->x, newAcceleration_clone.x);
		EXPECT_EQ(PhysicsGetAcceleration(clone)->y, newAcceleration_clone.y);
		EXPECT_EQ(PhysicsGetVelocity(clone)->x, newVelocity_clone.x);
		EXPECT_EQ(PhysicsGetVelocity(clone)->y, newVelocity_clone.y);
		EXPECT_FLOAT_EQ(PhysicsGetRotationalVelocity(clone), newRotationalVelocity_clone);

		PhysicsFree(&physics);
		EXPECT_EQ(physics, nullptr);
		EXPECT_NE(clone, nullptr);
		PhysicsFree(&clone);
		ASSERT_EQ(clone, nullptr);
	}

	TEST(PhysicsUnitTests, CloneNull)
	{
		Physics* clone = PhysicsClone(nullptr);
		EXPECT_EQ(clone, nullptr);
	}

	RC_GTEST_PROP(PhysicsPropertyTests, PhysicsCloneRandom, (bool setAcceleration, bool setVelocity, bool setRotationalVelocity))
	{
		Physics* physics = PhysicsCreate();
		RC_ASSERT(physics);

		Vector2D acceleration, velocity;
		float rotationalVelocity;
		if (setAcceleration)
		{
			acceleration = { *rc::gen::arbitrary<float>(), *rc::gen::arbitrary<float>() };
			PhysicsSetAcceleration(physics, &acceleration);
		}

		if (setVelocity)
		{
			velocity = { *rc::gen::arbitrary<float>(), *rc::gen::arbitrary<float>() };
			PhysicsSetVelocity(physics, &velocity);
		}

		if (setRotationalVelocity)
		{
			rotationalVelocity = *rc::gen::arbitrary<float>();
			PhysicsSetRotationalVelocity(physics, rotationalVelocity);
		}

		Physics* clone = PhysicsClone(physics);
		RC_ASSERT(clone);

		const Vector2D* accelerationResult = PhysicsGetAcceleration(clone);
		RC_ASSERT(accelerationResult);
		RC_ASSERT(accelerationResult->x == (setAcceleration ? acceleration.x : 0.0f));
		RC_ASSERT(accelerationResult->y == (setAcceleration ? acceleration.y : 0.0f));

		const Vector2D* velocityResult = PhysicsGetVelocity(clone);
		RC_ASSERT(velocityResult);
		RC_ASSERT(velocityResult->x == (setVelocity ? velocity.x : 0.0f));
		RC_ASSERT(velocityResult->y == (setVelocity ? velocity.y : 0.0f));

		float rotationalVelocityResult = PhysicsGetRotationalVelocity(clone);
		RC_ASSERT(rotationalVelocityResult == (setRotationalVelocity ? rotationalVelocity : 0.0f));

		PhysicsFree(&physics);
		RC_ASSERT(!physics);
		PhysicsFree(&clone);
		RC_ASSERT(!clone);
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
		float rotationalVelocity = 3.0f;
		PhysicsSetAcceleration(physics, &acceleration);
		PhysicsSetRotationalVelocity(physics, rotationalVelocity);

		// Tick 1
		PhysicsUpdate(physics, transform, 1.0f);

		const Vector2D* oldTranslation = PhysicsGetOldTranslation(physics);
		EXPECT_EQ(oldTranslation->x, 0.0f);
		EXPECT_EQ(oldTranslation->y, 0.0f);

		const Vector2D* translation = TransformGetTranslation(transform);
		EXPECT_EQ(translation->x, 1.0f);
		EXPECT_EQ(translation->y, 2.0f);

		const Vector2D* velocity = PhysicsGetVelocity(physics);
		EXPECT_EQ(velocity->x, 1.0f);
		EXPECT_EQ(velocity->y, 2.0f);

		EXPECT_EQ(TransformGetRotation(transform), 3.0f);

		// Tick 2
		PhysicsUpdate(physics, transform, 1.0f);

		oldTranslation = PhysicsGetOldTranslation(physics);
		EXPECT_EQ(oldTranslation->x, 1.0f);
		EXPECT_EQ(oldTranslation->y, 2.0f);

		translation = TransformGetTranslation(transform);
		EXPECT_EQ(translation->x, 3.0f);
		EXPECT_EQ(translation->y, 6.0f);

		velocity = PhysicsGetVelocity(physics);
		EXPECT_EQ(velocity->x, 2.0f);
		EXPECT_EQ(velocity->y, 4.0f);

		EXPECT_EQ(TransformGetRotation(transform), 6.0f);
	}

	RC_GTEST_FIXTURE_PROP(PhysicsWithTransformTest, UpdatePhysicsRandom, (float ax, float ay, float rot))
	{
		Vector2D acceleration = { ax, ay };
		PhysicsSetAcceleration(physics, &acceleration);
		PhysicsSetRotationalVelocity(physics, rot);

		// tick 1
		float dt = *rc::gen::positive<float>();
		dt = fmodf(dt, 1.0f); // dt should always be very small - between 0 and 1
		PhysicsUpdate(physics, transform, dt);

		Vector2D oldTranslation_t1 = { 0.0f, 0.0f };
		memcpy_s(&oldTranslation_t1, sizeof(Vector2D), PhysicsGetOldTranslation(physics), sizeof(Vector2D));
		RC_ASSERT(oldTranslation_t1.x == 0.0f);
		RC_ASSERT(oldTranslation_t1.y == 0.0f);

		Vector2D velocity_t1 = { 0.0f, 0.0f };
		memcpy_s(&velocity_t1, sizeof(Vector2D), PhysicsGetVelocity(physics), sizeof(Vector2D));
		RC_ASSERT(velocity_t1.x == acceleration.x * dt);
		RC_ASSERT(velocity_t1.y == acceleration.y * dt);

		Vector2D translation_t1 = { 0.0f, 0.0f };
		memcpy_s(&translation_t1, sizeof(Vector2D), TransformGetTranslation(transform), sizeof(Vector2D));
		RC_ASSERT(translation_t1.x == velocity_t1.x * dt);
		RC_ASSERT(translation_t1.y == velocity_t1.y * dt);

		const float rotation_t1 = TransformGetRotation(transform);
		RC_ASSERT(rotation_t1 == rot * dt);

		// tick 2
		dt = *rc::gen::positive<float>();
		dt = fmodf(dt, 1.0f);
		PhysicsUpdate(physics, transform, dt);

		const Vector2D* oldTranslation_t2 = PhysicsGetOldTranslation(physics);
		RC_ASSERT(oldTranslation_t2->x == translation_t1.x);
		RC_ASSERT(oldTranslation_t2->y == translation_t1.y);

		const Vector2D* velocity_t2 = PhysicsGetVelocity(physics);
		RC_ASSERT(velocity_t2->x == velocity_t1.x + acceleration.x * dt);
		RC_ASSERT(velocity_t2->y == velocity_t1.y + acceleration.y * dt);

		const Vector2D* translation_t2 = TransformGetTranslation(transform);
		RC_ASSERT(translation_t2->x == translation_t1.x + velocity_t2->x * dt);
		RC_ASSERT(translation_t2->y == translation_t1.y + velocity_t2->y * dt);

		const float rotation_t2 = TransformGetRotation(transform);
		RC_ASSERT(rotation_t2 == rotation_t1 + rot * dt);
	}
}