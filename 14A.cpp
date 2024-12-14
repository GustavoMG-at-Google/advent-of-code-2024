#include <bits/stdc++.h>

const int32_t wide = 101;
const int32_t tall = 103;
const int32_t t = 100;

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

int32_t move_inf(int32_t x0, int32_t vx) { return x0 + vx * t; }

int32_t move_cycle(int32_t x0, int32_t vx, int32_t len) {
  int32_t x_in_inf = move_inf(x0, vx);
  int32_t x_in_cycle = x_in_inf % len;
  if (x_in_cycle < 0) x_in_cycle += len;
  return x_in_cycle;
}

using Coord = std::pair<int32_t, int32_t>;
Coord move(const Robot& robot) {
  return {move_cycle(robot.x0, robot.vx, wide),
          move_cycle(robot.y0, robot.vy, tall)};
}

int32_t sign(int32_t x) { return x > 0 ? 1 : x == 0 ? 0 : -1; }

using Quad = std::pair<int32_t, int32_t>;
Quad get_quad(const Coord& coord) {
  return {sign(coord.first - wide / 2), sign(coord.second - tall / 2)};
}

int main() {
  std::string line;
  std::map<Quad, int64_t> quad_count;
  while (std::getline(std::cin, line)) {
    Robot robot = parseRobot(line);
    Coord final_coord = move(robot);
    quad_count[get_quad(final_coord)]++;
  }
  int64_t ans = quad_count[Quad(-1, -1)] * quad_count[Quad(-1, 1)] *
                quad_count[Quad(1, -1)] * quad_count[Quad(1, 1)];
  std::cout << ans << std::endl;
}
