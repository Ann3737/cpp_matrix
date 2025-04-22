#include "s21_matrix_oop.h"

#include <iostream>

// void S21Matrix::PrintlnMatrix() const {
//     for (size_t i = 0; i < this->rows_; ++i) {
//         auto sep = "";
//         for (size_t j = 0; j < this->cols_; ++j) {
//             const size_t m = this->_GetDataIdx(i, j);
//             std::cout << sep << this->matrix_[m];
//             sep = " ";
//         }
//         std::cout << std::endl;
//     }
// }

void S21Matrix::SetRows(const int row) {
  if (row < 1) {
    throw std::out_of_range("Incorrect input, rows should be more than zero");
  }
  S21Matrix res(row, this->cols_);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < (int)this->cols_; ++j) {
      size_t m = res._GetDataIdx(i, j);
      if (i < (int)this->rows_) {
        size_t n = this->_GetDataIdx(i, j);
        res.matrix_[m] = this->matrix_[n];
      } else {
        res.matrix_[m] = 0.0;
      }
    }
  }
  *this = res;
}

void S21Matrix::SetCols(const int col) {
  if (col < 1) {
    throw std::out_of_range("Incorrect input, rows should be more than zero");
  }
  S21Matrix res(this->rows_, col);
  for (int i = 0; i < (int)this->rows_; ++i) {
    for (int j = 0; j < col; ++j) {
      size_t m = res._GetDataIdx(i, j);
      if (j < (int)this->cols_) {
        size_t n = this->_GetDataIdx(i, j);
        res.matrix_[m] = this->matrix_[n];
      } else {
        res.matrix_[m] = 0.0;
      }
    }
  }
  *this = res;
}

size_t S21Matrix::_GetDataIdx(const size_t i, const size_t j) const {
  return i * this->cols_ + j;
}

S21Matrix::ItemsPtr S21Matrix::_AllocateMatrixData(const size_t r,
                                                   const size_t c) {
  return (r * c != 0) ? new S21Matrix::Item[r * c] : nullptr;
}

void S21Matrix::_DeallocateMatrixData(ItemsPtr data) { delete[] data; }

void S21Matrix::_Deallocate() {
  if (this->matrix_ != nullptr) {
    _DeallocateMatrixData(this->matrix_);
  }
}

S21Matrix::S21Matrix()
    : S21Matrix(kDefaultRowsNum, kDefaultColsNum, kDefaultValue) {}

