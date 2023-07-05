#include "s21_matrix_oop.h"

//Выделение памяти

void S21Matrix::S21CreateMatrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

//Для копирования другой матрицы

void S21Matrix::OtherMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

//Для освобожения памяти

void S21Matrix::CleanMatrix() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
}

//Проверка матриц на равенство

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 0.0000001) {
          result = false;
          break;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

//Прибавление второй матрицы к текущей

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument("различная размерность матриц");
  }
}

//Вычитание из текущей матрицы другую

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument("различная размерность матриц");
  }
}

//Умножает текущую матрицу на число

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

//Умножает текущую матрицу на вторую

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "число столбцов первой матрицы не равно числу строк второй матрицы");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      res.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

//Создает новую транспонированную матрицу из текущей и возвращает ее

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

//Возвращения минора матрицы

S21Matrix S21Matrix::GetMinor(int rows, int cols) const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Размеры матрицы не равны");
  }
  S21Matrix temp(rows_ - 1, cols_ - 1);
  int r = 0;
  for (int i = 0; i < temp.rows_; ++i) {
    if (i == rows) r = 1;
    int k = 0;
    for (int j = 0; j < temp.cols_; ++j) {
      if (j == cols) k = 1;
      temp.matrix_[i][j] = matrix_[i + r][j + k];
    }
  }
  return temp;
}

//Вычисляет и возвращает определитель текущей матрицы

double S21Matrix::Determinant() {
  if (rows_ <= 0 || rows_ != cols_) {
    throw std::invalid_argument("Размеры матрицы не равны");
  }
  double result = 0.0;
  if (cols_ == 1) {
    result = matrix_[0][0];
  } else if (cols_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < cols_; ++i) {
      S21Matrix temp = this->GetMinor(0, i);
      result += matrix_[0][i] * pow(-1.0, i) * temp.Determinant();
    }
  }
  return result;
}

//Вычисляет матрицу алгебраических дополнений

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix temp(rows_, cols_);
  if (rows_ != cols_ || rows_ <= 1) {
    throw std::invalid_argument("матрица не является квадратной");
  }
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      S21Matrix minor_matrix = GetMinor(i, j);
      temp.matrix_[i][j] = pow(-1.0, i + j) * minor_matrix.Determinant();
    }
  }
  return temp;
}

//Вычисляет и возвращает обратную матрицу

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0 || rows_ != cols_) {
    throw std::invalid_argument("определитель матрицы равен 0");
  }
  S21Matrix res = CalcComplements().Transpose();
  res *= (1 / det);
  return res;
}

//Получение Rows - рядов(сторк), и Cols - столбцов
//Установка Rows - рядов(строк), и Cols - столбцов

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  S21Matrix tmp(rows, cols_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[i][j] = (i < rows_) ? matrix_[i][j] : 0;
    }
  }
  *this = tmp;
}

void S21Matrix::SetCols(int cols) {
  S21Matrix tmp(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      tmp.matrix_[i][j] = (i < cols_) ? matrix_[i][j] : 0;
    }
  }
  *this = tmp;
}
