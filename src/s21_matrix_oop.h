#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class S21Matrix {
    private:
        int rows_, cols_; //Количество строк и столбцов
        double **matrix_; //Указатель на матрицу

        void Allocate();
        void Deallocate();
        S21Matrix Minor();

    public:
        // Constructors & Destructors
        S21Matrix(); // Конструктор, инициализирующий матрицу заранее заданной размерностью
        S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
            Allocate();
        }; //Параметризированный конструктор с количеством строк и столбцов
        S21Matrix(const S21Matrix& other) {
            *this = std::move(other);
        }; //Конструктор копирования
        S21Matrix(S21Matrix&& other); //Конструктор переноса
        ~S21Matrix(); // Деструктор

        // Accessors
        int GetRows() const;
        int GetCols() const;
        int SetRows(int rows);
        int SetCols(int cols);

        // Operators
        S21Matrix& operator=(const S21Matrix& other) {
            if (this != &other) {
                std::swap(other.rows_, rows_);
                std::swap(other.cols_, cols_);
            }
            return *this;
        };                   // assignment operator overload
        S21Matrix& operator=(S21Matrix&& other); 
        int& operator()(int row, int col);                          // index operator overload
        int& operator()(int row, int col) const;
        S21Matrix& operator+=(const S21Matrix& other);                            
        S21Matrix operator+(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
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
