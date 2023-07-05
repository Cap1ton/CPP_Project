#include "s21_matrix_oop.h"

// сложение двух матриц

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

// вычитание одной матрицы из другой

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

// умножение матриц

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

// умножение матрицы на число

S21Matrix S21Matrix::operator*(const double &num) {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

// проверка на равенство матриц (EqMatrix)

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

// присвоение матрице значений другой матрицы

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  CleanMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  S21CreateMatrix();
  OtherMatrix(other);
  return *this;
}

// присвоение сложения (SumMatrix)

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

// присвоение разности (SubMatrix)

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

// присвоение умножения (MulMatrix)

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

// присвоение умножения (MulNumber)

void S21Matrix::operator*=(const double &num) { MulNumber(num); }

// индексация по элементам матрицы (строка, колонка)

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::invalid_argument("индекс за пределами матрицы");
  }
  return matrix_[row][col];
}