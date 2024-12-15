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
  void read() {
    std::string line;
    while (std::getline(std::cin, line), line.size()) {
      map.push_back(line);
    }
  }
  int32_t rows() { return map.size(); }
  int32_t cols() { return map.front().size(); }
  char& get(int32_t x, int32_t y) { return map[x][y]; }
  int32_t total_gps() {
    int32_t ans = 0;
    for (int32_t i = 0; i < rows(); i++) {
      for (int32_t j = 0; j < cols(); j++) {
        if (get(i, j) == 'O') {
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
  char& get_in_dir(int32_t dir, int32_t len) {
    return map.get(x + dx[dir] * len, y + dy[dir] * len);
  }
  int32_t get_boxes_in_dir(int32_t dir) {
    int32_t ans = 0;
    while (get_in_dir(dir, ans + 1) == 'O') {
      ans++;
    }
    return ans;
  }

  void try_move(int32_t dir) {
    int32_t boxes_in_dir = get_boxes_in_dir(dir);
    if (get_in_dir(dir, boxes_in_dir + 1) == '#') {
      return;
    }
    get_in_dir(dir, 0) = '.';
    get_in_dir(dir, 1) = '@';
    if (boxes_in_dir > 0) {
      get_in_dir(dir, boxes_in_dir + 1) = 'O';
    }
    x += dx[dir];
    y += dy[dir];
  }

  void execute(const Program& program) {
    for (const char instruction : program) {
      try_move(get_dir(instruction));
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
