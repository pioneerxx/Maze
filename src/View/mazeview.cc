#include "mazeview.h"

#include "ui_mazeview.h"

s21::MazeView::MazeView(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MazeView) {
  controller_ = controller;
  ui_->setupUi(this);
  timer_.setSingleShot(true);
  movie_ = new QMovie("../../../../misc/resized_idle.gif");
  ui_->minotaurGIF->setMovie(movie_);
  movie_->start();
  movie_->setSpeed(250);
  maze_ = new Maze(controller, ui_->graphicsView);
  this->setFixedSize(768, 646);
  connect(ui_->openFileButton, &QPushButton::clicked, this,
          &MazeView::OpenFile);
  connect(ui_->saveFileButton, &QPushButton::clicked, this,
          &MazeView::SaveFile);
  connect(ui_->generateButton, &QPushButton::clicked, this,
          &MazeView::GenerateMaze);
  connect(&timer_, &QTimer::timeout, [&]() {
    delete movie_;
    movie_ = new QMovie("../../../../misc/resized_idle.gif");
    movie_->setSpeed(250);
    ui_->minotaurGIF->setMovie(movie_);
    movie_->start();
    ui_->generateButton->setDisabled(false);
  });
}

s21::MazeView::~MazeView() {
  delete ui_;
  delete movie_;
  delete maze_;
}

void s21::MazeView::OpenFile() {
  QFileDialog *fileDialog = new QFileDialog(this);
  QStringList fileNames;
  QString fileName;
  if (fileDialog) {
    fileDialog->setWindowTitle(tr("Select a maze"));
    fileDialog->setDirectory("../../../../Maps");
    fileDialog->setNameFilter(tr("*.txt"));
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    if (fileDialog->exec()) {
      fileNames = fileDialog->selectedFiles();
      if (fileNames.size() > 0) {
        fileName = fileNames.at(0);
        try {
          maze_->SetTuple(controller_->OpenFile(fileName.toStdString()));
          maze_->DrawMaze();
        } catch (std::exception e) {
          maze_->DefaultMaze();
          maze_->DrawMaze();
          QMessageBox::critical(this, "Error", "Unable to open maze",
                                QMessageBox::Button::Ok);
        }
      }
    }
  }
  delete fileDialog;
}

void s21::MazeView::SaveFile() {
  try {
    controller_->SaveFile(maze_->GetRows(), maze_->GetCols(),
                          maze_->GetMatrixVertical(),
                          maze_->GetMatrixHorizontal());
    QMessageBox::information(this, "Save file", "Maze saved successfully",
                             QMessageBox::Button::Ok);
  } catch (std::exception e) {
    QMessageBox::critical(this, "Error", "Unable to save maze",
                          QMessageBox::Button::Ok);
  }
}

void s21::MazeView::GenerateMaze() {
  delete movie_;
  movie_ = new QMovie("../../../../misc/resized_jump.gif");
  movie_->setSpeed(150);
  ui_->minotaurGIF->setMovie(movie_);
  movie_->start();
  ui_->generateButton->setDisabled(true);
  controller_->GenerateMaze(ui_->rowsSpinBox->value(),
                            ui_->columnsSpinBox->value());
  maze_->GenerateMaze(ui_->rowsSpinBox->value(), ui_->columnsSpinBox->value());
  timer_.start(1500);
}
