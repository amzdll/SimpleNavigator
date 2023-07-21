#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class Matrix {
 public:
  Matrix();
  explicit Matrix(unsigned int rows, unsigned int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other) noexcept;
  ~Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const Matrix &other);
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const Matrix &other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();

  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix operator*(double num);
  Matrix operator*(const Matrix &other);
  bool operator==(const Matrix &other);
  Matrix &operator=(const Matrix &other);
  Matrix operator+=(const Matrix &other);
  Matrix operator-=(const Matrix &other);
  Matrix operator*=(double num);
  Matrix operator*=(const Matrix &other);
  double &operator()(int i, int j);

  void FillingMatrix();
  void ZeroingMatrix();

 private:
  int rows_, cols_;
  double **matrix_;

  void InitMatrix();
  bool MatrixIsExtend() const;
  bool SizeComparison(const Matrix &other) const;
  void ShortenedCopy(const Matrix &other, int row, int column);
  void DeleteMatrix();
};

#endif  //  CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_
