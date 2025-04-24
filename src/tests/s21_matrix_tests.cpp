#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// Тесты для конструкторов
TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(ConstructorTest, ParameterizedConstructor) {
  S21Matrix m(4, 5);
  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 5);
}

TEST(ConstructorTest, CopyConstructor) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1.0;
  S21Matrix m2(m1);

  EXPECT_TRUE(m1 == m2);
}

TEST(ConstructorTest, MoveConstructor) {
  S21Matrix m(2, 3);
  m(0, 0) = 1.0;
  S21Matrix copy(m);
  S21Matrix moved(std::move(m));

  EXPECT_TRUE(moved == copy);
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

// Тесты для операторов
TEST(OperatorTest, CopySelfAssignment) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  S21Matrix m2 = m1;

  EXPECT_TRUE(m1 == m2);
}

TEST(OperatorTest, MoveSelfMove) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  S21Matrix copy = m;
  S21Matrix temp = std::move(m);

  EXPECT_TRUE(temp == copy);
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

TEST(OperatorTest, DifferentDimensions) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 4);
  EXPECT_FALSE(m1 == m2);
}

TEST(OperatorTest, SmallDifference) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.0;
  m2(0, 0) = 1.0 + 1e-7;

  EXPECT_TRUE(m1 == m2);
}

TEST(OperatorTest, SignificantDifference) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.0;
  m2(0, 0) = 2.0;

  EXPECT_FALSE(m1 == m2);
}

TEST(OperatorTest, DifferentRowsSameCols) {
  S21Matrix m1(2, 3), m2(3, 3);
  EXPECT_FALSE(m1 == m2);
}

TEST(OperatorTest, SameRowsDifferentCols) {
  S21Matrix m1(3, 2), m2(3, 3);
  EXPECT_FALSE(m1 == m2);
}

TEST(OperatorTest, SameRowsSameCols) {
  S21Matrix m1(3, 3), m2(3, 3);
  EXPECT_TRUE(m1 == m2);
}

TEST(OperatorTest, SelfAssignment) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m += m;

  EXPECT_DOUBLE_EQ(m(0, 0), 2.0);
}

TEST(OperatorTest, PlusEquals) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 2;
  m2(0, 1) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;

  m1 += m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 9.0);
}

TEST(OperatorTest, MinusEquals) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 2;
  m2(0, 1) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;

  m1 -= m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), -1.0);
}

TEST(OperatorTest, Addition) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  S21Matrix result = m1 + m2;

  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(OperatorTest, Multiplication) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  S21Matrix m2(3, 2);
  m2(0, 0) = 7;
  m2(0, 1) = 8;
  m2(1, 0) = 9;
  m2(1, 1) = 10;
  m2(2, 0) = 11;
  m2(2, 1) = 12;

  S21Matrix result = m1 * m2;

  EXPECT_DOUBLE_EQ(result(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 154.0);
}

TEST(OperatorTest, MultiplyEqualsNum) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m *= 2.0;

  EXPECT_DOUBLE_EQ(m(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 8.0);
}

TEST(OperatorTest, StaplesIncorrectNum) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m(2, -1), std::out_of_range);
}

TEST(OperatorTest, StaplesCorrectNum) {
  S21Matrix m(2, 2);
  EXPECT_DOUBLE_EQ(m(1, 1), 0.0);
}

TEST(OperatorTest, OutOfBounds) {
  S21Matrix m(3, 3);
  EXPECT_THROW(m(3, 2), std::out_of_range);
  EXPECT_THROW(m(2, 3), std::out_of_range);
  EXPECT_THROW(m(-1, 2), std::out_of_range);
  EXPECT_THROW(m(2, -1), std::out_of_range);
}

// Тесты граничных значений
TEST(EdgeCaseTest, ZeroSizeMatrix) {
  EXPECT_THROW(S21Matrix m(0, 0), std::out_of_range);
}

TEST(EdgeCaseTest, LargeMatrix) {
  S21Matrix m(1000, 1000);
  EXPECT_EQ(m.GetRows(), 1000);
  EXPECT_EQ(m.GetCols(), 1000);
}

// Тесты для методов
TEST(SetRowsTest, DecreaseRowsWithDataLoss) {
  S21Matrix m(3, 3);
  m(2, 2) = 5.0;
  m.SetRows(2);

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_THROW(m(2, 2), std::out_of_range);
}

TEST(SetRowsTest, SetRowsIncrease) {
  S21Matrix m(2, 3);
  m.SetRows(4);

  EXPECT_EQ(m.GetRows(), 4);

  for (size_t i = 2; i < 4; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(m(i, j), 0.0);
    }
  }
}

TEST(SetRowsTest, SetRowsDecrease) {
  S21Matrix m(4, 3);
  m.SetRows(2);
  EXPECT_EQ(m.GetRows(), 2);
}

TEST(SetRowsTest, InvalidRowValue) {
  S21Matrix m(3, 3);
  EXPECT_THROW(m.SetRows(0), std::out_of_range);
  EXPECT_THROW(m.SetRows(-1), std::out_of_range);
}

