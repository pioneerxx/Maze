#include "Controller.h"

s21::Controller::Controller(Model *model) { this->model_ = model; }

std::tuple<int, int, std::vector<std::vector<int>>,
           std::vector<std::vector<int>>>
s21::Controller::OpenFile(std::string filename) {
  model_->ParserMaze(filename);
  return std::tuple<int, int, std::vector<std::vector<int>>,
                    std::vector<std::vector<int>>>(
      model_->GetParser().GetCols(), model_->GetParser().GetRows(),
      model_->GetParser().GetMatrixVertical(),
      model_->GetParser().GetMatrixHorizontal());
}

void s21::Controller::SaveFile(int rows, int cols,
                               std::vector<std::vector<int>> vertical,
                               std::vector<std::vector<int>> horizontal) {
  model_->SaveFile(rows, cols, vertical, horizontal);
}

std::vector<std::pair<int, int>> s21::Controller::GetSolution(
    int startX, int startY, int endX, int endY,
    std::vector<std::vector<int>> horizontalWalls,
    std::vector<std::vector<int>> verticalWalls) {
  model_->SearchSolution(startX, startY, endX, endY, horizontalWalls,
                         verticalWalls);
  return model_->GetPathFinder().GetSolution();
}

void s21::Controller::GenerateMaze(int rows, int cols) {
  model_->GenerateMaze(rows, cols);
}

std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
s21::Controller::GetGeneratedWalls() {
  return std::tuple<std::vector<std::vector<int>>,
                    std::vector<std::vector<int>>>(
      model_->GetGenerator().GetMatrixHorizontal(),
      model_->GetGenerator().GetMatrixVertical());
}
