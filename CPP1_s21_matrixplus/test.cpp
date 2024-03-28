#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(EqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);

  EXPECT_TRUE(matrix_a == matrix_b);
  S21Matrix matrix_ba = std::move(matrix_a);
  EXPECT_THROW(matrix_a == matrix_b, std::out_of_range);
}
TEST(EqMatrix1, False) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);

  EXPECT_FALSE(matrix_a == matrix_b);
}

TEST(EqMatrix3, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -2;
  matrix_a(1, 1) = -1;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = -2;
  matrix_b(1, 1) = -1;

  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorParentheses, True) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  EXPECT_EQ(matrix_a(0, 1), 2);
}
TEST(OperatorParentheses1, False) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  EXPECT_NE(matrix_a(0, 1), 10);
}

TEST(OperatorParentheses2, False) {
  S21Matrix matrix_a(2, 2);

  EXPECT_THROW(matrix_a(0, 5) = 5, std::out_of_range);

  EXPECT_THROW(matrix_a(5, 0) = 5, std::out_of_range);
}

TEST(OperatorPlus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;

  result(0, 0) = 2;
  result(0, 1) = 4;
  result(1, 0) = 6;
  result(1, 1) = 8;

  EXPECT_TRUE((matrix_a + matrix_b) == result);
}
TEST(OperatorMinus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;

  result(0, 0) = 0;
  result(0, 1) = 0;
  result(1, 0) = 0;
  result(1, 1) = 0;

  EXPECT_TRUE((matrix_a - matrix_b) == result);
}
TEST(OperatorMultiplyMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  EXPECT_TRUE((matrix_a * matrix_b) == result);
}
TEST(OperatorMultiplyNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  EXPECT_TRUE((matrix_a * 10) == result);
}

TEST(OperatorMultiplyNumber2, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  EXPECT_TRUE((10 * matrix_a) == result);
}

TEST(OperatorEqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(1, 3);
  matrix_a = matrix_b;
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorSumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  EXPECT_TRUE((matrix_a += matrix_b) == result);
}
TEST(OperatorSumMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW((matrix_a += matrix_b), std::out_of_range);
}

TEST(OperatorSubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  EXPECT_TRUE((matrix_a -= matrix_b) == result);
}

TEST(OperatorSubMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a -= matrix_b, std::out_of_range);
}
TEST(OperatorMulNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  EXPECT_TRUE((matrix_a *= 10) == result);
}
TEST(OperatorMulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  EXPECT_TRUE((matrix_a *= matrix_b) == result);
}
TEST(OperatorMulMatrix, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a *= matrix_b, std::out_of_range);
}

TEST(Get, True) {
  S21Matrix matrix_a(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;

  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;

  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  EXPECT_EQ(matrix_a.get_rows(), 3);
  EXPECT_EQ(matrix_a.get_cols(), 3);
}
TEST(Set, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 2);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;

  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;

  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 2;
  result(0, 1) = 5;
  result(1, 0) = 6;

  result(1, 1) = 3;
  result(2, 0) = 5;
  result(2, 1) = -2;

  matrix_a.set_cols(2);

  EXPECT_TRUE(matrix_a == result);

  EXPECT_THROW(matrix_a.set_cols(-2), std::invalid_argument);

  S21Matrix matrix_b(3, 3);
  S21Matrix result_b(2, 3);

  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 5;
  matrix_b(0, 2) = 7;

  matrix_b(1, 0) = 6;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 4;

  matrix_b(2, 0) = 5;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = -3;

  result_b(0, 0) = 2;
  result_b(0, 1) = 5;
  result_b(0, 2) = 7;

  result_b(1, 0) = 6;
  result_b(1, 1) = 3;
  result_b(1, 2) = 4;

  matrix_b.set_rows(2);

  EXPECT_TRUE(matrix_b == result_b);
}

TEST(Set2, True) {
  S21Matrix matrix_b(3, 3);
  S21Matrix result_b(2, 3);

  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 5;
  matrix_b(0, 2) = 7;

  matrix_b(1, 0) = 6;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 4;

  matrix_b(2, 0) = 5;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = -3;

  result_b(0, 0) = 2;
  result_b(0, 1) = 5;
  result_b(0, 2) = 7;
  result_b(1, 0) = 6;
  result_b(1, 1) = 3;
  result_b(1, 2) = 4;

  EXPECT_THROW(matrix_b.set_rows(-2), std::invalid_argument);
}
TEST(constructor, True) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -2;
  matrix_a(1, 1) = -1;

  S21Matrix matrix_c(2, 2);
  matrix_c(0, 0) = 1;
  matrix_c(0, 1) = 2;
  matrix_c(1, 0) = -2;
  matrix_c(1, 1) = -1;
  S21Matrix m_move;
  S21Matrix matrix_b(std::move(m_move = matrix_a + matrix_c));

  EXPECT_TRUE(matrix_b(0, 1) == 4);

  S21Matrix matrix_d;
  matrix_d(0, 2) = 1;
  EXPECT_TRUE(matrix_d(0, 2) == 1);
}

TEST(Transpose, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 4;
  matrix_a(0, 2) = 6;
  matrix_a(1, 0) = 1;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 5;
  matrix_a(2, 0) = 0;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 7;

  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 1;
  matrix_b(0, 2) = 0;

  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 8;

  matrix_b(2, 0) = 6;
  matrix_b(2, 1) = 5;
  matrix_b(2, 2) = 7;

  EXPECT_TRUE(matrix_a.Transpose() == matrix_b);
}

