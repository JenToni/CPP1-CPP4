#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = (cols_ == other.cols_ && rows_ == other.rows_);
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::out_of_range("invalid matrix");
  for (int i = 0; i < rows_ && res; i++) {
    for (int j = 0; j < cols_ && res; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) res = false;
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ || matrix_ == nullptr ||
      other.matrix_ == nullptr)
    throw std::out_of_range(
        "Number of rows and columns must be equal to or invalid matrix");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ || matrix_ == nullptr ||
      other.matrix_ == nullptr)
    throw std::out_of_range(
        "Number of rows and columns must be equal to or invalid matrix");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr) throw std::out_of_range("invalid matrix");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr || cols_ != other.rows_)
    throw std::out_of_range("cols != rows or invalid matrices");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  if (matrix_ == nullptr) throw std::out_of_range("Invalid matrix");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double result = 0.0;
  if (rows_ != cols_ || matrix_ == nullptr || cols_ < 1 || rows_ < 1)
    throw std::out_of_range(
        "the matrix is not square or invalid matrix or rows_ || cols_ < 1");
  result = get_determinant();
  return result;
}

double S21Matrix::get_determinant() {
  double determ = 0.0;
  if (rows_ == 1) determ = matrix_[0][0];
  if (rows_ == 2) {
    determ = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int i = 0; i < cols_; i++) {
      minor.copy_matrix(0, i, *this);
      if (i % 2)
        determ -= matrix_[0][i] * minor.get_determinant();
      else
        determ += matrix_[0][i] * minor.get_determinant();
    }
  }
  return determ;
}

void S21Matrix::copy_matrix(int row, int col, S21Matrix &other) {
  int r_row = 0;
  int r_col = 0;
  for (int i = 0; i < other.rows_; i++) {
    if (i == row) continue;
    r_col = 0;
    for (int j = 0; j < other.cols_; j++) {
      if (j == col) continue;
      matrix_[r_row][r_col] = other.matrix_[i][j];
      r_col++;
    }
    r_row++;
  }
}
void S21Matrix::copy_matrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_ || matrix_ == nullptr || rows_ < 1 || cols_ < 1)
    throw std::out_of_range(
        "the matrix is not square or invalid matrix or rows_ || cols_ < 1");
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result(0, 0) = 1.0;
    return result;
  }
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      minor.copy_matrix(i, j, *this);
      result.matrix_[i][j] = pow(-1.0, (i + j)) * minor.get_determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_ || matrix_ == nullptr || rows_ < 1 || cols_ < 1)
    throw std::out_of_range(
        "the matrix is not square or invalid matrix or rows_ || cols_ < 1");
  if (rows_ == 1 && cols_ == 1) {
    S21Matrix result(1, 1);
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
    return result;
  } else {
    double det = 0.0;
    det = Determinant();
    if (fabs(det) < 1e-7)
      throw std::out_of_range("determinant of the matrix is 0");
    S21Matrix result = CalcComplements().Transpose();
    result *= (1 / det);
    return result;
  }
}

// Operators

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    cleaning_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    Memory_allocation();
    copy_matrix(other);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    cleaning_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}
S21Matrix operator*(const double value, const S21Matrix &matrix) {
  S21Matrix result = matrix;
  result.MulNumber(value);
  return result;
}
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_) {
    throw std::out_of_range("Index outside the range of rows");
  }
  if (col < 0 || col >= cols_) {
    throw std::out_of_range("Index outside the range of columns");
  }
  return matrix_[row][col];
}

// Get && Set
int S21Matrix::get_rows() noexcept { return rows_; }

int S21Matrix::get_cols() noexcept { return cols_; }

void S21Matrix::set_rows(const int rows) {
  if (rows < 1) {
    throw std::invalid_argument("The number of rows is less than one.");
  }
  if (rows != rows_) {
    S21Matrix temp(*this);
    cleaning_matrix();
    cols_ = temp.cols_;
    rows_ = rows;
    Memory_allocation();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = temp.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::set_cols(const int cols) {
  if (cols < 1) {
    throw std::invalid_argument("The number of cols is less than one.");
  }
  if (cols != cols_) {
    S21Matrix temp(*this);
    cleaning_matrix();
    cols_ = cols;
    rows_ = temp.rows_;
    Memory_allocation();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = temp.matrix_[i][j];
      }
    }
  }
}

// Constructor && Destructor
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  Memory_allocation();
  copy_matrix(other);
}
S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  Memory_allocation();
}
S21Matrix::S21Matrix() : rows_(3), cols_(3) { Memory_allocation(); }
S21Matrix::~S21Matrix() { cleaning_matrix(); }

// Other functions
void S21Matrix::Memory_allocation() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("rows or cols less 1 ");
  }
  matrix_ = new double *[rows_];
  int i = 0;
  try {
    for (; i < rows_; i++) matrix_[i] = new double[cols_]{};
  } catch (...) {
    for (int j = 0; j < i; j++) delete[] matrix_[j];
    delete[] matrix_;
    throw "Memory error";
  }
}

void S21Matrix::cleaning_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  cols_ = 0;
  rows_ = 0;
}
