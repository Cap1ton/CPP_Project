#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

using namespace std;

TEST(Constructors, Default) {
  S21Matrix m1;
  EXPECT_EQ(1, m1.GetRows());
  EXPECT_EQ(1, m1.GetCols());
}

TEST(Constructors, With_parameters) {
  S21Matrix m1(4, 5);
  EXPECT_EQ(4, m1.GetRows());
  EXPECT_EQ(5, m1.GetCols());
  EXPECT_NO_THROW(S21Matrix m1(4, 5));

  EXPECT_ANY_THROW(S21Matrix m2(0, 8));
  EXPECT_ANY_THROW(S21Matrix(-8, 8));
}

TEST(Constructors, Copy) {
  S21Matrix m1(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
    }
  }

  S21Matrix m2(m1);
  EXPECT_EQ(m1.GetRows(), m2.GetRows());
  EXPECT_EQ(m1.GetCols(), m2.GetCols());
  for (int i = 0; i < m2.GetRows(); i++) {
    for (int j = 0; j < m2.GetCols(); j++) {
      EXPECT_EQ(m1(i, j), m2(i, j));
    }
  }
}

TEST(Constructors, Move) {
  S21Matrix m2(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m2(i, j) = i * j;
    }
  }
  S21Matrix res1(m2);
  S21Matrix m1(move(m2));
  EXPECT_EQ(m1.GetRows(), res1.GetRows());
  EXPECT_EQ(m1.GetCols(), res1.GetCols());
  EXPECT_EQ(true, m1.EqMatrix(res1));
  EXPECT_EQ(false, m1.EqMatrix(m2));
}

TEST(Constructors, Destructor) {
  S21Matrix m1(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
    }
  }
  m1.~S21Matrix();
  EXPECT_EQ(0, m1.GetRows());
  EXPECT_EQ(0, m1.GetCols());
}

TEST(Method, Equal) {
  S21Matrix m1(4, 5), test1(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
      test1(i, j) = i * j + 1;
    }
  }
  S21Matrix test2(m1);
  EXPECT_EQ(false, m1.EqMatrix(test1));
  EXPECT_EQ(true, m1.EqMatrix(test2));
}

TEST(Method, Sum) {
  S21Matrix m1(4, 5), m2(4, 5), m3(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
      m2(i, j) = i * j + 1;
      m3(i, j) = i * j + 2;
    }
  }
  m1.SumMatrix(m2);
  EXPECT_EQ(false, m1.EqMatrix(m3));
}

TEST(Method, Sub) {
  S21Matrix m1(4, 5), m2(4, 5), m3(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
      m2(i, j) = i * j + 1;
      m3(i, j) = i * j + 2;
    }
  }
  m1.SubMatrix(m2);
  EXPECT_EQ(false, m1.EqMatrix(m3));
}

TEST(Method, MulNumber) {
  S21Matrix m1(4, 5), m2(4, 5);
  int num = 2;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
      m2(i, j) = i * j + 1;
    }
  }
  m1.MulNumber(num);
  EXPECT_EQ(false, m1.EqMatrix(m2));
}

TEST(Method, MulMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      m1(i, j) = 2;
      m2(i, j) = 3;
      m3(i, j) = 12;
    }
  }
  m1.MulMatrix(m2);

  S21Matrix m2_2(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      m2_2(i, j) = i * j;
    }
  }

  EXPECT_EQ(true, m1.EqMatrix(m3));
  EXPECT_ANY_THROW(m1.MulMatrix(m2_2));
}

TEST(Method, Transpose) {
  S21Matrix m1(3, 3), m2(3, 3);
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 4, 7, 2, 5, 8, 3, 6, 9};
  int tmp = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m1(i, j) = arr[tmp];
      tmp++;
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m2(i, j) = arr[tmp];
      tmp++;
    }
  }
  S21Matrix m3(m1.Transpose());
  ASSERT_TRUE(m3 == m2);
}

TEST(Method, Complements) {
  S21Matrix m1(4, 5);
  EXPECT_ANY_THROW(m1.CalcComplements());
}

TEST(Method, Complements2) {
  int n = 1, add = 1;
  S21Matrix m1(3, 3), res1(3, 3), test1(2, 2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m1(i, j) = n;
      n += add;
    }
  }
  test1 = m1.CalcComplements();
  res1(0, 0) = -3;
  res1(0, 1) = 6;
  res1(0, 2) = -3;
  res1(1, 0) = 6;
  res1(1, 1) = -12;
  res1(1, 2) = 6;
  res1(2, 0) = -3;
  res1(2, 1) = 6;
  res1(2, 2) = -3;
  EXPECT_EQ(true, test1.EqMatrix(res1));
}

