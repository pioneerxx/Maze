#include "GraphicsScene.h"

#include <iostream>

s21::Maze::Maze(Controller *controller, QGraphicsView *widg)
    : QGraphicsView(widg) {
  scene_ = new QGraphicsScene(this);
  controller_ = controller;
  vertical_walls_.push_back({0});
  horizontal_walls_.push_back({0});
  DrawMaze();
}

s21::Maze::~Maze() { delete scene_; }

void s21::Maze::DefaultMaze() {
  ClearMaze();
  rows_ = 1;
  cols_ = 1;
  horizontal_walls_.clear();
  vertical_walls_.clear();
  horizontal_walls_.push_back({0});
  vertical_walls_.push_back({0});
}

void s21::Maze::ClearMaze() {
  scene_->clear();
  dots_.clear();
  path_ends_.clear();
  path_coordinates_.clear();
}

void s21::Maze::DrawMaze() {
  ClearMaze();
  setScene(scene_);
  vertical_size_of_cell_ = 600 / rows_;
  horizontal_size_of_cell_ = 600 / cols_;
  QPen pen(Qt::white, 2);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (vertical_walls_[i][j] == 1) {
        scene_->addLine((j + 1) * horizontal_size_of_cell_,
                        i * vertical_size_of_cell_,
                        (j + 1) * horizontal_size_of_cell_,
                        (i + 1) * vertical_size_of_cell_, pen);
      }
      if (horizontal_walls_[i][j] == 1) {
        scene_->addLine(j * horizontal_size_of_cell_,
                        (i + 1) * vertical_size_of_cell_,
                        (j + 1) * horizontal_size_of_cell_,
                        (i + 1) * vertical_size_of_cell_, pen);
      }
    }
  }
  scene_->addRect(0, 0, rows_ * vertical_size_of_cell_,
                  cols_ * horizontal_size_of_cell_, pen);
}

void s21::Maze::mousePressEvent(QMouseEvent *event) {
  if (dots_.size() == 2) {
    DrawMaze();
  }
  QPen pen(Qt::green, 2);
  float dotHeight = vertical_size_of_cell_ / 2;
  float dotWidth = horizontal_size_of_cell_ / 2;
  int dotX = (int)event->pos().x() / horizontal_size_of_cell_;
  int dotY = (int)event->pos().y() / vertical_size_of_cell_;
  float verticalCentering = (vertical_size_of_cell_ - dotHeight) / 2;
  float horizontalCentering = (horizontal_size_of_cell_ - dotWidth) / 2;
  QGraphicsEllipseItem *dot =
      scene_->addEllipse(dotX * horizontal_size_of_cell_ + horizontalCentering,
                         dotY * vertical_size_of_cell_ + verticalCentering,
                         dotWidth, dotHeight, pen);
  dot->setBrush(Qt::green);
  dots_.push_back(dot);
  path_ends_.push_back({dotX, dotY});
  if (dots_.size() == 2) {
    try {
      DrawPath();
    } catch (const std::exception &e) {
      QMessageBox::critical(this, "Error", "Can't draw a path",
                            QMessageBox::Button::Ok);
    }
  }
}

void s21::Maze::DrawPath() {
  path_coordinates_ = controller_->GetSolution(
      path_ends_.at(0).second, path_ends_.at(0).first, path_ends_.at(1).second,
      path_ends_.at(1).first, vertical_walls_, horizontal_walls_);
  float dotHeight = vertical_size_of_cell_ * 0.2;
  float dotWidth = horizontal_size_of_cell_ * 0.2;
  float verticalCentering = (vertical_size_of_cell_ - dotHeight) / 2;
  float horizontalCentering = (horizontal_size_of_cell_ - dotWidth) / 2;
  QPen pen(Qt::green, 2);
  for (int i = 0; i < (int)path_coordinates_.size() - 1; i++) {
    scene_->addLine(
        path_coordinates_[i].second * horizontal_size_of_cell_ +
            horizontalCentering,
        path_coordinates_[i].first * vertical_size_of_cell_ + verticalCentering,
        path_coordinates_[i + 1].second * horizontal_size_of_cell_ +
            horizontalCentering,
        path_coordinates_[i + 1].first * vertical_size_of_cell_ +
            verticalCentering,
        pen);
  }
}

void s21::Maze::SetCols(int cols) { cols_ = cols; }
void s21::Maze::SetRows(int rows) { rows_ = rows; }
void s21::Maze::SetMatrixHorizontal(std::vector<std::vector<int>> matrix) {
  horizontal_walls_ = matrix;
}
void s21::Maze::SetMatrixVertical(std::vector<std::vector<int>> matrix) {
  vertical_walls_ = matrix;
}

void s21::Maze::SetTuple(std::tuple<int, int, std::vector<std::vector<int>>,
                                    std::vector<std::vector<int>>>
                             tuple) {
  cols_ = std::get<0>(tuple);
  rows_ = std::get<1>(tuple);
  vertical_walls_ = std::get<3>(tuple);
  horizontal_walls_ = std::get<2>(tuple);
}

int s21::Maze::GetCols() { return cols_; }

int s21::Maze::GetRows() { return rows_; }

std::vector<std::vector<int>> s21::Maze::GetMatrixHorizontal() {
  return horizontal_walls_;
}

std::vector<std::vector<int>> s21::Maze::GetMatrixVertical() {
  return vertical_walls_;
}

void s21::Maze::GenerateMaze(int rows, int cols) {
  std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
      tuple = controller_->GetGeneratedWalls();
  vertical_walls_ = std::get<0>(tuple);
  horizontal_walls_ = std::get<1>(tuple);
  rows_ = rows;
  cols_ = cols;
  DrawMaze();
}
