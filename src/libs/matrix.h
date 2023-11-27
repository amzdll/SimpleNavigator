#ifndef SIMPLENAVIGATOR_SRC_INCLUDE_S21_MATRIX_H_
#define SIMPLENAVIGATOR_SRC_INCLUDE_S21_MATRIX_H_

#include <cmath>
#include <iostream>
#include <type_traits>

namespace s21 {
template <class T>
class matrix {
  static_assert(std::is_arithmetic_v<T>,
                "Matrix<T> can only be instantiated with numeric types.");
  static_assert(!std::is_same_v<T, char>,
                "Matrix<T> can only be instantiated with numeric types.");

 public:
  matrix();
  explicit matrix(unsigned int rows, unsigned int cols);
  matrix(const matrix &other);
  matrix(matrix &&other) noexcept;
  ~matrix();

  [[nodiscard]] int GetRows() const;
  [[nodiscard]] int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const matrix &other);
  void SumMatrix(const matrix &other);
  void SubMatrix(const matrix &other);
  void MulNumber(double num);
  void MulMatrix(const matrix &other);
  matrix Transpose();
  matrix CalcComplements();
  double Determinant();
  matrix InverseMatrix();

  matrix operator+(const matrix &other);
  matrix operator-(const matrix &other);
  matrix operator*(double num);
  matrix operator*(const matrix &other);
  bool operator==(const matrix &other);
  matrix &operator=(const matrix &other);
  matrix operator+=(const matrix &other);
  matrix operator-=(const matrix &other);
  matrix operator*=(double num);
  matrix operator*=(const matrix &other);
  T &operator()(int i, int j);
  T *operator[](size_t row);

  void FillingMatrix();
  void ZeroingMatrix();

 private:
  size_t rows_, cols_;
  T **matrix_;

  void InitMatrix();
  [[nodiscard]] bool MatrixIsExtend() const;
  bool SizeComparison(const matrix &other) const;
  void ShortenedCopy(const matrix &other, int row, int column);
  void DeleteMatrix();
};

template <class T>
matrix<T>::matrix() : rows_(0), cols_(0), matrix_(nullptr) {
  InitMatrix();
}

template <class T>
matrix<T>::matrix(unsigned int rows, unsigned int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new T *[rows_];
  for (size_t i = 0; i < rows_; ++i) {
    matrix_[i] = new T[cols_];
  }
  ZeroingMatrix();
}

template <class T>
matrix<T>::matrix(const matrix &other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new T *[other.rows_];
    for (size_t i = 0; i < other.rows_; ++i) {
      matrix_[i] = new T[cols_];
    }
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } else {
    InitMatrix();
  }
}

template <class T>
matrix<T>::matrix(matrix &&other) noexcept {
  if (other.MatrixIsExtend() && this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  } else {
    InitMatrix();
  }
}

template <class T>
matrix<T>::~matrix() {
  DeleteMatrix();
}
template <class T>
int matrix<T>::GetRows() const {
  return matrix_ ? rows_ : 0;
}
template <class T>
int matrix<T>::GetCols() const {
  return matrix_ ? cols_ : 0;
}
template <class T>
void matrix<T>::SetRows(int rows) {
  if (rows != rows_) {
    if (matrix_) {
      matrix temp_matrix(rows, cols_);
      for (int i = 0; i < (rows < rows_ ? rows : rows_); ++i) {
        for (int j = 0; j < cols_; ++j) {
          temp_matrix.matrix_[i][j] = matrix_[i][j];
        }
      }
      DeleteMatrix();
      rows_ = rows;
      cols_ = temp_matrix.cols_;
      matrix_ = temp_matrix.matrix_;
      temp_matrix.matrix_ = nullptr;
    }
  }
}

template <class T>
void matrix<T>::SetCols(int cols) {
  if (cols != cols_) {
    if (matrix_) {
      matrix temp_matrix(rows_, cols);
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < (cols < cols_ ? cols : cols_); ++j) {
          temp_matrix.matrix_[i][j] = matrix_[i][j];
        }
      }
      DeleteMatrix();
      rows_ = temp_matrix.rows_;
      cols_ = cols;
      matrix_ = temp_matrix.matrix_;
      temp_matrix.matrix_ = nullptr;
    }
  }
}

template <class T>
bool matrix<T>::EqMatrix(const matrix &other) {
  if (!(SizeComparison(other))) {
    return false;
  } else if (this == &other) {
    return true;
  }
  bool result = true;
  for (int i = 0; i < rows_ && result; ++i) {
    for (int j = 0; j < cols_ && result; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
        result = false;
      }
    }
  }
  return result;
}

template <class T>
void matrix<T>::SumMatrix(const matrix &other) {
  if (!SizeComparison(other)) {
    throw std::out_of_range("different dimensionality of matrices");
  }
  if (MatrixIsExtend() && other.MatrixIsExtend()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      }
    }
  }
}

template <class T>
void matrix<T>::SubMatrix(const matrix &other) {
  if (!SizeComparison(other)) {
    throw std::out_of_range("different dimensionality of matrices");
  }
  if (MatrixIsExtend() && other.MatrixIsExtend()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
      }
    }
  }
}

template <class T>
void matrix<T>::MulNumber(const double num) {
  if (MatrixIsExtend()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  }
}

template <class T>
void matrix<T>::MulMatrix(const matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "the number of columns of the first matrix does not equal the number "
        "of rows of the second matrix");
  }
  if (MatrixIsExtend() && other.MatrixIsExtend()) {
    matrix temp_result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < other.cols_; ++j) {
        for (int k = 0; k < cols_; ++k) {
          temp_result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = temp_result;
  }
}