TEST(Method, Determinant) {
  double arr[] = {9.9, 2, 3, 4, 5, 6, 7, 8, 9};
  int tmp = 0;
  S21Matrix m1(3, 3);
  for (int i = 1; i < 3; i++) {
    for (int j = 1; j < 3; j++) {
      m1(i, j) = arr[tmp];
      tmp++;
    }
  }
  double m2;
  m2 = m1.Determinant();
  EXPECT_EQ(0, m2);

  S21Matrix m3(4, 5);
  EXPECT_ANY_THROW(m3.Determinant());
}

TEST(DeterminantTest, MethodTest) {
  S21Matrix a(1, 1);
  a(0, 0) = 9;
  ASSERT_NEAR(a.Determinant(), 9, 1e-7);
}

TEST(Methods, Inverse) {
  S21Matrix m1(3, 3);
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int tmp = 0;
  for (int i = 1; i < 3; i++) {
    for (int j = 1; j < 3; j++) {
      m1(i, j) = arr[tmp];
      tmp++;
    }
  }
  EXPECT_ANY_THROW(m1.InverseMatrix());
}

TEST(Methods, Inverse2) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 6;
  m1(0, 2) = 4;
  m1(1, 0) = 9;
  m1(1, 1) = 2;
  m1(1, 2) = 8;
  m1(2, 0) = 5;
  m1(2, 1) = 7;
  m1(2, 2) = 3;
  S21Matrix test1 = m1.InverseMatrix();
  S21Matrix res1(3, 3);
  res1(0, 0) = -0.208333333;
  res1(0, 1) = 0.0416666667;
  res1(0, 2) = 0.1666666667;
  res1(1, 0) = 0.0541666667;
  res1(1, 1) = -0.070833333;
  res1(1, 2) = 0.1166666667;
  res1(2, 0) = 0.2208333333;
  res1(2, 1) = 0.0958333333;
  res1(2, 2) = -0.216666667;
  EXPECT_EQ(true, test1.EqMatrix(res1));
}

TEST(Operator, Sum) {
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 2);
  for (int i = 1; i < 2; i++) {
    for (int j = 1; j < 2; j++) {
      m1(i, j) = i * j * 6.6;
      m2(i, j) = i * j * 7.7;
      m3(i, j) = i * j * (6.6 + 7.7);
    }
  }
  S21Matrix m4 = m1 + m2;
  EXPECT_EQ(true, m3.EqMatrix(m4));
}

TEST(Operator, Sub) {
  int arr1[] = {3, 2, -6, 0};
  int arr2[] = {-7, 0, -3, 2};
  int arr3[] = {10, 2, -3, -2};
  int tmp = 0;
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 2);
  for (int i = 1; i < 2; i++) {
    for (int j = 1; j < 2; j++) {
      m1(i, j) = arr1[tmp];
      m2(i, j) = arr2[tmp];
      m3(i, j) = arr3[tmp];
      tmp++;
    }
  }
  S21Matrix m4 = m1 - m2;
  EXPECT_EQ(true, m3.EqMatrix(m4));
}

TEST(Operator, MulNum) {
  S21Matrix m1(3, 3), m2(3, 3);
  for (int i = 1; i < 3; ++i) {
    for (int j = 1; j < 3; ++j) {
      m1(i, j) = 2;
      m2(i, j) = 2 * 5;
    }
  }
  S21Matrix m3 = m1 * 5;
  EXPECT_EQ(true, m2.EqMatrix(m3));
}

TEST(Operator, MulMat) {
  S21Matrix m1(2, 4), m2(4, 1), m3(2, 1);
  int arr[] = {1, 2, 3, 4, 5, 6, 7, -8, 10, 9, 8, -7, 24, 216};
  int tmp = 0;
  for (int i = 1; i < 2; ++i) {
    for (int j = 1; j < 4; ++j) {
      m1(i, j) = arr[tmp];
      tmp++;
    }
  }
  for (int i = 1; i < 4; ++i) {
    for (int j = 1; j < 1; ++j) {
      m2(i, j) = arr[tmp];
      tmp++;
    }
  }
  for (int i = 1; i < 2; ++i) {
    for (int j = 1; j < 1; ++j) {
      m3(i, j) = arr[tmp];
      tmp++;
    }
  }
  m1.MulMatrix(m2);
  ASSERT_TRUE(m1 == m3);
}

