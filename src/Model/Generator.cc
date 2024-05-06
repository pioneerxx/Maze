#include "Generator.h"

void s21::Generator::GenerateInit(int rows, int cols) {
  current_line_.clear();
  matrix_horizontal_.clear();
  matrix_vertical_.clear();
  if (rows > 50 || cols > 50 || rows < 1 || cols < 1) {
    std::cout << "cant init generate" << std::endl;
    throw;
  }
  rows_ = rows;
  cols_ = cols;

  matrix_horizontal_.resize(rows_);
  matrix_vertical_.resize(rows_);
  for (int i = 0; i < rows_; ++i) {
    matrix_horizontal_[i].resize(cols_);
    matrix_vertical_[i].resize(cols_);
  }
  current_line_.resize(cols_);
  for (int j = 0; j < rows_ - 1; j++) {
    AssignSet();
    VWalls(j);
    HWalls(j);
    CheckHWalls(j);
    RemoveUnsuitableCells(j);
  }
  AddLastRow();
}

void s21::Generator::Print() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << matrix_horizontal_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << matrix_vertical_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<int>>& s21::Generator::GetMatrixHorizontal() {
  return matrix_horizontal_;
}
std::vector<std::vector<int>>& s21::Generator::GetMatrixVertical() {
  return matrix_vertical_;
}

void s21::Generator::AssignSet() {
  for (int i = 0; i < cols_; i++) {
    if (current_line_[i] == 0) {
      current_line_[i] = count_;
      ++count_;
    }
  }
}

int s21::Generator::GetRandomNumber() {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  return mersenne() % 2;
}

void s21::Generator::VWalls(int row) {
  for (int i = 0; i < cols_ - 1; i++) {
    int choise = GetRandomNumber();
    if (choise == 1 || current_line_[i] == current_line_[i + 1])
      matrix_horizontal_[row][i] = 1;
    else
      MergeSet(i, current_line_[i]);
  }
  matrix_horizontal_[row][cols_ - 1] = 1;
}

void s21::Generator::MergeSet(int index, int element) {
  int tempSet = current_line_[index + 1];
  for (int j = 0; j < cols_; j++) {
    if (current_line_[j] == tempSet) current_line_[j] = element;
  }
}

void s21::Generator::HWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    bool choise = GetRandomNumber();
    if (CountSet(current_line_[i]) != 1 && choise == 1) {
      matrix_vertical_[row][i] = 1;
    }
  }
}

int s21::Generator::CountSet(int element) {
  int countUniqSet = 0;
  for (int i = 0; i < cols_; i++) {
    if (current_line_[i] == element) ++countUniqSet;
  }
  return countUniqSet;
}

void s21::Generator::CheckHWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    if (CountHWalls(current_line_[i], row) == 0) {
      matrix_vertical_[row][i] = 0;
    }
  }
}

int s21::Generator::CountHWalls(int element, int row) {
  int count = 0;
  for (int i = 0; i < cols_; i++) {
    if (current_line_[i] == element && matrix_vertical_[row][i] == 0) ++count;
  }
  return count;
}

void s21::Generator::RemoveUnsuitableCells(int row) {
  for (int i = 0; i < cols_; i++) {
    if (matrix_vertical_[row][i] == 1) current_line_[i] = 0;
  }
}

void s21::Generator::AddLastRow() {
  AssignSet();
  VWalls(rows_ - 1);
  CheckLastRow();
}

void s21::Generator::CheckLastRow() {
  for (int i = 0; i < cols_ - 1; i++) {
    if (current_line_[i] != current_line_[i + 1]) {
      matrix_horizontal_[rows_ - 1][i] = 0;
      MergeSet(i, current_line_[i]);
    }
    matrix_vertical_[rows_ - 1][i] = 1;
  }
  matrix_vertical_[rows_ - 1][cols_ - 1] = 1;
}
