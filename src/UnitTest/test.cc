#include <gtest/gtest.h>

#include <iostream>

#include "../Model/Model.h"

s21::Model model;
std::string path4x4 = "../Maps/4x4.txt";
std::string path10x10 = "../Maps/10x10.txt";
std::string path51x51 = "testmaps/51x51.txt";
std::string path_1x_1 = "testmaps/-1x-1.txt";
std::string path_unreadble = "testmaps/unreadble.txt";
std::string path_empty = "testmaps/empty.txt";
std::string path_trash1 = "testmaps/trash1.txt";
std::string path_trash2 = "testmaps/trash2.txt";
std::string path_incomplete = "testmaps/incomplete.txt";
std::string path_not1not0 = "testmaps/not1not0.txt";
std::vector<std::vector<int>> matrix4x4Horizontal = {
    {0, 0, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {0, 0, 0, 1}};
std::vector<std::vector<int>> matrix4x4Vertical = {
    {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 1, 0, 1}, {1, 1, 1, 1}};
std::vector<std::vector<int>> matrix10x10Horizontal = {
    {1, 1, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 1, 1, 0, 1, 1}, {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
    {0, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {1, 0, 1, 0, 1, 0, 0, 1, 1, 1},
    {1, 0, 1, 1, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
    {1, 1, 0, 0, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 1}};
std::vector<std::vector<int>> matrix10x10Vertical = {
    {0, 0, 0, 1, 0, 1, 0, 0, 1, 0}, {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
    {1, 1, 0, 0, 0, 1, 1, 0, 0, 1}, {0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
std::vector<std::pair<int, int>> solution4x4_0033 = {
    {3, 3}, {3, 2}, {2, 2}, {2, 3}, {1, 3}, {0, 3}, {0, 2}, {0, 1}, {0, 0}};
std::vector<std::pair<int, int>> solution4x4_3300 = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 2}, {3, 2}, {3, 3}};

std::vector<std::pair<int, int>> solution10x10_0099 = {
    {9, 9}, {8, 9}, {8, 8}, {7, 8}, {6, 8}, {6, 9}, {5, 9}, {4, 9}, {3, 9},
    {3, 8}, {4, 8}, {4, 7}, {5, 7}, {5, 6}, {5, 5}, {6, 5}, {6, 6}, {6, 7},
    {7, 7}, {8, 7}, {8, 6}, {8, 5}, {7, 5}, {7, 4}, {7, 3}, {6, 3}, {5, 3},
    {5, 4}, {4, 4}, {4, 5}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}, {0, 5},
    {0, 4}, {0, 3}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {2, 2}, {2, 1}, {3, 1},
    {4, 1}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}};

std::vector<std::pair<int, int>> solution10x10_9900 = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {4, 1}, {3, 1}, {2, 1}, {2, 2},
    {2, 3}, {1, 3}, {1, 2}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 6},
    {2, 6}, {3, 6}, {4, 6}, {4, 5}, {4, 4}, {5, 4}, {5, 3}, {6, 3}, {7, 3},
    {7, 4}, {7, 5}, {8, 5}, {8, 6}, {8, 7}, {7, 7}, {6, 7}, {6, 6}, {6, 5},
    {5, 5}, {5, 6}, {5, 7}, {4, 7}, {4, 8}, {3, 8}, {3, 9}, {4, 9}, {5, 9},
    {6, 9}, {6, 8}, {7, 8}, {8, 8}, {8, 9}, {9, 9}};

bool CompareMatrix(std::vector<std::vector<int>> matrix1,
                   std::vector<std::vector<int>> matrix2) {
  if (matrix1.size() != matrix2.size() ||
      matrix1[0].size() != matrix2[0].size()) {
    return false;
  }
  for (size_t i = 0; i < matrix1.size(); ++i) {
    for (size_t j = 0; j < matrix1[0].size(); ++j) {
      if (matrix1[i][j] != matrix2[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool CompareVector(std::vector<std::pair<int, int>> vector1,
                   std::vector<std::pair<int, int>> vector2) {
  if (vector1.size() != vector2.size()) {
    return false;
  }
  for (size_t i = 0; i < vector1.size(); ++i) {
    if (vector1[i] != vector2[i]) {
      return false;
    }
  }
  return true;
}

TEST(parser, test_4x4) {
  model.ParserMaze(path4x4);
  ASSERT_TRUE(CompareMatrix(model.GetParser().GetMatrixHorizontal(),
                            matrix4x4Horizontal));
  ASSERT_TRUE(
      CompareMatrix(model.GetParser().GetMatrixVertical(), matrix4x4Vertical));
}

TEST(parser, test_10x10) {
  model.ParserMaze(path10x10);
  ASSERT_TRUE(CompareMatrix(model.GetParser().GetMatrixHorizontal(),
                            matrix10x10Horizontal));
  ASSERT_TRUE(CompareMatrix(model.GetParser().GetMatrixVertical(),
                            matrix10x10Vertical));
}

TEST(parser, test_incorrect) {
  ASSERT_ANY_THROW(model.ParserMaze(path51x51));
  ASSERT_ANY_THROW(model.ParserMaze(path_1x_1));
  ASSERT_ANY_THROW(model.ParserMaze(path_unreadble));
  ASSERT_ANY_THROW(model.ParserMaze(path_empty));
  ASSERT_ANY_THROW(model.ParserMaze(path_trash1));
  ASSERT_ANY_THROW(model.ParserMaze(path_trash2));
  ASSERT_ANY_THROW(model.ParserMaze(path_incomplete));
  ASSERT_ANY_THROW(model.ParserMaze(path_not1not0));
}

TEST(search, test_search4x4) {
  model.ParserMaze(path4x4);
  model.SearchSolution(0, 0, 3, 3, model.GetParser().GetMatrixHorizontal(),
                       model.GetParser().GetMatrixVertical());
  ASSERT_TRUE(
      CompareVector(model.GetPathFinder().GetSolution(), solution4x4_0033));
  model.SearchSolution(3, 3, 0, 0, model.GetParser().GetMatrixHorizontal(),
                       model.GetParser().GetMatrixVertical());
  ASSERT_TRUE(
      CompareVector(model.GetPathFinder().GetSolution(), solution4x4_3300));
}

TEST(search, test_search10x10) {
  model.ParserMaze(path10x10);
  model.SearchSolution(0, 0, 9, 9, model.GetParser().GetMatrixHorizontal(),
                       model.GetParser().GetMatrixVertical());
  ASSERT_TRUE(
      CompareVector(model.GetPathFinder().GetSolution(), solution10x10_0099));
  model.SearchSolution(9, 9, 0, 0, model.GetParser().GetMatrixHorizontal(),
                       model.GetParser().GetMatrixVertical());
  ASSERT_TRUE(
      CompareVector(model.GetPathFinder().GetSolution(), solution10x10_9900));
}

TEST(search, test_incorrect) {
  model.ParserMaze(path4x4);
  ASSERT_ANY_THROW(model.SearchSolution(0, 0, 3, 4,
                                        model.GetParser().GetMatrixHorizontal(),
                                        model.GetParser().GetMatrixVertical()));
  ASSERT_ANY_THROW(model.SearchSolution(0, 0, 4, 3,
                                        model.GetParser().GetMatrixHorizontal(),
                                        model.GetParser().GetMatrixVertical()));
  ASSERT_ANY_THROW(model.SearchSolution(0, -1, 3, 3,
                                        model.GetParser().GetMatrixHorizontal(),
                                        model.GetParser().GetMatrixVertical()));
  ASSERT_ANY_THROW(model.SearchSolution(-1, 0, 3, 3,
                                        model.GetParser().GetMatrixHorizontal(),
                                        model.GetParser().GetMatrixVertical()));
  ASSERT_ANY_THROW(model.SearchSolution(0, 0, 0, 0,
                                        model.GetParser().GetMatrixHorizontal(),
                                        model.GetParser().GetMatrixVertical()));
  ASSERT_ANY_THROW(model.SearchSolution(0, 1, 0, 1,
                                        model.GetParser().GetMatrixHorizontal(),
                                        model.GetParser().GetMatrixVertical()));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}