#ifndef VIEW_GRAPHICSSCENE_H
#define VIEW_GRAPHICSSCENE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTimer>

#include "../Controller/Controller.h"

namespace s21 {
class Maze : public QGraphicsView {
 public:
  Maze(Controller *controller, QGraphicsView *widg);
  ~Maze();
  void DrawMaze();
  void DrawPath();
  void ClearMaze();
  void DefaultMaze();

  void SetCols(int cols);
  void SetRows(int rows);
  void SetMatrixHorizontal(std::vector<std::vector<int>> matrix);
  void SetMatrixVertical(std::vector<std::vector<int>> matrix);
  int GetCols();
  int GetRows();
  std::vector<std::vector<int>> GetMatrixHorizontal();
  std::vector<std::vector<int>> GetMatrixVertical();
  void SetTuple(std::tuple<int, int, std::vector<std::vector<int>>,
                           std::vector<std::vector<int>>>);
  void GenerateMaze(int rows, int cols);

  void mousePressEvent(QMouseEvent *event) override;

 private:
  QGraphicsScene *scene_;
  Controller *controller_;
  int rows_ = 1;
  int cols_ = 1;
  float vertical_size_of_cell_;
  float horizontal_size_of_cell_;
  std::vector<std::vector<int>> vertical_walls_;
  std::vector<std::vector<int>> horizontal_walls_;
  std::vector<std::pair<int, int>> path_coordinates_;
  std::vector<std::pair<int, int>> path_ends_;
  QVector<QGraphicsEllipseItem *> dots_;
};
}  // namespace s21
#endif