TEST(Operator, MulMat2) {
  S21Matrix m1(3, 3), m2(3, 3), m3(3, 3), m4(3, 3), m5(1, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m1(i, j) = 4;
      m2(i, j) = 4;
      m3(i, j) = 48;
    }
  }
  m4 = m1 * m2;
  EXPECT_EQ(true, m3.EqMatrix(m4));

  EXPECT_ANY_THROW(m1 * m5);
}

TEST(Operator, Equal) {
  S21Matrix m1(21, 42), m2(21, 42), m3(8, 21);
  EXPECT_EQ(true, m1 == m2);
  EXPECT_NE(true, m1 == m3);
}

TEST(EqMatrixTest, MethodTest) {
  S21Matrix m1(3, 3), m2(3, 3);
  ASSERT_TRUE(m1 == m2);
}

TEST(OperatorEqMatrix2, MethodTest) {
  S21Matrix m1(3, 3), m2(2, 2);
  ASSERT_FALSE(m1 == m2);
}

TEST(OperatorEqMatrix3, MethodTest) {
  S21Matrix m1(3, 4), m2(3, 4), m3(3, 33);
  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
}

TEST(OperatorEqMatrix4, MethodTest) {
  S21Matrix m1(3, 3), m2(3, 33);
  m1 = m2;
  EXPECT_TRUE(m1 == m2);
}

TEST(EqMatrix1, MethodTest) {
  S21Matrix m1(21, 42), m2(21, 42), m3(8, 21);
  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_FALSE(m1.EqMatrix(m3));
}
TEST(AccessorMutator1, GetRowsTest) {
  S21Matrix m1(3, 4);
  EXPECT_EQ(m1.GetRows(), 3);
}

TEST(AccessorMutator2, GetColsTest) {
  S21Matrix m1(3, 4);
  EXPECT_EQ(m1.GetCols(), 4);
}

TEST(AccessorMutator3, SetRowsTest) {
  S21Matrix m1(4, 3);
  m1.SetRows(3);
  EXPECT_EQ(m1.GetRows(), 3);
  EXPECT_FALSE(m1.GetRows() == 4);
}

TEST(AccessorMutator4, SetColsTest) {
  S21Matrix m1(3, 4);
  m1.SetCols(3);
  EXPECT_EQ(m1.GetCols(), 3);
  EXPECT_FALSE(m1.GetCols() == 4);
}

TEST(AccessorMutator5, MinusTest) {
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 2);
  double arr[] = {2.4, 5.8,   3.2,  333.89, 3.6,  -5.8,
                  3.8, -0.89, -1.2, 11.6,   -0.6, 334.78};
  int t1 = 0, t2 = 4, t3 = 8;
  for (int i = 1; i < 2; i++) {
    for (int j = 1; j < 2; j++) {
      m1(i, j) = arr[t1];
      m2(i, j) = arr[t2];
      m3(i, j) = arr[t3];
      t1++;
      t2++;
      t3++;
    }
  }
  ASSERT_TRUE(m1 - m2 == m3);
}

TEST(AccessorMutator6, PlusEqualTest) {
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 2);
  for (int i = 1; i < 2; ++i) {
    for (int j = 1; j < 2; ++j) {
      m1(i, j) = i * j * 6.6;
      m2(i, j) = i * j * 7.7;
      m3(i, j) = i * j * (6.6 + 7.7);
    }
  }
  m1 += m2;
  ASSERT_TRUE(m1 == m3);
}

TEST(AccessorMutator7, MinusEqualTest) {
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 2);
  for (int i = 1; i < 2; ++i) {
    for (int j = 1; j < 2; ++j) {
      m1(i, j) = i * j * 6.6;
      m2(i, j) = i * j * 7.7;
      m3(i, j) = i * j * (6.6 - 7.7);
    }
  }
  m1 -= m2;
  ASSERT_TRUE(m1 == m3);
}

TEST(AccessorMutator8, MultEqualTest) {
  S21Matrix m1, m2, m3;
  m1 *= m2;
  EXPECT_EQ(true, m1.EqMatrix(m3));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
