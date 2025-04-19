#include "s21_matrix_oop.h"

void S21Matrix::PrintMatrix(const S21Matrix& other) {
    if(other.matrix_) {
        int count = 0;
        for(int i = 0; i < rows_; ++i) {
            for(int j = 0; j < cols_; ++j) {
                other.matrix_[i][j] = count;
                std::cout << other.matrix_[i][j] << " ";
                count++;
            }
        std::cout << std::endl;
        }  
    }
}

void S21Matrix::FreeMatrix(const S21Matrix& other) {
    if (other.matrix_) {
        for (int i = 0; i < other.rows_; ++i) {
            delete [] other.matrix_[i];
        }
        delete [] other.matrix_;
    }
}

void S21Matrix::Allocate() {
    this->matrix_ = new double* [rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double [cols_];
    }
}

void S21Matrix::Deallocate(int rows, int cols) {
    S21Matrix b(rows, cols);
    b.matrix_ = new double *[rows];
    for (int i = 0; i < rows; ++i) {
        b.matrix_[i] = new double[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            b.matrix_[i][j] = matrix_[i][j];
        }
    }
    FreeMatrix(*this);
    rows_ = rows;
    cols_ = cols;
    matrix_ = b.matrix_;
    b.rows_ = 0;
    b.cols_ = 0;
    b.matrix_ = nullptr;
}

S21Matrix::S21Matrix() {
    this->rows_ = 3;
    this->cols_ = 3;
    Allocate();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if(rows <= 0 || cols <= 0) {
        throw std::out_of_range("Incorrect input, rows and cols must be more than zero");
    } else {
        this->rows_ = rows;
        this->cols_ = cols;
    }
    Allocate();
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    Allocate();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
        *this = std::move(other);
    } else {
        Deallocate(other.rows_, other.cols_);
        *this = std::move(other);
    }
    
}

S21Matrix::~S21Matrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; ++i) {
            delete [] matrix_[i];
        }
        delete [] matrix_;
    }
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
    if (this != &other) {
        FreeMatrix(*this);
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_ = other.matrix_;
        other.rows_ = 0;
        other.cols_ = 0;
        other.matrix_ = nullptr;
    }
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other){
    SumMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other){
    S21Matrix result(*this);
    result.SumMatrix(other);
    return result;
}
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        *this = std::move(S21Matrix(other));
    }
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SubMatrix(other);
    return result;
}

// записывает элемент по i j месту
double &S21Matrix::operator()(int i, int j) {
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}

//считывает элемент по i j месту
double &S21Matrix::operator()(int i, int j) const {
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}


/*S21Matrix S21Matrix::operator*(const S21Matrix& other) {};

friend S21Matrix S21Matrix::operator*(const double num, const S21Matrix& other) {

}

friend S21Matrix S21Matrix::operator*=(const double num, const S21Matrix& other) {

}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {

}

bool S21Matrix::operator==(const S21Matrix& other) {
    bool result = EqMatrix(other);
    return result;
} */
        

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    bool result = true;
    if (other.matrix_ == nullptr || matrix_ == nullptr) {
        result = false;
    } else if (rows_ != other.rows_ || cols_ != other.cols_) {
        result = false;
    } else {
        for (int i = 0; i < rows_ && result; ++i) {
            for (int j = 0; j < cols_ && result; ++j) {
                if (fabs(other.matrix_[i][j] - matrix_[i][j]) > 1e-6) {
                    result = false;
                }
            }
        }
    }
    return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (other.matrix_ == nullptr || matrix_ == nullptr) {
        throw std::out_of_range("Incorrect matrix");
    } else if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::out_of_range("Different size of matrix");
    } else {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
            }
        }
    }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (other.matrix_ == nullptr || matrix_ == nullptr) {
        throw std::out_of_range("Incorrect matrix");
    } else if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::out_of_range("Different size of matrix");
    } else {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
            }
        }
    }

}
/*void S21Matrix::MulNumber(const double num) {

}
void S21Matrix::MulMatrix(const S21Matrix& other) {

}
S21Matrix S21Matrix::Transpose() {

}
S21Matrix S21Matrix::CalcComplements() {

}
double S21Matrix::Determinant() {

}
S21Matrix S21Matrix::InverseMatrix() {

} */

int main() {
    S21Matrix a;
    a.PrintMatrix(a);
    S21Matrix b(3, 3);
    b.PrintMatrix(b);
    a.SumMatrix(b);
    for(int i = 0; i < a.GetRows(); ++i) {
        for(int j = 0; j < a.GetCols(); ++j) {
            std::cout << a(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}