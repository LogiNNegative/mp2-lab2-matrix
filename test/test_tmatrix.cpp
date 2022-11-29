#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<double> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<double> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<double> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<double> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<double> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size);

	matrix_1[0][0] = 1; matrix_1[0][1] = 6; matrix_1[0][2] = 3;
	matrix_1[1][0] = 7; matrix_1[1][1] = 1; matrix_1[1][2] = -5;
	matrix_1[2][0] = 2; matrix_1[2][1] = 1; matrix_1[2][2] = 0.5;

	TDynamicMatrix<double> matrix_2(matrix_1);

	EXPECT_EQ(matrix_1, matrix_2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size);

	matrix_1[0][0] = 1; matrix_1[0][1] = 6; matrix_1[0][2] = 3;
	matrix_1[1][0] = 7; matrix_1[1][1] = 1; matrix_1[1][2] = -5;
	matrix_1[2][0] = 2; matrix_1[2][1] = 1; matrix_1[2][2] = 0.5;

	TDynamicMatrix<double> matrix_2(matrix_1);

	matrix_1[0][0] = -1;

	EXPECT_NE(matrix_1[0][0], matrix_2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size);

	EXPECT_EQ(matrix_1.size(), matrix_size);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size);

	ASSERT_NO_THROW(matrix_1[1][1] = 10);
	EXPECT_EQ(matrix_1[1][1], 10);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<double> matrix_1(5);
	ASSERT_ANY_THROW(matrix_1.at(-1, 0) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<double> matrix_1(5);
	ASSERT_ANY_THROW(matrix_1.at(6, 0) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size);
	ASSERT_NO_THROW(matrix_1 = matrix_1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size), matrix_2(matrix_size);
	matrix_1[0][0] = 993;
	EXPECT_EQ(matrix_1, matrix_2 = matrix_1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<double> matrix_1(7), matrix_2(1);
	matrix_2 = matrix_1;
	EXPECT_EQ(matrix_1.size(), matrix_2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<double> matrix_1(7), matrix_2(1);
	matrix_1[6][6] = -1;
	matrix_2 = matrix_1;
	EXPECT_EQ(matrix_1, matrix_2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<double> matrix_1(7), matrix_2(1);
	matrix_1[6][6] = -1;
	matrix_2 = matrix_1;
	EXPECT_EQ(matrix_1 == matrix_2, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<double> matrix_1(7);
	matrix_1[6][6] = -1;
	EXPECT_EQ(matrix_1 == matrix_1, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<double> matrix_1(7), matrix_2(1);
	EXPECT_EQ(matrix_1 == matrix_2, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size), matrix_2(matrix_size), matrix_3(matrix_size);
	matrix_1[0][0] = -1; matrix_1[0][1] = -7; matrix_1[0][2] = -9;
	matrix_2[0][0] = 1; matrix_2[0][1] = 1000; matrix_2[0][2] = 89;
	matrix_3[0][0] = 0; matrix_3[0][1] = 993; matrix_3[0][2] = 80;

	EXPECT_EQ(matrix_1 + matrix_2, matrix_3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<double> matrix_1(1), matrix_2(2);
	ASSERT_ANY_THROW(matrix_1 + matrix_2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	size_t matrix_size = 3;
	TDynamicMatrix<double> matrix_1(matrix_size), matrix_2(matrix_size), matrix_3(matrix_size);
	matrix_1[0][0] = -1; matrix_1[0][1] = -7; matrix_1[0][2] = -9;
	matrix_2[0][0] = 1; matrix_2[0][1] = 1000; matrix_2[0][2] = 89;
	matrix_3[0][0] = -2; matrix_3[0][1] = -1007; matrix_3[0][2] = -98;

	EXPECT_EQ(matrix_1 - matrix_2, matrix_3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<double> matrix_1(3), matrix_2(5);
	ASSERT_ANY_THROW(matrix_1 - matrix_2);
}