TEST(Transpose_operator, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 4;
  matrix_a(0, 2) = 6;
  matrix_a(1, 0) = 1;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 5;
  matrix_a(2, 0) = 0;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 7;

  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 1;
  matrix_b(0, 2) = 0;

  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 8;

  matrix_b(2, 0) = 6;
  matrix_b(2, 1) = 5;
  matrix_b(2, 2) = 7;

  S21Matrix s = std::move(matrix_a);
  EXPECT_TRUE(s.Transpose() == matrix_b);
  EXPECT_TRUE(matrix_a.get_cols() == 0);
}

TEST(determinant, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 1;
  matrix_a(0, 2) = 2;

  matrix_a(1, 0) = 2;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 4;

  matrix_a(2, 0) = 1;
  matrix_a(2, 1) = 6;
  matrix_a(2, 2) = 3;

  EXPECT_TRUE(matrix_a.Determinant() == -15);

  S21Matrix matrix_c(3, 4);
  matrix_c(0, 0) = 3;
  matrix_c(0, 1) = 1;
  matrix_c(0, 2) = 2;

  matrix_c(1, 0) = 2;
  matrix_c(1, 1) = 5;
  matrix_c(1, 2) = 4;

  matrix_c(2, 0) = 1;
  matrix_c(2, 1) = 6;
  matrix_c(2, 2) = 3;

  EXPECT_THROW(matrix_c.Determinant(), std::out_of_range);
}

TEST(CalcComplements, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;

  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;

  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 1;

  matrix_b(0, 0) = 0;
  matrix_b(0, 1) = 10;
  matrix_b(0, 2) = -20;

  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = -14;
  matrix_b(1, 2) = 8;

  matrix_b(2, 0) = -8;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = 4;
  S21Matrix m_move;
  S21Matrix matrix_c(std::move(m_move = matrix_a.CalcComplements()));
  EXPECT_TRUE(matrix_c == matrix_b);
}

TEST(CalcComplements1, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(0, 2) = 3.0;

  matrix_a(1, 0) = 1.0;
  matrix_a(1, 1) = 3.0;
  matrix_a(1, 2) = 2.0;

  matrix_a(2, 0) = 5.0;
  matrix_a(2, 1) = 2.0;
  matrix_a(2, 2) = 1.0;

  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = -1.0;
  matrix_b(0, 1) = 9.0;
  matrix_b(0, 2) = -13.0;

  matrix_b(1, 0) = 4.0;
  matrix_b(1, 1) = -14.0;
  matrix_b(1, 2) = 8.0;

  matrix_b(2, 0) = -5.0;
  matrix_b(2, 1) = 1.0;
  matrix_b(2, 2) = 1.0;

  S21Matrix matrix_result = matrix_a.CalcComplements();

  EXPECT_TRUE(matrix_result.EqMatrix(matrix_b));

  S21Matrix matrix_a1(1, 1);
  S21Matrix matrix_result1 = matrix_a1.CalcComplements();

  EXPECT_TRUE(matrix_result1(0, 0) == 1);
}

TEST(CalcComplements2, True) {
  S21Matrix matrix_a(3, 4);
  S21Matrix matrix_b(3, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;

  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;

  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 1;
  S21Matrix m_move;
  EXPECT_THROW(
      S21Matrix matrix_c(std::move(m_move = matrix_a.CalcComplements())),
      std::out_of_range);
}

TEST(InverseMatrix, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2.0;
  matrix_a(0, 1) = 5.0;
  matrix_a(0, 2) = 7.0;

  matrix_a(1, 0) = 6.0;
  matrix_a(1, 1) = 3.0;
  matrix_a(1, 2) = 4.0;

  matrix_a(2, 0) = 5.0;
  matrix_a(2, 1) = -2.0;
  matrix_a(2, 2) = -3.0;

  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 1.0;
  matrix_b(0, 1) = -1.0;
  matrix_b(0, 2) = 1.0;

  matrix_b(1, 0) = -38.0;
  matrix_b(1, 1) = 41.0;
  matrix_b(1, 2) = -34.0;

  matrix_b(2, 0) = 27.0;
  matrix_b(2, 1) = -29.0;
  matrix_b(2, 2) = 24.0;

  S21Matrix matrix_result = matrix_a.InverseMatrix();

  EXPECT_TRUE(matrix_result.EqMatrix(matrix_b));

  S21Matrix matrix_a1(1, 1);

  matrix_a1(0, 0) = 2.0;

  S21Matrix matrix_result1 = matrix_a1.InverseMatrix();

  EXPECT_TRUE(matrix_result1(0, 0) == 0.5);
}
TEST(InverseMatrix2, False) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2.0;
  matrix_a(0, 1) = 5.0;
  matrix_a(0, 2) = 7.0;

  matrix_a(1, 0) = 6.0;
  matrix_a(1, 1) = 3.0;
  matrix_a(1, 2) = 4.0;

  matrix_a(2, 0) = 5.0;
  matrix_a(2, 1) = -2.0;
  matrix_a(2, 2) = -3.0;

  S21Matrix matrix_result = std::move(matrix_a);

  EXPECT_THROW(matrix_a.InverseMatrix(), std::out_of_range);
}

TEST(InverseMatrix3, False) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 1.0;
  matrix_a(0, 2) = 1.0;

  matrix_a(1, 0) = 1.0;
  matrix_a(1, 1) = 1.0;
  matrix_a(1, 2) = 1.0;

  matrix_a(2, 0) = 1.0;
  matrix_a(2, 1) = 1.0;
  matrix_a(2, 2) = 1.0;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::out_of_range);
}

TEST(Memory_allocation, FALSE) {
  EXPECT_THROW(S21Matrix matrix_result(0, 1), std::out_of_range);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
