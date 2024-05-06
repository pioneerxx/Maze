#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include <sstream>

#include "Generator.h"
#include "Parser.h"
#include "PathFinder.h"

namespace s21 {

class Model {
 public:
  Model() {}
  ~Model() {}
  void ParserMaze(std::string path);
  void GenerateMaze(int rows, int cols);
  void SearchSolution(int startX, int startY, int endX, int endY,
                      std::vector<std::vector<int>> matrixHorizontal,
                      std::vector<std::vector<int>> matrixVertical);
  void SaveFile(int rows, int cols, std::vector<std::vector<int>> vertical,
                std::vector<std::vector<int>> horizontal);

  Parser GetParser();
  Generator GetGenerator();
  PathFinder GetPathFinder();

 private:
  Parser parser_;
  PathFinder search_;
  Generator generate_;
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H