S21Matrix::S21Matrix(const size_t r, const size_t c, const Item& init_value)
    : rows_(r), cols_(c), matrix_(_AllocateMatrixData(r, c)) {
  if (r == 0 || c == 0) {
    throw std::out_of_range(
        "Incorrect input, rows/cols should be more than zero");
  }
  for (size_t i = 0; i < r * c; ++i) {
    this->matrix_[i] = init_value;
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(_AllocateMatrixData(rows_, cols_)) {
  for (size_t i = 0; i < this->rows_ * this->cols_; ++i) {
    this->matrix_[i] = other.matrix_[i];
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { this->_Deallocate(); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (&other != this) {
    this->_Deallocate();

    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = _AllocateMatrixData(this->rows_, this->cols_);

    for (size_t i = 0; i < this->rows_ * this->cols_; ++i) {
      this->matrix_[i] = other.matrix_[i];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (&other != this) {
    this->_Deallocate();

    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix::Item& S21Matrix::operator()(const size_t i, const size_t j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Index out of range");
  }
  return this->matrix_[_GetDataIdx(i, j)];
}

const S21Matrix::Item& S21Matrix::operator()(const size_t i,
                                             const size_t j) const {
  return this->matrix_[_GetDataIdx(i, j)];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const Item num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  S21Matrix res(*this);
  return res.EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const Item num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;

  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    res = false;
  } else {
    for (size_t i = 0; i < this->rows_ * this->cols_ && res; ++i) {
      if (std::fabs(this->matrix_[i] - other.matrix_[i]) > 1e-6) {
        res = false;
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Invalid matrix's sizes");
  }
  for (size_t i = 0; i < this->rows_ * this->cols_; ++i) {
    this->matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Invalid matrix's sizes");
  }
  for (size_t i = 0; i < this->rows_ * this->cols_; ++i) {
    this->matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const Item num) {
  for (size_t i = 0; i < this->rows_ * this->cols_; ++i) {
    this->matrix_[i] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument("Invalid matrix's sizes");
  }
  S21Matrix res(this->rows_, other.cols_);
  for (size_t i = 0; i < this->rows_; ++i) {
    for (size_t j = 0; j < other.cols_; ++j) {
      for (size_t k = 0; k < this->cols_; ++k) {
        size_t r = res._GetDataIdx(i, j);
        size_t t = this->_GetDataIdx(i, k);
        size_t o = other._GetDataIdx(k, j);
        res.matrix_[r] += this->matrix_[t] * other.matrix_[o];
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(this->cols_, this->rows_);
  for (size_t i = 0; i < this->rows_; ++i) {
    for (size_t j = 0; j < this->cols_; ++j) {
      size_t m = this->_GetDataIdx(i, j);
      size_t n = res._GetDataIdx(j, i);
      res.matrix_[n] = this->matrix_[m];
    }
  }
  return res;
}

S21Matrix S21Matrix::_Minor(size_t row, size_t col) const {
  S21Matrix MinorMatrix(this->rows_ - 1, this->cols_ - 1);
  size_t MinorI = 0;
  for (size_t i = 0; i < this->rows_; ++i) {
    if (i == row) continue;
    size_t MinorJ = 0;
    for (size_t j = 0; j < this->cols_; ++j) {
      if (j == col) continue;
      size_t m = MinorMatrix._GetDataIdx(MinorI, MinorJ);
      size_t o = this->_GetDataIdx(i, j);
      MinorMatrix.matrix_[m] = this->matrix_[o];
      MinorJ++;
    }
    MinorI++;
  }
  return MinorMatrix;
}

S21Matrix::Item S21Matrix::Determinant() const {
  if (this->rows_ != this->cols_) {
    throw std::domain_error("Matrix isn't square");
  }
  Item res = 0.0;
  if (this->rows_ == 1) {
    res = this->matrix_[0];
  } else if (this->rows_ == 2) {
    res = this->matrix_[0] * this->matrix_[3] -
          this->matrix_[1] * this->matrix_[2];
  } else {
    for (size_t i = 0; i < this->cols_; ++i) {
      S21Matrix MinorMatrix = this->_Minor(0, i);
      size_t t = this->_GetDataIdx(0, i);
      res += this->matrix_[t] * std::pow(-1.0, i) * MinorMatrix.Determinant();
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (this->rows_ != this->cols_) {
    throw std::domain_error("Matrix isn't square");
  }
  S21Matrix res(this->rows_, this->cols_);
  for (size_t i = 0; i < this->rows_; ++i) {
    for (size_t j = 0; j < this->cols_; ++j) {
      S21Matrix MinorMatrix = this->_Minor(i, j);
      size_t n = res._GetDataIdx(i, j);
      res.matrix_[n] = std::pow(-1.0, i + j) * MinorMatrix.Determinant();
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  Item d = this->Determinant();
  if (std::fabs(d) < 1e-6) {
    throw std::invalid_argument("Determinant can't be equal zero");
  }
  S21Matrix res(this->rows_, this->cols_);
  if (this->rows_ == 1) {
    res.matrix_[0] = 1.0 / this->matrix_[0];
  } else {
    S21Matrix comp = this->CalcComplements();
    res = comp.Transpose();
    res.MulNumber(1.0 / d);
  }
  return res;
}

// int main () {

//     S21Matrix a(4, 2, 1.0);
//     a.PrintlnMatrix();
//     S21Matrix b(4, 4, 2.0);
//     b.PrintlnMatrix();
//     S21Matrix c = b.InverseMatrix();
//     c.PrintlnMatrix();
//     // S21Matrix::Item c = b.Determinant();
//     // std::cout << c << std::endl;
//     return 0;
// }