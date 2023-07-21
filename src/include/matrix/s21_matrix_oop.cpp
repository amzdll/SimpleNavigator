#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() { InitMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
  ZeroingMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[other.rows_];
    for (int i = 0; i < other.rows_; ++i) {
      matrix_[i] = new double[cols_];
    }
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } else {
    InitMatrix();
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
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

S21Matrix::~S21Matrix() { DeleteMatrix(); }

int S21Matrix::get_rows() const { return matrix_ ? rows_ : 0; }

int S21Matrix::get_cols() const { return matrix_ ? cols_ : 0; }

void S21Matrix::set_rows(int rows) {
  if (rows != rows_) {
    if (matrix_) {
      S21Matrix temp_matrix(rows, cols_);
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

void S21Matrix::set_cols(int cols) {
  if (cols != cols_) {
    if (matrix_) {
      S21Matrix temp_matrix(rows_, cols);
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

bool S21Matrix::EqMatrix(const S21Matrix &other) {
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

void S21Matrix::SumMatrix(const S21Matrix &other) {
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

void S21Matrix::SubMatrix(const S21Matrix &other) {
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

void S21Matrix::MulNumber(const double num) {
  if (MatrixIsExtend()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "the number of columns of the first matrix does not equal the number "
        "of rows of the second matrix");
  }
  if (MatrixIsExtend() && other.MatrixIsExtend()) {
    S21Matrix temp_result(rows_, other.cols_);
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

S21Matrix S21Matrix::Transpose() {
  S21Matrix transposed_matrix(cols_, rows_);
  if (MatrixIsExtend()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        transposed_matrix.matrix_[j][i] = matrix_[i][j];
      }
    }
  }
  return transposed_matrix;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::logic_error("the matrix is not square");
  }
  if (MatrixIsExtend()) {
    S21Matrix temp_matrix(rows_ - 1, cols_ - 1);
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

double S21Matrix::Determinant() {
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
      S21Matrix temp_matrix(rows_ - 1, cols_ - 1);
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

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix temp_matrix(rows_, cols_);
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

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix new_matrix(*this);
  new_matrix.SumMatrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix new_matrix(*this);
  new_matrix.SubMatrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix new_matrix(*this);
  new_matrix.MulNumber(num);
  return new_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix new_matrix(*this);
  new_matrix.MulMatrix(other);
  return new_matrix;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
    }
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (!(rows_ >= i && i >= 0 && cols_ >= j && j >= 0)) {
    throw std::out_of_range("different dimensionality of matrices");
  }
  return matrix_[i][j];
}

void S21Matrix::FillingMatrix() {
  double temp = 0;
  for (int i = 0; i < get_rows(); ++i) {
    for (int j = 0; j < get_cols(); ++j) {
      matrix_[i][j] = temp;
      temp++;
    }
  }
}

void S21Matrix::InitMatrix() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::SizeComparison(const S21Matrix &other) const {
  return cols_ == other.cols_ && rows_ == other.rows_;
}

bool S21Matrix::MatrixIsExtend() const {
  return (cols_ > 0 && rows_ > 0 && matrix_ != nullptr);
}

void S21Matrix::DeleteMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete matrix_[i];
    }
    delete matrix_;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::ZeroingMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::ShortenedCopy(const S21Matrix &other, int row, int column) {
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
