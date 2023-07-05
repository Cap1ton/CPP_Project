#include "s21_matrix_oop.h"

//Базовый конструктор, инициализирующий матрицу некоторой заранее заданной
//размерностью

S21Matrix::S21Matrix() {
  rows_ = cols_ = 1;
  S21CreateMatrix();
}

//Параметризированный конструктор с количеством строк и столбцов

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument(
        "Столбцы и троки не могут быть меньше или равны 0");
  S21CreateMatrix();
}

//Конструктор копирования

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  S21CreateMatrix();
  OtherMatrix(other);
}

//Конструктор переноса

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

//Деструктор

S21Matrix::~S21Matrix() {
  if (matrix_) CleanMatrix();
  matrix_ = nullptr;
  rows_ = cols_ = 0;
}