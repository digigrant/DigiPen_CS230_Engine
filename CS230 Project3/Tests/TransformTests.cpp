#include <gtest/gtest.h>
#include "Transform.h"
#include "Vector2D.h"
#include "Matrix2D.h"

namespace TransformTests
{
	TEST(TransformCreateAndFreeTests, BasicCreateAndFree)
	{
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		const Vector2D* translation = TransformGetTranslation(transform);
		ASSERT_NE(translation, nullptr);
		EXPECT_EQ(translation->x, 0.0f);
		EXPECT_EQ(translation->y, 0.0f);

		float rotation = TransformGetRotation(transform);
		EXPECT_EQ(rotation, 0.0f);

		const Vector2D* scale = TransformGetScale(transform);
		ASSERT_NE(scale, nullptr);
		EXPECT_EQ(scale->x, 1.0f);
		EXPECT_EQ(scale->y, 1.0f);

		TransformFree(&transform);
		ASSERT_EQ(transform, nullptr);
	}

	TEST(TransformCreateAndFreeTests, NullFree)
	{
		Transform* transform = nullptr;
		TransformFree(&transform);
		ASSERT_EQ(transform, nullptr);
	}

	TEST(TransformCreateAndFreeTests, DoubleFree)
	{
		Transform* transform = TransformCreate();
		TransformFree(&transform);
		TransformFree(&transform);
		ASSERT_EQ(transform, nullptr);
	}

	TEST(TransformMemberTests, SetTranslationAndGet)
	{
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		Vector2D translation = { 1.0f, 2.0f };
		TransformSetTranslation(transform, &translation);

		const Vector2D* result = TransformGetTranslation(transform);
		ASSERT_NE(result, nullptr);
		EXPECT_EQ(result->x, translation.x);
		EXPECT_EQ(result->y, translation.y);

		TransformFree(&transform);
	}

	TEST(TransformMemberTests, GetTranslationNull)
	{
		const Vector2D* result = TransformGetTranslation(nullptr);
		EXPECT_EQ(result, nullptr);
	}

	TEST(TransformMemberTests, SetRotationAndGet)
	{
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		float rotation = 1.0f;
		TransformSetRotation(transform, rotation);

		float result = TransformGetRotation(transform);
		EXPECT_EQ(result, rotation);

		TransformFree(&transform);
	}

	TEST(TransformMemberTests, GetRotationNull)
	{
		float result = TransformGetRotation(nullptr);
		EXPECT_EQ(result, 0.0f);
	}

	TEST(TransformMemberTests, SetScaleAndGet)
	{
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		Vector2D scale = { 1.0f, 2.0f };
		TransformSetScale(transform, &scale);

		const Vector2D* result = TransformGetScale(transform);
		ASSERT_NE(result, nullptr);
		EXPECT_EQ(result->x, scale.x);
		EXPECT_EQ(result->y, scale.y);

		TransformFree(&transform);
	}

	TEST(TransformMemberTests, GetScaleNull)
	{
		const Vector2D* result = TransformGetScale(nullptr);
		EXPECT_EQ(result, nullptr);
	}

	TEST(TransformMemberTests, SetAllAndGet)
	{
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		Vector2D translation = { 1.0f, 2.0f };
		TransformSetTranslation(transform, &translation);

		float rotation = 1.0f;
		TransformSetRotation(transform, rotation);

		Vector2D scale = { 1.0f, 2.0f };
		TransformSetScale(transform, &scale);

		const Vector2D* resultTranslation = TransformGetTranslation(transform);
		ASSERT_NE(resultTranslation, nullptr);
		EXPECT_EQ(resultTranslation->x, translation.x);
		EXPECT_EQ(resultTranslation->y, translation.y);

		float resultRotation = TransformGetRotation(transform);
		EXPECT_EQ(resultRotation, rotation);

		const Vector2D* resultScale = TransformGetScale(transform);
		ASSERT_NE(resultScale, nullptr);
		EXPECT_EQ(resultScale->x, scale.x);
		EXPECT_EQ(resultScale->y, scale.y);

		TransformFree(&transform);
	}

	/*
	TEST(TransformMemberTests, GetMatrix)
	{
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);
		ASSERT_TRUE(transform->isDirty);

		Vector2D translation = { 1.0f, 2.0f };
		TransformSetTranslation(transform, &translation);
		float rotation = 90.0f;
		TransformSetRotation(transform, rotation);
		Vector2D scale = { 3.0f, 4.0f };
		TransformSetScale(transform, &scale);

		const Matrix2D* result = TransformGetMatrix(transform);
		ASSERT_NE(result, nullptr);

		EXPECT_EQ(Matrix2DRowCol(result, 0, 0), 3.0f);
		EXPECT_EQ(Matrix2DRowCol(result, 0, 1), 0.0f);
		EXPECT_EQ(Matrix2DRowCol(result, 0, 2), 1.0f);
		EXPECT_EQ(Matrix2DRowCol(result, 0, 3), 0.0f);

		TransformFree(&transform);
	}
	*/
}