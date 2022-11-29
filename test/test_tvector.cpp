#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> vector_1(10);
	vector_1[0] = 7; vector_1[3] = 1; vector_1[9] = 4;
	TDynamicVector<int> vector_2(vector_1);

	EXPECT_EQ(vector_1, vector_2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> vector_1(10);
	vector_1[0] = 7; vector_1[3] = 1; vector_1[9] = 4;
	TDynamicVector<int> vector_2(vector_1);
	vector_1[0] = 1;

	EXPECT_NE(vector_1, vector_2);
}

TEST(TDynamicVector, can_get_size)
{
	size_t vector_size = 2;
	TDynamicVector<int> vector_1(vector_size);

	EXPECT_EQ(vector_size, vector_1.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> vector_1(4);

	ASSERT_NO_THROW(vector_1[0] = 10);
	EXPECT_EQ(vector_1[0], 10);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> vector_1(7);

	ASSERT_ANY_THROW(vector_1.at(-5) = -5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> vector_1(1);

	ASSERT_ANY_THROW(vector_1.at(73) = 37);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> vector_1(5);

	ASSERT_NO_THROW(vector_1 = vector_1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	size_t vector_size = 3;
	TDynamicVector<int> vector_1(vector_size), vector_2(vector_size);
	vector_2[0] = 77;

	ASSERT_NO_THROW(vector_1 = vector_2);
	EXPECT_EQ(vector_1, vector_2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	size_t size_vector_2 = 3;
	TDynamicVector<int> vector_1(1), vector_2(size_vector_2);

	vector_1 = vector_2;

	EXPECT_EQ(vector_1.size(), size_vector_2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> vector_1(10), vector_2(1);

	vector_1[0] = 10; vector_1[3] = 7; vector_1[8] = 2;
	vector_2 = vector_1;

	EXPECT_EQ(vector_1, vector_1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> vector_1(5);
	vector_1[0] = 9; vector_1[3] = 7;
	TDynamicVector<int> vector_2(vector_1);

	EXPECT_EQ(vector_1 == vector_2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> vector_1(1);

	EXPECT_EQ(vector_1 == vector_1, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> vector_1(6), vector_2(16);

	EXPECT_EQ(vector_1 == vector_2, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	size_t vector_size = 2;
	TDynamicVector<int> vector_1(vector_size), vector_2(vector_size);

	vector_1[0] = 100; vector_1[1] = 133;
	vector_2[0] = 167; vector_2[1] = 200;

	ASSERT_NO_THROW(vector_1 + 67);
	EXPECT_EQ(vector_1 + 67, vector_2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	size_t vector_size = 4;
	TDynamicVector<int> vector_1(vector_size), vector_2(vector_size);

	vector_1[0] = 139; vector_1[1] = 249; vector_1[2] = 333; vector_1[3] = 379;
	vector_2[0] = 100; vector_2[1] = 210; vector_2[2] = 294; vector_2[3] = 340;

	ASSERT_NO_THROW(vector_1 - 39);
	EXPECT_EQ(vector_1 - 39, vector_2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	size_t vector_size = 4;
	TDynamicVector<double> vector_1(vector_size), vector_2(vector_size);

	vector_1[0] = 0.5; vector_1[1] = 125; vector_1[2] = 107; vector_1[3] = 249;
	vector_2[0] = 2.0; vector_2[1] = 500; vector_2[2] = 428; vector_2[3] = 996;

	ASSERT_NO_THROW(vector_1 * 4);
	EXPECT_EQ(vector_1 * 4, vector_2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	size_t vector_size = 13;
	TDynamicVector<int> vector_1(vector_size), vector_2(vector_size), vector_3(vector_size);

	vector_1[0] = 15; vector_2[0] = 85; vector_3[0] = 100;

	ASSERT_NO_THROW(vector_1 + vector_2);
	EXPECT_EQ(vector_1 + vector_2, vector_3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> vector_1(1), vector_2(11);

	ASSERT_ANY_THROW(vector_1 + vector_2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	size_t vector_size = 13;
	TDynamicVector<int> vector_1(vector_size), vector_2(vector_size), vector_3(vector_size);

	vector_1[0] = 100; vector_2[0] = 85; vector_3[0] = 15;

	ASSERT_NO_THROW(vector_1 - vector_2);
	EXPECT_EQ(vector_1 - vector_2, vector_3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> vector_1(7), vector_2(2);
	ASSERT_ANY_THROW(vector_1 - vector_2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	size_t vector_size = 5;
	TDynamicVector<int> vector_1(vector_size), vector_2(vector_size);

	vector_1[0] = 7; vector_1[1] = 9;
	vector_2[0] = 8; vector_2[1] = 10;

	ASSERT_NO_THROW(vector_1 * vector_2);
	EXPECT_EQ(vector_1 * vector_2, 146);
}


TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> vector_1(16), vector_2(15);
	ASSERT_ANY_THROW(vector_1 * vector_2);
}

