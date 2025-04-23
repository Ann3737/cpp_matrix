#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "s21_matrix_oop.h"

// Тесты конструкторов
TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.GetRows(), 3ul);
  EXPECT_EQ(matrix1.GetCols(), 3ul);
}

TEST(ConstructorTest, ParameterizedConstructor) {
  S21Matrix matrix1(4ul, 5ul);
  EXPECT_EQ(matrix1.GetRows(), 4ul);
  EXPECT_EQ(matrix1.GetCols(), 5ul);
}

TEST(ConstructorTest, CopyConstructor) {
  S21Matrix matrix1(2ul, 3ul);
  matrix1(0, 0) = 1.0;
  S21Matrix matrix2(matrix1);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(ConstructorTest, MoveConstructor) {
  S21Matrix matrix1(2ul, 3ul);
  matrix1(0, 0) = 1.0;
  S21Matrix copy(matrix1);
  S21Matrix moved(std::move(matrix1));
  EXPECT_TRUE(moved == copy);
  EXPECT_EQ(matrix1.GetRows(), 0ul);
  EXPECT_EQ(matrix1.GetCols(), 0ul);
}

// Тесты операторов присваивания
TEST(AssignmentOperatorTest, CopySelfAssignment) {
  S21Matrix matrix1(2ul, 2ul);
  matrix1(0, 0) = 1.0;
  S21Matrix matrix2 = matrix1;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(AssignmentOperatorTest, MoveSelfMove) {
  S21Matrix matrix1(2ul, 2ul);
  matrix1(0, 0) = 1.0;
  S21Matrix copy = matrix1;

  S21Matrix temp = std::move(matrix1);
  EXPECT_TRUE(temp == copy);
  EXPECT_EQ(matrix1.GetRows(), 0ul);
  EXPECT_EQ(matrix1.GetCols(), 0ul);
}

TEST(EqMatrixTest, DifferentDimensions) {
    S21Matrix matrix1(3, 3);
    S21Matrix matrix2(3, 4);
    EXPECT_FALSE(matrix1 == matrix2);
}

TEST(EqMatrixTest, SmallDifference) {
    S21Matrix matrix1(3, 3);
    S21Matrix matrix2(3, 3);
    matrix1(0, 0) = 1.0;
    matrix2(0, 0) = 1.0 + 1e-7;
    EXPECT_TRUE(matrix1 == matrix2);
}

TEST(EqMatrixTest, SignificantDifference) {
    S21Matrix matrix1(3, 3);
    S21Matrix matrix2(3, 3);
    matrix1(0, 0) = 1.0;
    matrix2(0, 0) = 2.0;
    EXPECT_FALSE(matrix1 == matrix2);
}

TEST(SetRowsTest, DecreaseRowsWithDataLoss) {
  S21Matrix m(3, 3);
  m(2, 2) = 5.0;
  m.SetRows(2);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_THROW(m(2, 2), std::out_of_range);
}

TEST(OperatorPlusEqualTest, SelfAssignment) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m += m;
  EXPECT_DOUBLE_EQ(m(0, 0), 2.0);
}

TEST(OperatorTest, PlusEquals) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  matrix1 += matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 9.0);
}

TEST(OperatorTest, MinusEquals) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  matrix1 -= matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -1.0);
}

TEST(OperatorTest, MultiplyEqualsScalar) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix *= 2.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

TEST(MulMatrixTest, MultiplyByZeroMatrix) {
  S21Matrix m1(2, 2), m2(2, 2); 
  m1.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(m1(0, 0), 0.0);
}

// Тесты граничных значений
TEST(EdgeCaseTest, ZeroSizeMatrix) {
  EXPECT_THROW(S21Matrix matrix1(0ul, 0ul), std::out_of_range);
}

TEST(EdgeCaseTest, LargeMatrix) {
  S21Matrix matrix1(1000ul, 1000ul);
  EXPECT_EQ(matrix1.GetRows(), 1000ul);
  EXPECT_EQ(matrix1.GetCols(), 1000ul);
}

// Тесты методов
TEST(MethodTest, SetRowsIncrease) {
  S21Matrix matrix1(2ul, 3ul);
  matrix1.SetRows(4ul);
  EXPECT_EQ(matrix1.GetRows(), 4ul);
  for (size_t i = 2; i < 4; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 0.0);
    }
  }
}

TEST(EqMatrixTest, DifferentRowsSameCols) {
  S21Matrix m1(2, 3), m2(3, 3);
  EXPECT_FALSE(m1 == m2);
}

TEST(EqMatrixTest, SameRowsDifferentCols) {
  S21Matrix m1(3, 2), m2(3, 3);
  EXPECT_FALSE(m1 == m2);
}

TEST(MethodTest, SetRowsDecrease) {
  S21Matrix matrix1(4ul, 3ul);
  matrix1.SetRows(2ul);
  EXPECT_EQ(matrix1.GetRows(), 2ul);
}

TEST(SetRowsTest, InvalidRowValue) {
    S21Matrix matrix(3, 3);
    EXPECT_THROW(matrix.SetRows(0), std::out_of_range);
    EXPECT_THROW(matrix.SetRows(-1), std::out_of_range);
}

