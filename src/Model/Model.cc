#include "Model.h"

void s21::Model::ParserMaze(std::string path) { parser_.ParserInit(path); }

void s21::Model::SearchSolution(int startX, int startY, int endX, int endY,
                                std::vector<std::vector<int>> matrixHorizontal,
                                std::vector<std::vector<int>> matrixVertical) {
  search_.SearchInit(startX, startY, endX, endY, matrixHorizontal,
                     matrixVertical);
  search_.SearchSolution();
}

void s21::Model::GenerateMaze(int rows, int cols) {
  generate_.GenerateInit(rows, cols);
}

s21::Parser s21::Model::GetParser() { return parser_; }

s21::Generator s21::Model::GetGenerator() { return generate_; }

s21::PathFinder s21::Model::GetPathFinder() { return search_; }

void s21::Model::SaveFile(int rows, int cols,
                          std::vector<std::vector<int>> vertical,
                          std::vector<std::vector<int>> horizontal) {
  int filenum = 1;
  std::string filename = "map" + std::to_string(filenum) + ".txt";
  std::ifstream *file = new std::ifstream("../../../../Maps/" + filename);
  while (file->is_open()) {
    file->close();
    filenum++;
    filename = "map" + std::to_string(filenum) + ".txt";
    delete file;
    file = new std::ifstream("../../../../Maps/" + filename);
  }
  file->close();
  delete file;
  std::ofstream fileout("../../../../Maps/" + filename);
  if (fileout.is_open()) {
    fileout << std::to_string(rows) + ' ' + std::to_string(cols) + '\n';
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        fileout << std::to_string(vertical[i][j]);
        if (j != cols - 1) {
          fileout << ' ';
        }
      }
      fileout << '\n';
    }
    fileout << '\n';
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        fileout << std::to_string(horizontal[i][j]);
        if (j != cols - 1) {
          fileout << ' ';
        }
      }
      if (i != rows - 1) {
        fileout << '\n';
      }
    }
  } else {
    throw std::exception();
  }
  fileout.close();
}
