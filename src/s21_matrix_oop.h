#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <iostream>
#include <cmath>
#include <algorithm>

class S21Matrix {
    private:
        int rows_, cols_; //Количество строк и столбцов
        double **matrix_; //Указатель на матрицу
        void Allocate();
        void Deallocate(int rows, int cols);
        void FreeMatrix(const S21Matrix& other);
        S21Matrix Minor();

    public:
        void PrintMatrix(const S21Matrix& other);
        // Constructors & Destructors
        S21Matrix(); // Дефолтный констуктор
        S21Matrix(int rows, int cols); //Параметризированный конструктор
        S21Matrix(const S21Matrix& other); //Конструктор копирования
        S21Matrix(S21Matrix&& other); //Конструктор переноса
        ~S21Matrix(); // Деструктор

        // Accessors & mutators
        int GetRows() const {return rows_;};
        int GetCols() const {return cols_;};
        int SetRows(int rows) {rows_ = rows; return rows_;};
        int SetCols(int cols) {cols_ = cols; return cols_;};

        // Operators
        S21Matrix& operator=(const S21Matrix& other);
        S21Matrix& operator=(S21Matrix&& other); 
        double &operator()(int i, int j); // записывает элемент по i j месту
        double &operator()(int i, int j) const; //считывает элемент по i j месту
        S21Matrix& operator+=(const S21Matrix& other);                            
        S21Matrix operator+(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
        S21Matrix operator*(const S21Matrix& other);
        friend S21Matrix operator*(const double num, const S21Matrix& other);
        S21Matrix operator*=(const S21Matrix& other);
        friend S21Matrix operator*=(const double num, const S21Matrix& other);
        bool operator==(const S21Matrix& other);
        
        // Methods
        bool EqMatrix(const S21Matrix& other);
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();
};

#endif
