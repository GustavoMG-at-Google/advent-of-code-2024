#include <bits/stdc++.h>

const int32_t wide = 101;
const int32_t tall = 103;

struct Robot {
  int32_t x0, y0, vx, vy;
};

Robot parseRobot(const std::string& line) {
  std::stringstream pos_reader(line.substr(2));
  std::stringstream vel_reader(line.substr(line.find("v=") + 2));
  Robot robot;
  char comma;
  pos_reader >> robot.x0 >> comma >> robot.y0;
  vel_reader >> robot.vx >> comma >> robot.vy;
  return robot;
}

int32_t move_inf(int32_t x0, int32_t vx, int32_t t) { return x0 + vx * t; }

int32_t move_cycle(int32_t x0, int32_t vx, int32_t t, int32_t len) {
  int32_t x_in_inf = move_inf(x0, vx, t);
  int32_t x_in_cycle = x_in_inf % len;
  if (x_in_cycle < 0) x_in_cycle += len;
  return x_in_cycle;
}

using Coord = std::pair<int32_t, int32_t>;
Coord move(const Robot& robot, int32_t t) {
  return {move_cycle(robot.x0, robot.vx, t, wide),
          move_cycle(robot.y0, robot.vy, t, tall)};
}

int main() {
  std::string line;
  std::vector<Robot> robots;
  while (std::getline(std::cin, line)) {
    robots.push_back(parseRobot(line));
  }

  for (int32_t t = 0; t < 1000; t++) {
    std::vector<std::string> image(tall, std::string(wide, '.'));
    std::cout << t << std::endl;
    for (const Robot& robot : robots) {
      Coord pos = move(robot, t);
      image[pos.second][pos.first] = '#';
    }
    for (const std::string& line : image) {
      std::cout << line << std::endl;
    }
    std::cout << std::endl;
  }

  // Pattern x-axis 11 + 101K
  // Pattern y-axis 65 + 103K
  // Coincide at 7687 + 10403K
}
