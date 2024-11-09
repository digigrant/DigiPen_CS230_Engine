#include <gtest/gtest.h>
#include "Transform.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Stream.h"

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

	TEST(TransformReadTests, ReadTransform)
	{
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		Stream stream = StreamOpen("TestData/TransformRead_data.txt");
		ASSERT_NE(stream, nullptr);

		TransformRead(transform, stream);

		const Vector2D* translation = TransformGetTranslation(transform);
		ASSERT_NE(translation, nullptr);
		EXPECT_EQ(translation->x, 1.0f);
		EXPECT_EQ(translation->y, 2.0f);

		float rotation = TransformGetRotation(transform);
		EXPECT_EQ(rotation, 90.0f);

		const Vector2D* scale = TransformGetScale(transform);
		ASSERT_NE(scale, nullptr);
		EXPECT_EQ(scale->x, 3.0f);
		EXPECT_EQ(scale->y, 4.0f);

		StreamClose(&stream);
		ASSERT_EQ(stream, nullptr);
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

	TEST(TransformUnitTests, TransformClone)
	{
		// Set up original
		Transform* transform = TransformCreate();
		ASSERT_NE(transform, nullptr);

		Vector2D pos = { 1.0f, 2.0f };
		float rot = 3.0f;
		Vector2D scale = { 4.0f, 5.0f };
		TransformSetTranslation(transform, &pos);
		TransformSetRotation(transform, rot);
		TransformSetScale(transform, &scale);

		// doesnt check matrix - matrix is never calculated. isDirty is true

		Transform* transformClone = TransformClone(transform);
		ASSERT_NE(transformClone, nullptr);
		EXPECT_EQ(TransformGetTranslation(transformClone)->x, pos.x);
		EXPECT_EQ(TransformGetTranslation(transformClone)->y, pos.y);
		EXPECT_EQ(TransformGetRotation(transformClone), rot);
		EXPECT_EQ(TransformGetScale(transformClone)->x, scale.x);
		EXPECT_EQ(TransformGetScale(transformClone)->y, scale.y);

		Vector2D newpos_orig, newpos_clone, newscale_orig, newscale_clone;
		float newrot_orig, newrot_clone;
		Vector2DScale(&newpos_orig, &pos, 5.0f);
		Vector2DScale(&newpos_clone, &pos, 10.0f);
		newrot_orig = rot * 5.0f;
		newrot_clone = rot * 10.0f;
		Vector2DScale(&newscale_orig, &scale, 5.0f);
		Vector2DScale(&newscale_clone, &scale, 10.0f);

		TransformSetTranslation(transform, &newpos_orig);
		TransformSetRotation(transform, newrot_orig);
		TransformSetScale(transform, &newscale_orig);
		TransformSetTranslation(transformClone, &newpos_clone);
		TransformSetRotation(transformClone, newrot_clone);
		TransformSetScale(transformClone, &newscale_clone);

		EXPECT_EQ(TransformGetTranslation(transform)->x, newpos_orig.x);
		EXPECT_EQ(TransformGetTranslation(transform)->y, newpos_orig.y);
		EXPECT_EQ(TransformGetRotation(transform), newrot_orig);
		EXPECT_EQ(TransformGetScale(transform)->x, newscale_orig.x);
		EXPECT_EQ(TransformGetScale(transform)->y, newscale_orig.y);

		EXPECT_EQ(TransformGetTranslation(transformClone)->x, newpos_clone.x);
		EXPECT_EQ(TransformGetTranslation(transformClone)->y, newpos_clone.y);
		EXPECT_EQ(TransformGetRotation(transformClone), newrot_clone);
		EXPECT_EQ(TransformGetScale(transformClone)->x, newscale_clone.x);
		EXPECT_EQ(TransformGetScale(transformClone)->y, newscale_clone.y);

		TransformFree(&transform);
		EXPECT_EQ(transform, nullptr);
		EXPECT_NE(transformClone, nullptr);
		TransformFree(&transformClone);
		ASSERT_EQ(transformClone, nullptr);

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