TEST(SetColsTest, IncreaseSize) {
  S21Matrix matrix(2, 2);
  matrix.SetCols(3);

  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 0.0);
}

TEST(SetColsTest, DecreaseSize) {
  S21Matrix matrix(2, 3);
  matrix.SetCols(2);

  EXPECT_EQ(matrix.GetCols(), 2);
}

TEST(SetColsTest, InvalidColValue) {
    S21Matrix matrix(3, 3);
    EXPECT_THROW(matrix.SetCols(0), std::out_of_range);
    EXPECT_THROW(matrix.SetCols(-1), std::out_of_range);
}

TEST(IndexationTest, OutOfBounds) {
    S21Matrix matrix(3, 3);
    EXPECT_THROW(matrix(3, 2), std::out_of_range); // Row out of bounds
    EXPECT_THROW(matrix(2, 3), std::out_of_range); // Column out of bounds
    EXPECT_THROW(matrix(-1, 2), std::out_of_range); // Negative row index
    EXPECT_THROW(matrix(2, -1), std::out_of_range); // Negative column index
}

TEST(SumMatrixTest, MismatchedDimensions) {
    S21Matrix matrix1(3, 3);
    S21Matrix matrix2(3, 4);
    EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(SubMatrixTest, MismatchedDimensions) {
    S21Matrix matrix1(3, 3);
    S21Matrix matrix2(3, 4);
    EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(SubMatrixTest, Basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  matrix1.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -1.0);
}

TEST(SubMatrixTest, SizeMismatchException) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(InverseMatrixTest, Basic2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  S21Matrix result = matrix.InverseMatrix();
  EXPECT_NEAR(result(0, 0), -2.0, 1e-6);
  EXPECT_NEAR(result(0, 1), 1.0, 1e-6);
  EXPECT_NEAR(result(1, 0), 1.5, 1e-6);
  EXPECT_NEAR(result(1, 1), -0.5, 1e-6);
}

TEST(InverseMatrixTest, ZeroDeterminantException) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 4;

  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(InverseMatrixTest, NonSquareMatrixException) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.InverseMatrix(), std::domain_error);
}

TEST(DeterminantTest, 1x1Matrix) {
  S21Matrix m(1, 1);
  m(0, 0) = 42.0;
  EXPECT_DOUBLE_EQ(m.Determinant(), 42.0);
}

TEST(InverseMatrixTest, IdentityMatrix) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0; m(1, 1) = 1.0; m(2, 2) = 1.0;
  S21Matrix inv = m.InverseMatrix();
  EXPECT_TRUE(inv == m);
}

TEST(CalcComplementsTest, Basic3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  S21Matrix result = matrix.CalcComplements();
  EXPECT_DOUBLE_EQ(result(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 2), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -12.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 6.0);
  EXPECT_DOUBLE_EQ(result(2, 0), -3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(result(2, 2), -3.0);
}

TEST(CalcComplementsTest, NonSquareMatrixException) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.CalcComplements(), std::domain_error);
}

TEST(CalcComplementsTest, NonSquareMatrix) {
    S21Matrix matrix(3, 4);
    EXPECT_THROW(matrix.CalcComplements(), std::domain_error);
}

TEST(MethodTest, Determinant) {
  S21Matrix matrix1(2ul, 2ul);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  EXPECT_DOUBLE_EQ(matrix1.Determinant(), -2.0);
}

TEST(DeterminantTest, Basic2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), -2.0);
}

TEST(DeterminantTest, Basic3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 6;
  matrix(0, 1) = 1;
  matrix(0, 2) = 1;
  matrix(1, 0) = 4;
  matrix(1, 1) = -2;
  matrix(1, 2) = 5;
  matrix(2, 0) = 2;
  matrix(2, 1) = 8;
  matrix(2, 2) = 7;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), -306.0);
}

TEST(DeterminantTest, ZeroDeterminant) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), 0.0);
}

TEST(DeterminantTest, NonSquareMatrix) {
    S21Matrix matrix(3, 4);
    EXPECT_THROW(matrix.Determinant(), std::domain_error);
}

TEST(DeterminantTest, NonSquareMatrixException) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.Determinant(), std::domain_error);
}

TEST(MethodTest, Transpose) {
  S21Matrix matrix1(2ul, 3ul);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  S21Matrix transposed = matrix1.Transpose();
  EXPECT_EQ(transposed.GetRows(), 3ul);
  EXPECT_EQ(transposed.GetCols(), 2ul);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposed(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(transposed(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposed(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(transposed(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(transposed(2, 1), 6.0);
}

// Тесты операторов
TEST(OperatorTest, Addition) {
  S21Matrix matrix1(2ul, 2ul);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2ul, 2ul);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  S21Matrix result = matrix1 + matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(OperatorTest, Multiplication) {
  S21Matrix matrix1(2ul, 3ul);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  S21Matrix matrix2(3ul, 2ul);
  matrix2(0, 0) = 7;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 10;
  matrix2(2, 0) = 11;
  matrix2(2, 1) = 12;

  S21Matrix result = matrix1 * matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 154.0);
}

TEST(MulMatrixTest, MismatchedDimensions) {
    S21Matrix matrix1(3, 4);
    S21Matrix matrix2(5, 3);
    EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}