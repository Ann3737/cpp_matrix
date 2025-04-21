#include "s21_matrix_oop.h"
#include <iostream>

void S21Matrix::PrintlnMatrix() const {
    for (size_t i = 0; i < this->rows_; ++i) {
        auto sep = "";
        for (size_t j = 0; j < this->cols_; ++j) {
            const size_t m = this->_GetDataIdx(i, j);
            std::cout << sep << this->matrix_[m];
            sep = " ";
        }
        std::cout << std::endl;
    }
}

size_t S21Matrix::_GetDataIdx(const size_t i, const size_t j) const {
    return i * this->cols_ + j;
}

S21Matrix::ItemsPtr S21Matrix::_AllocateMatrixData(const size_t r, const size_t c) {
    return (r * c != 0) ? new S21Matrix::Item[r * c]
                        : nullptr;
}

void S21Matrix::_DeallocateMatrixData(ItemsPtr data) {
    delete[] data;
}

S21Matrix::S21Matrix()
    : S21Matrix(kDefaultRowsNum, kDefaultColsNum)
{
}

S21Matrix::S21Matrix(const size_t r, const size_t c, const Item& init_value)
    : rows_(r)
    , cols_(c)
    , matrix_(_AllocateMatrixData(r, c))
{
    for (size_t i = 0; i < r * c; ++i) {
        this->matrix_[i] = init_value;
    }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_)
    , cols_(other.cols_)
    , matrix_(_AllocateMatrixData(rows_, cols_))
{
    for (size_t i = 0; i < this->rows_ * this->cols_; ++i) {
        this->matrix_[i] = other.matrix_[i];
    }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_)
    , cols_(other.cols_)
    , matrix_(other.matrix_)  
{
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    this->_Deallocate();
}

void S21Matrix::_Deallocate() {
    if (this->matrix_ != nullptr) {
        _DeallocateMatrixData(this->matrix_);
    }
}

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