#include "Parser.h"

int s21::Parser::GetRows() { return matrix_horizontal_.size(); }

int s21::Parser::GetCols() { return matrix_horizontal_[0].size(); }

std::vector<std::vector<int>> s21::Parser::GetMatrixHorizontal() {
  return matrix_horizontal_;
}

std::vector<std::vector<int>> s21::Parser::GetMatrixVertical() {
  return matrix_vertical_;
}

void s21::Parser::ParserInit(std::string path) {
  std::ifstream file(path);
  if (file.is_open()) {
    int rows, cols;
    std::vector<int> vectorHorizontal, vectorVertical;
    file >> rows >> cols;
    if (rows > 50 || cols > 50 || rows < 1 || cols < 1) {
      throw std::exception();
    }
    vectorHorizontal = ToVector(std::move(file), rows, cols);
    file.close();
    std::ifstream file2(path);
    for (int i = 0; i < rows * cols + 2; ++i) {
      int temp;
      file2 >> temp;
    }
    vectorVertical = ToVector(std::move(file2), rows, cols);
    matrix_horizontal_ = ToMatrix(vectorHorizontal, rows, cols);
    matrix_vertical_ = ToMatrix(vectorVertical, rows, cols);
    file2.close();

  } else {
    throw std::exception();
  }
}

std::vector<int> s21::Parser::ToVector(std::ifstream file, int rows, int cols) {
  int size = rows * cols;
  int number;
  int i = 0;
  std::vector<int> vector;
  while (i < size) {
    if (file >> number && (number != 1 || number != 0)) {
      vector.push_back(number);
      i++;
    } else {
      throw std::exception();
    }
  }
  return vector;
}

std::vector<std::vector<int>> s21::Parser::ToMatrix(std::vector<int> vector,
                                                    int rows, int cols) {
  std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = vector[i * cols + j];
    }
  }
  return matrix;
}
