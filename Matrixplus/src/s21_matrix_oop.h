#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  //Базовый конструктор
  S21Matrix();
  //Пользовательские параметры
  S21Matrix(int rows, int cols);
  //Копирование матрицы
  S21Matrix(const S21Matrix &other);
  //Перенос матрицы
  S21Matrix(S21Matrix &&other);
  //Деструктор
  ~S21Matrix();

  //Проверка матриц на равенство
  bool EqMatrix(const S21Matrix &other);
  //Прибавление второй матрицы к текущей
  void SumMatrix(const S21Matrix &other);
  //Вычитание из текущей матрицы другую
  void SubMatrix(const S21Matrix &other);
  //Умножает текущую матрицу на число
  void MulNumber(const double num);
  //Умножает текущую матрицу на вторую
  void MulMatrix(const S21Matrix &other);
  //Создает новую транспонированную матрицу из текущей и возвращает ее
  double Determinant();
  //Вычисляет и возвращает определитель текущей матрицы
  S21Matrix Transpose();
  //Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
  S21Matrix CalcComplements();
  //Вычисляет и возвращает обратную матрицу
  S21Matrix InverseMatrix();

  //Сложение двух матриц
  S21Matrix operator+(const S21Matrix &other);
  //Вычитание одной матрицы из другой
  S21Matrix operator-(const S21Matrix &other);
  //Умножение матриц
  S21Matrix operator*(const S21Matrix &other);
  //Умножение матрицы на число
  S21Matrix operator*(const double &num);
  //Проверка на равенство матриц (EqMatrix)
  bool operator==(const S21Matrix &other);
  //Присвоение матрице значений другой матрицы
  S21Matrix &operator=(const S21Matrix &other);
  //Присвоение сложения (SumMatrix)
  void operator+=(const S21Matrix &other);
  //Присвоение разности (SubMatrix)
  void operator-=(const S21Matrix &other);
  //Присвоение умножения (MulMatrix)
  void operator*=(const S21Matrix &other);
  //Присвоение умножения (MulNumber)
  void operator*=(const double &num);
  //Индексация по элементам матрицы (строка, колонка)
  double &operator()(int row, int col);

  //Перезадаём кол-во строк
  void SetRows(int rows);
  //Перезадаём кол-во столбцов
  void SetCols(int cols);
  //Получаем колл-во строк
  int GetRows() const;
  //Получаем кол-во столбцов
  int GetCols() const;

 private:
  //Выделение памяти
  void S21CreateMatrix();
  //Копирование другой матрицы
  void OtherMatrix(const S21Matrix &matrix);
  //Очистка памяти
  void CleanMatrix();
  //Возвращения минора матрицы
  S21Matrix GetMinor(int rows, int cols) const;
};

#endif  // SRC_S21_MATRIX_OOP_H_