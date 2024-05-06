#ifndef SRC_MODEL_PARSER_H
#define SRC_MODEL_PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
class Parser {
 public:
  Parser() {}
  ~Parser() {}
  void ParserInit(std::string path);
  int GetRows();
  int GetCols();
  std::vector<std::vector<int>> GetMatrixHorizontal();
  std::vector<std::vector<int>> GetMatrixVertical();

 private:
  std::vector<int> ToVector(std::ifstream file, int rows, int cols);
  std::vector<std::vector<int>> ToMatrix(std::vector<int>, int rows, int cols);
  std::vector<std::vector<int>> matrix_horizontal_;
  std::vector<std::vector<int>> matrix_vertical_;
};
}  // namespace s21

#endif  // SRC_MODEL_PARSER_H
