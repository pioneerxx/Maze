#ifndef SRC_MODEL_SEARCH_H
#define SRC_MODEL_SEARCH_H

#include <iostream>
#include <vector>

namespace s21 {
class PathFinder {
 public:
  PathFinder() {}
  ~PathFinder() {}
  void SearchInit(int startX, int startY, int endX, int endY,
                  std::vector<std::vector<int>> matrixHorizontal,
                  std::vector<std::vector<int>> matrixVertical);
  std::vector<std::pair<int, int>> GetSolution();
  bool SearchSolution();

 private:
  void Backtrack();
  bool RightObserve(std::pair<int, int> current,
                    std::vector<std::pair<int, int>> *tempAvable);
  bool LeftObserve(std::pair<int, int> current,
                   std::vector<std::pair<int, int>> *tempAvable);
  bool UpObserve(std::pair<int, int> current,
                 std::vector<std::pair<int, int>> *tempAvable);
  bool DownObserve(std::pair<int, int> current,
                   std::vector<std::pair<int, int>> *tempAvable);
  bool UpBacktrack();
  bool LeftBacktrack();
  bool DownBacktrack();
  bool RightBacktrack();
  std::pair<int, int> start_;
  std::pair<int, int> end_;
  int iter_;
  std::vector<std::vector<int>> matrix_horizontal_;
  std::vector<std::vector<int>> matrix_vertical_;
  std::vector<std::pair<int, int>> solution_;
  std::vector<std::vector<int>> matrix_observer_;
};
}  // namespace s21

#endif  // SRC_MODEL_SEARCH_H
