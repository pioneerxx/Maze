#include "View/mazeview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Model model;
    s21::Controller controller(&model);
    s21::MazeView view(&controller);
    view.show();
    return a.exec();
}