template <class T>
matrix<T> matrix<T>::Transpose() {
  matrix transposed_matrix(cols_, rows_);
  if (MatrixIsExtend()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        transposed_matrix.matrix_[j][i] = matrix_[i][j];
      }
    }
  }
  return transposed_matrix;
}

template <class T>
matrix<T> matrix<T>::CalcComplements() {
  matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::logic_error("the matrix is not square");
  }
  if (MatrixIsExtend()) {
    matrix temp_matrix(rows_ - 1, cols_ - 1);
    double temp_result;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        temp_matrix.ShortenedCopy(*this, i, j);
        temp_result = temp_matrix.Determinant();
        result.matrix_[i][j] += pow(-1, i + j) * temp_result;
      }
    }
  }
  return result;
}

template <class T>
double matrix<T>::Determinant() {
  double result = 0;
  double temp_result = 0.0;
  if (rows_ != cols_) {
    throw std::logic_error("the matrix is not square");
  }
  if (MatrixIsExtend()) {
    if (rows_ == 1) {
      temp_result = matrix_[0][0];
    } else if (rows_ == 2) {
      temp_result =
          (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
    } else {
      matrix temp_matrix(rows_ - 1, cols_ - 1);
      for (int i = 0; i < cols_; ++i) {
        temp_matrix.ShortenedCopy(*this, 0, i);
        result = temp_matrix.Determinant();
        temp_result += matrix_[0][i] * pow(-1, i) * result;
      }
    }
    result = temp_result;
  }
  return result;
}

template <class T>
matrix<T> matrix<T>::InverseMatrix() {
  matrix temp_matrix(rows_, cols_);
  double deter = Determinant();
  if (deter == 0) {
    throw std::invalid_argument("the Determinant of the matrix is 0");
  }
  if (MatrixIsExtend() && (rows_ == cols_)) {
    temp_matrix = CalcComplements();
    temp_matrix = temp_matrix.Transpose();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        temp_matrix.matrix_[i][j] = 1 / deter * temp_matrix.matrix_[i][j];
      }
    }
  }
  return temp_matrix;
}

template <class T>
matrix<T> matrix<T>::operator+(const matrix &other) {
  matrix new_matrix(*this);
  new_matrix.SumMatrix(other);
  return new_matrix;
}

template <class T>
matrix<T> matrix<T>::operator-(const matrix &other) {
  matrix new_matrix(*this);
  new_matrix.SubMatrix(other);
  return new_matrix;
}

template <class T>
matrix<T> matrix<T>::operator*(const double num) {
  matrix new_matrix(*this);
  new_matrix.MulNumber(num);
  return new_matrix;
}

template <class T>
matrix<T> matrix<T>::operator*(const matrix &other) {
  matrix new_matrix(*this);
  new_matrix.MulMatrix(other);
  return new_matrix;
}

template <class T>
bool matrix<T>::operator==(const matrix &other) {
  return EqMatrix(other);
}

template <class T>
matrix<T> &matrix<T>::operator=(const matrix &other) {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new T *[rows_];
    for (size_t i = 0; i < rows_; ++i) {
      matrix_[i] = new T[cols_];
    }
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

template <class T>
matrix<T> matrix<T>::operator+=(const matrix &other) {
  SumMatrix(other);
  return *this;
}

template <class T>
matrix<T> matrix<T>::operator-=(const matrix &other) {
  SubMatrix(other);
  return *this;
}

template <class T>
matrix<T> matrix<T>::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

template <class T>
matrix<T> matrix<T>::operator*=(const matrix &other) {
  MulMatrix(other);
  return *this;
}

template <class T>
T &matrix<T>::operator()(int i, int j) {
  if (!(rows_ >= (size_t)i && (size_t)i >= 0 && cols_ >= (size_t)j &&
        (size_t)j >= 0)) {
    throw std::out_of_range("different dimensionality of matrices");
  }
  return matrix_[i][j];
}

template <class T>
T *matrix<T>::operator[](size_t row) {
  if (row >= rows_) {
    throw std::out_of_range("Row index out of range");
  }
  return matrix_[row];
}

template <class T>
void matrix<T>::FillingMatrix() {
  double temp = 0;
  for (int i = 0; i < GetRows(); ++i) {
    for (int j = 0; j < GetCols(); ++j) {
      matrix_[i][j] = temp;
      temp++;
    }
  }
}

template <class T>
void matrix<T>::InitMatrix() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

template <class T>
bool matrix<T>::SizeComparison(const matrix &other) const {
  return cols_ == other.cols_ && rows_ == other.rows_;
}

template <class T>
bool matrix<T>::MatrixIsExtend() const {
  return (cols_ > 0 && rows_ > 0 && matrix_ != nullptr);
}

template <class T>
void matrix<T>::DeleteMatrix() {
  if (matrix_) {
    for (size_t i = 0; i < rows_; ++i) {
      delete matrix_[i];
    }
    delete matrix_;
  }
  rows_ = 0;
  cols_ = 0;
}

template <class T>
void matrix<T>::ZeroingMatrix() {
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

template <class T>
void matrix<T>::ShortenedCopy(const matrix &other, int row, int column) {
  for (int i = 0, x = 0; i < other.rows_; ++i) {
    if (i != row) {
      for (int j = 0, y = 0; j < other.cols_; ++j) {
        if (j != column) {
          matrix_[x][y] = other.matrix_[i][j];
          y++;
        }
      }
      x++;
    }
  }
}
}  // namespace s21
#endif  // SIMPLENAVIGATOR_SRC_INCLUDE_S21_MATRIX_H_
