#include "PathFinder.h"

void s21::PathFinder::SearchInit(int startX, int startY, int endX, int endY,
                                 std::vector<std::vector<int>> matrixHorizontal,
                                 std::vector<std::vector<int>> matrixVertical) {
  solution_.clear();
  matrix_horizontal_.clear();
  matrix_vertical_.clear();
  matrix_observer_.clear();
  if ((startX == endX && startY == endY) ||
      ((startX < 0 || startX > (int)(matrixVertical.size() - 1)) ||
       (startY < 0 || startY > (int)(matrixHorizontal[0].size() - 1)) ||
       (endX < 0 || endX > (int)(matrixVertical.size() - 1)) ||
       (endY < 0 || endY > (int)(matrixHorizontal[0].size() - 1)))) {
    throw std::exception();
  }
  start_ = std::make_pair(startX, startY);
  end_ = std::make_pair(endX, endY);
  matrix_horizontal_ = matrixHorizontal;
  matrix_vertical_ = matrixVertical;
  matrix_observer_ = std::vector<std::vector<int>>(
      matrixHorizontal.size(), std::vector<int>(matrixHorizontal[0].size()));
  matrix_observer_[start_.first][start_.second] = -1;
  matrix_observer_[end_.first][end_.second] = -2;
}

std::vector<std::pair<int, int>> s21::PathFinder::GetSolution() {
  return solution_;
}

bool s21::PathFinder::SearchSolution() {
  bool result = false;
  std::vector<std::pair<int, int>> avable;
  std::vector<std::pair<int, int>> tempAvable = {start_};
  iter_ = 1;
  int size = matrix_observer_[0].size() * matrix_observer_.size();
  while (true) {
    avable = std::move(tempAvable);
    for (std::pair<int, int> current : avable) {
      if (RightObserve(current, &tempAvable)) {
        result = true;
        break;
      } else if (DownObserve(current, &tempAvable)) {
        result = true;
        break;
      } else if (LeftObserve(current, &tempAvable)) {
        result = true;
        break;
      } else if (UpObserve(current, &tempAvable)) {
        result = true;
        break;
      }
    }
    if (result == true) break;
    iter_++;
    if (iter_ == size + 1) break;
  }
  Backtrack();
  return result;
}

bool s21::PathFinder::RightObserve(
    std::pair<int, int> current, std::vector<std::pair<int, int>> *tempAvable) {
  bool result = false;
  if (current.second != (int)(matrix_horizontal_[0].size() - 1)) {
    if (matrix_horizontal_[current.first][current.second] == 0 &&
        matrix_observer_[current.first][current.second + 1] == 0) {
      matrix_observer_[current.first][current.second + 1] = iter_;
      tempAvable->push_back(std::make_pair(current.first, current.second + 1));
    } else if (matrix_horizontal_[current.first][current.second] == 0 &&
               matrix_observer_[current.first][current.second + 1] == -2) {
      result = true;
    }
  }
  return result;
}

bool s21::PathFinder::DownObserve(
    std::pair<int, int> current, std::vector<std::pair<int, int>> *tempAvable) {
  bool result = false;
  if (current.first != (int)(matrix_vertical_.size() - 1)) {
    if (matrix_vertical_[current.first][current.second] == 0 &&
        matrix_observer_[current.first + 1][current.second] == 0) {
      matrix_observer_[current.first + 1][current.second] = iter_;
      tempAvable->push_back(std::make_pair(current.first + 1, current.second));
    } else if (matrix_vertical_[current.first][current.second] == 0 &&
               matrix_observer_[current.first + 1][current.second] == -2) {
      result = true;
    }
  }
  return result;
}

bool s21::PathFinder::LeftObserve(
    std::pair<int, int> current, std::vector<std::pair<int, int>> *tempAvable) {
  bool result = false;
  if (current.second != 0) {
    if (matrix_horizontal_[current.first][current.second - 1] == 0 &&
        matrix_observer_[current.first][current.second - 1] == 0) {
      matrix_observer_[current.first][current.second - 1] = iter_;
      tempAvable->push_back(std::make_pair(current.first, current.second - 1));
    } else if (matrix_horizontal_[current.first][current.second - 1] == 0 &&
               matrix_observer_[current.first][current.second - 1] == -2) {
      result = true;
    }
  }
  return result;
}

bool s21::PathFinder::UpObserve(std::pair<int, int> current,
                                std::vector<std::pair<int, int>> *tempAvable) {
  bool result = false;
  if (current.first != 0) {
    if (matrix_vertical_[current.first - 1][current.second] == 0 &&
        matrix_observer_[current.first - 1][current.second] == 0) {
      matrix_observer_[current.first - 1][current.second] = iter_;
      tempAvable->push_back(std::make_pair(current.first - 1, current.second));
    } else if (matrix_vertical_[current.first - 1][current.second] == 0 &&
               matrix_observer_[current.first - 1][current.second] == -2) {
      result = true;
    }
  }
  return result;
}

void s21::PathFinder::Backtrack() {
  solution_.push_back(end_);
  while (iter_ != 1) {
    iter_--;
    if (UpBacktrack()) continue;
    if (LeftBacktrack()) continue;
    if (DownBacktrack()) continue;
    if (RightBacktrack()) continue;
  }
  solution_.push_back(start_);
}

bool s21::PathFinder::UpBacktrack() {
  bool result = false;
  if (solution_.back().first != 0) {
    if (matrix_observer_[solution_.back().first - 1][solution_.back().second] ==
            iter_ &&
        matrix_vertical_[solution_.back().first - 1][solution_.back().second] ==
            0) {
      solution_.push_back(
          std::make_pair(solution_.back().first - 1, solution_.back().second));
      result = true;
    }
  }
  return result;
}

bool s21::PathFinder::LeftBacktrack() {
  bool result = false;
  if (solution_.back().second != 0) {
    if (matrix_observer_[solution_.back().first][solution_.back().second - 1] ==
            iter_ &&
        matrix_horizontal_[solution_.back().first]
                          [solution_.back().second - 1] == 0) {
      solution_.push_back(
          std::make_pair(solution_.back().first, solution_.back().second - 1));
      result = true;
    }
  }
  return result;
}

bool s21::PathFinder::DownBacktrack() {
  bool result = false;
  if (solution_.back().first != (int)(matrix_vertical_.size() - 1)) {
    if (matrix_observer_[solution_.back().first + 1][solution_.back().second] ==
            iter_ &&
        matrix_vertical_[solution_.back().first][solution_.back().second] ==
            0) {
      solution_.push_back(
          std::make_pair(solution_.back().first + 1, solution_.back().second));
      result = true;
    }
  }
  return result;
}

bool s21::PathFinder::RightBacktrack() {
  bool result = false;
  if (solution_.back().second != (int)(matrix_horizontal_[0].size() - 1)) {
    if (matrix_observer_[solution_.back().first][solution_.back().second + 1] ==
            iter_ &&
        matrix_horizontal_[solution_.back().first][solution_.back().second] ==
            0) {
      solution_.push_back(
          std::make_pair(solution_.back().first, solution_.back().second + 1));
      result = true;
    }
  }
  return result;
}
