#include <bits/stdc++.h>

struct Machine {
  int64_t dx1, dy1, dx2, dy2, x, y;
};

int64_t get_int_after_pattern(const std::string& haystack,
                              const std::string& needle) {
  int64_t pos = haystack.find(needle) + needle.size();
  std::stringstream ss(haystack.substr(pos));
  int64_t ans;
  ss >> ans;
  return ans;
}

std::optional<Machine> read() {
  std::string line;
  if (std::getline(std::cin, line)) {
    Machine machine;
    machine.dx1 = get_int_after_pattern(line, "X+");
    machine.dy1 = get_int_after_pattern(line, "Y+");
    std::getline(std::cin, line);
    machine.dx2 = get_int_after_pattern(line, "X+");
    machine.dy2 = get_int_after_pattern(line, "Y+");
    std::getline(std::cin, line);
    machine.x = 1e13 + get_int_after_pattern(line, "X=");
    machine.y = 1e13 + get_int_after_pattern(line, "Y=");
    std::getline(std::cin, line);
    return machine;
  } else {
    return std::nullopt;
  }
}

bool is_sol(const Machine& machine, int64_t n1, int64_t n2) {
  return machine.dx1 * n1 + machine.dx2 * n2 == machine.x &&
         machine.dy1 * n1 + machine.dy2 * n2 == machine.y;
}

int64_t det(int64_t a11, int64_t a12, int64_t a21, int64_t a22) {
  return a11 * a22 - a12 * a21;
}

int64_t cost_1 = 3;
int64_t cost_2 = 1;
std::optional<int64_t> calc_min_cost(const Machine& machine) {
  int64_t d = det(machine.dx1, machine.dx2, machine.dy1, machine.dy2);
  int64_t dx = det(machine.x, machine.dx2, machine.y, machine.dy2);
  int64_t dy = det(machine.dx1, machine.x, machine.dy1, machine.y);
  if (d == 0) {
    if (dx == 0 && dy == 0) {
      exit(-1);
    } else {
      return std::nullopt;
    }
  }
  int64_t n1 = dx / d;
  int64_t n2 = dy / d;
  if (n1 >= 0 && n2 >= 0 && is_sol(machine, n1, n2)) {
    return n1 * cost_1 + n2 * cost_2;
  } else {
    return std::nullopt;
  }
}

int main() {
  std::optional<Machine> machine;
  int64_t ans = 0;
  while (machine = read(), machine.has_value()) {
    std::optional<int64_t> min_cost = calc_min_cost(*machine);
    if (min_cost.has_value()) {
      ans += *min_cost;
    }
  }
  std::cout << ans << std::endl;
}
