#ifndef SRC_MODEL_GENERATE_H
#define SRC_MODEL_GENERATE_H

#include <iostream>
#include <random>
#include <vector>

namespace s21 {
class Generator {
 public:
  Generator(){};
  void GenerateInit(int rows, int cols);
  std::vector<std::vector<int>>& GetMatrixHorizontal();
  std::vector<std::vector<int>>& GetMatrixVertical();
  void Print();

 private:
  int rows_;
  int cols_;
  std::vector<std::vector<int>> matrix_horizontal_;
  std::vector<std::vector<int>> matrix_vertical_;
  std::vector<int> current_line_;
  int count_{1};
  void AssignSet();
  void VWalls(int row);
  void HWalls(int row);
  void CheckHWalls(int row);
  void RemoveUnsuitableCells(int row);
  int GetRandomNumber();
  void MergeSet(int index, int element);
  int CountSet(int element);
  int CountHWalls(int element, int row);
  void AddLastRow();
  void CheckLastRow();
};
}  // namespace s21

#endif  // SRC_MODEL_GENERATE_H