TEST(SetColsTest, DecreaseCol) {
  S21Matrix m(3, 3);
  m(2, 2) = 5.0;
  m.SetCols(2);

  EXPECT_EQ(m.GetCols(), 2);
  EXPECT_THROW(m(2, 2), std::out_of_range);
}

TEST(SetColsTest, InvalidColValue) {
  S21Matrix m(3, 3);
  EXPECT_THROW(m.SetCols(0), std::out_of_range);
  EXPECT_THROW(m.SetCols(-1), std::out_of_range);
}

TEST(SetColsTest, IncreaseSize) {
  S21Matrix m(2, 2);
  m.SetCols(3);
  EXPECT_EQ(m.GetCols(), 3);
  EXPECT_DOUBLE_EQ(m(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 2), 0.0);
}

TEST(SetColsTest, DecreaseSize) {
  S21Matrix m(2, 3);
  m.SetCols(2);
  EXPECT_EQ(m.GetCols(), 2);
}

TEST(SumTest, MismatchedDimensions) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 4);
  EXPECT_THROW(m1.SumMatrix(m2), std::invalid_argument);
}

TEST(SumTest, Basic) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 2;
  m2(0, 1) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;

  m1.SumMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 9.0);
}

TEST(SubTest, MismatchedDimensions) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 4);
  EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(SubTest, Basic) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 2;
  m2(0, 1) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;

  m1.SubMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), -1.0);
}

TEST(SubTest, SizeMismatchException) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);
  EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(MulTest, ValidValues) {
  S21Matrix m1(2, 3, 3.0), m2(3, 2, 2.0);
  m1.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(m1(0, 0), 18.0);
}

TEST(MulTest, MultiplyByZeroMatrix) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(m1(0, 0), 0.0);
}

TEST(MulTest, MismatchedDimensions) {
  S21Matrix m1(3, 4);
  S21Matrix m2(5, 3);
  EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);
}

TEST(MulTest, MulNum) {
  S21Matrix m(3, 4, 2.0);
  m.MulNumber(2.0);
  EXPECT_DOUBLE_EQ(m(0, 0), 4.0);
}

TEST(TransposeTest, Transpose) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  S21Matrix transposed = m1.Transpose();

  EXPECT_EQ(transposed.GetRows(), 3);
  EXPECT_EQ(transposed.GetCols(), 2);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposed(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(transposed(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposed(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(transposed(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(transposed(2, 1), 6.0);
}

TEST(CalcComplementsTest, Matrix3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 9;

  S21Matrix result = m.CalcComplements();
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

TEST(CalcComplementsTest, NonSquareMatrix1) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.CalcComplements(), std::domain_error);
}

TEST(CalcComplementsTest, NonSquareMatrix2) {
  S21Matrix m(3, 4);
  EXPECT_THROW(m.CalcComplements(), std::domain_error);
}

TEST(DeterminantTest, Matrix1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 42.0;
  EXPECT_DOUBLE_EQ(m.Determinant(), 42.0);
}

TEST(DeterminantTest, Matrix2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  EXPECT_DOUBLE_EQ(m.Determinant(), -2.0);
}

TEST(DeterminantTest, Matrix3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 6;
  m(0, 1) = 1;
  m(0, 2) = 1;
  m(1, 0) = 4;
  m(1, 1) = -2;
  m(1, 2) = 5;
  m(2, 0) = 2;
  m(2, 1) = 8;
  m(2, 2) = 7;

  EXPECT_DOUBLE_EQ(m.Determinant(), -306.0);
}

TEST(DeterminantTest, ZeroDeterminant) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 9;

  EXPECT_DOUBLE_EQ(m.Determinant(), 0.0);
}

TEST(DeterminantTest, NonSquareMatrix) {
  S21Matrix m(3, 4);
  EXPECT_THROW(m.Determinant(), std::domain_error);
}

TEST(DeterminantTest, NonSquareMatrixException) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.Determinant(), std::domain_error);
}

TEST(InverseTest, Matrix2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  S21Matrix result = m.InverseMatrix();

  EXPECT_NEAR(result(0, 0), -2.0, 1e-6);
  EXPECT_NEAR(result(0, 1), 1.0, 1e-6);
  EXPECT_NEAR(result(1, 0), 1.5, 1e-6);
  EXPECT_NEAR(result(1, 1), -0.5, 1e-6);
}

TEST(InverseTest, ZeroDeterminantException) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 2;
  m(1, 1) = 4;

  EXPECT_THROW(m.InverseMatrix(), std::invalid_argument);
}

TEST(InverseTest, NonSquareMatrixException) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.InverseMatrix(), std::domain_error);
}

TEST(InverseTest, IdentityMatrix) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  m(1, 1) = 1.0;
  m(2, 2) = 1.0;
  S21Matrix inv = m.InverseMatrix();

  EXPECT_TRUE(inv == m);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}