#include <bits/stdc++.h>

std::string dc = "^>v<";
int32_t dx[] = {-1, 0, 1, 0};
int32_t dy[] = {0, 1, 0, -1};
int32_t get_dir(char c) { return dc.find(c); }

using Program = std::string;
Program readProgram() {
  Program program;
  std::string line;
  while (std::getline(std::cin, line)) {
    program += line;
  }
  return program;
}

struct Map {
  std::vector<std::string> map;
  std::string expand(const std::string& line) {
    std::string expanded;
    for (char c : line) {
      if (c == '.') {
        expanded += "..";
      } else if (c == '#') {
        expanded += "##";
      } else if (c == '@') {
        expanded += "@.";
      } else {
        expanded += "[]";
      }
    }
    return expanded;
  }
  void read() {
    std::string line;
    while (std::getline(std::cin, line), line.size()) {
      map.push_back(expand(line));
    }
  }
  int32_t rows() { return map.size(); }
  int32_t cols() { return map.front().size(); }
  char& get(int32_t x, int32_t y) { return map[x][y]; }
  std::set<std::tuple<int32_t, int32_t>> to_move;
  void calc_to_move(int32_t x, int32_t y, int32_t dir) {
    if (get(x, y) == '.' || get(x, y) == '#') {
      return;
    }
    to_move.emplace(x, y);
    int32_t nextx = x + dx[dir], nexty = y + dy[dir];
    if (get(x, y) == '[' && !to_move.count({x, y + 1}) && nexty == y) {
      calc_to_move(x, y + 1, dir);
    } else if (get(x, y) == ']' && !to_move.count({x, y - 1}) && nexty == y) {
      calc_to_move(x, y - 1, dir);
    }
    calc_to_move(nextx, nexty, dir);
  }
  bool to_move_collides(int32_t dir) {
    bool collision = false;
    for (const auto& [x, y] : to_move) {
      collision |= get(x + dx[dir], y + dy[dir]) == '#';
    }
    return collision;
  }
  void move(int32_t dir) {
    std::vector<std::string> map_copy(map);
    for (const auto& [x, y] : to_move) {
      get(x, y) = '.';
    }
    for (const auto& [x, y] : to_move) {
      get(x + dx[dir], y + dy[dir]) = map_copy[x][y];
    }
  }
  void try_move(int32_t& x, int32_t& y, int32_t dir) {
    to_move.clear();
    calc_to_move(x, y, dir);
    if (to_move_collides(dir)) {
      return;
    }
    move(dir);
    get(x, y) = '.';
    x += dx[dir];
    y += dy[dir];
  }
  int32_t total_gps() {
    int32_t ans = 0;
    for (int32_t i = 0; i < rows(); i++) {
      for (int32_t j = 0; j < cols(); j++) {
        if (get(i, j) == '[') {
          ans += 100 * i + j;
        }
      }
    }
    return ans;
  }
  void print() {
    for (int32_t i = 0; i < rows(); i++) {
      for (int32_t j = 0; j < cols(); j++) {
        std::cout << get(i, j);
      }
      std::cout << std::endl;
    }
  }
};

struct Robot {
  Map& map;
  int32_t x, y;
  Robot(Map& map_) : map(map_) {
    for (int32_t i = 0; i < map.rows(); i++) {
      for (int32_t j = 0; j < map.cols(); j++) {
        if (map.get(i, j) == '@') {
          x = i;
          y = j;
        }
      }
    }
  }

  void execute(const Program& program) {
    for (const char instruction : program) {
      map.try_move(x, y, get_dir(instruction));
    }
  }
};

int main() {
  Map map;
  map.read();
  Robot robot(map);
  Program program = readProgram();
  robot.execute(program);
  std::cout << map.total_gps() << std::endl;
}
