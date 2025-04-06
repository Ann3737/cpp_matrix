#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <iostream>
#include <cmath>
#include <vector>

class S21Matrix {
    private:
        int rows_, cols_; //Количество строк и столбцов
        double **matrix_; //Указатель на матрицу

    public:
        S21Matrix(); // Конструктор, инициализирующий матрицу заранее заданной размерностью
        S21Matrix(int rows, int cols); //Параметризированный конструктор с количеством строк и столбцов
        S21Matrix(const S21Matrix& other); //Конструктор копирования
        S21Matrix(S21Matrix&& other); //Конструктор переноса
        ~S21Matrix(); // Деструктор

        S21Matrix& operator=(const S21Matrix& other);                   // assignment operator overload
        int& operator()(int row, int col);                          // index operator overload
        int& operator()(int row, int col) const;
        S21Matrix& operator+=(const S21Matrix& other);                            
        S21Matrix operator+(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);


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
