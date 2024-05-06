#ifndef VIEW_MAZEVIEW_H
#define VIEW_MAZEVIEW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>

#include "../Controller/Controller.h"
#include "GraphicsScene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeView;
}
QT_END_NAMESPACE

namespace s21 {
class MazeView : public QMainWindow {
  Q_OBJECT

 public:
  MazeView(Controller *controller, QWidget *parent = nullptr);
  ~MazeView();

  void OpenFile();
  void SaveFile();
  void GenerateMaze();

 private:
  Maze *maze_;
  Controller *controller_;
  Ui::MazeView *ui_;
  QMovie *movie_;
  QTimer timer_;
};
}  // namespace s21
#endif  // MAZEVIEW_H
