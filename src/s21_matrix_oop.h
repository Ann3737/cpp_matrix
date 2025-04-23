#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <cstddef>
#include <unistd.h>

class S21Matrix {
 public:
  using Item = double;
  using ItemsPtr = double*;

  inline static constexpr size_t kDefaultRowsNum = 3;
  inline static constexpr size_t kDefaultColsNum = 3;
  inline static constexpr Item kDefaultValue = 0.0;
  inline static constexpr Item kEqualityDiff = 1e-6;

 private:
  size_t rows_;      // Кол-во строк
  size_t cols_;      // Кол-во столбцов
  ItemsPtr matrix_;  // Указатель на данные матрицы

 public:
  // Constructors & Destructors
  S21Matrix();
  S21Matrix(const size_t r, const size_t c,
            const Item& init_value = kDefaultValue);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

 public:
  void PrintlnMatrix() const;

  // Methods
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const Item num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  Item Determinant() const;
  S21Matrix InverseMatrix() const;

  // Operators
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const Item num) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const Item num);
  Item& operator()(const size_t i, const size_t j);
  const Item& operator()(const size_t i, const size_t j) const;

  // Accessors & Mutators
  size_t GetRows() const { return rows_; };
  size_t GetCols() const { return cols_; };
  void SetRows(const ssize_t row);
  void SetCols(const ssize_t col);

 private:
  static ItemsPtr _AllocateMatrixData(const size_t r, const size_t c);
  static void _DeallocateMatrixData(ItemsPtr data);
  size_t _GetDataIdx(const size_t i, const size_t j) const;
  void _Deallocate();
  S21Matrix _GetMinor(size_t row, size_t col) const;
};

#endif
