#ifndef MATRIX_OOP
#define MATRIX_OOP

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  // Constructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  S21Matrix();

  // Destructor
  ~S21Matrix();

  // Operators
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  bool operator==(const S21Matrix& other);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  double& operator()(int row, int col);

  // Methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  double Determinant();

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  // Get
  int get_rows() noexcept;
  int get_cols() noexcept;
  // Set
  void set_rows(const int rows);
  void set_cols(const int cols);

  friend S21Matrix operator*(const double value, const S21Matrix& matrix);

 private:
  int rows_, cols_;
  double** matrix_ = nullptr;

  // Other functions
  void Memory_allocation();
  void cleaning_matrix();
  double get_determinant();
  void copy_matrix(int row, int col, S21Matrix& other);
  void copy_matrix(const S21Matrix& other);
};

#endif  // MATRIX_OOP
