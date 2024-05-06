#ifndef A1_MAZE_1_CONTROLLER_CONTROLLER_H
#define A1_MAZE_1_CONTROLLER_CONTROLLER_H

#include "../Model/Model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model *model);
  std::tuple<int, int, std::vector<std::vector<int>>,
             std::vector<std::vector<int>>>
  OpenFile(std::string filename);
  void SaveFile(int rows, int cols, std::vector<std::vector<int>> vertical,
                std::vector<std::vector<int>> horizontal);
  std::vector<std::pair<int, int>> GetSolution(
      int startX, int startY, int endX, int endY,
      std::vector<std::vector<int>> horizontalWalls,
      std::vector<std::vector<int>> verticalWalls);
  void GenerateMaze(int rows, int cols);
  std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
  GetGeneratedWalls();

 private:
  Model *model_;
};

}  // namespace s21

#endif
