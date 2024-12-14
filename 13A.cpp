#include <bits/stdc++.h>

struct Machine {
  int32_t dx1, dy1, dx2, dy2, x, y;
};

int32_t get_int_after_pattern(const std::string& haystack,
                              const std::string& needle) {
  int32_t pos = haystack.find(needle) + needle.size();
  std::stringstream ss(haystack.substr(pos));
  int32_t ans;
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
    machine.x = get_int_after_pattern(line, "X=");
    machine.y = get_int_after_pattern(line, "Y=");
    std::getline(std::cin, line);
    return machine;
  } else {
    return std::nullopt;
  }
}

bool is_sol(const Machine& machine, int32_t n1, int32_t n2) {
  return machine.dx1 * n1 + machine.dx2 * n2 == machine.x &&
         machine.dy1 * n1 + machine.dy2 * n2 == machine.y;
}

int32_t cost_1 = 3;
int32_t cost_2 = 1;
std::optional<int32_t> calc_min_cost(const Machine& machine) {
  std::optional<int32_t> ans;
  for (int32_t n1 = 0; n1 < 1000; n1++) {
    for (int32_t n2 = 0; n2 < 1000; n2++) {
      if (is_sol(machine, n1, n2)) {
        int32_t cost = n1 * cost_1 + n2 * cost_2;
        if (!ans.has_value() || cost < *ans) {
          ans = cost;
        }
      }
    }
  }
  return ans;
}

int main() {
  std::optional<Machine> machine;
  int64_t ans = 0;
  while (machine = read(), machine.has_value()) {
    std::optional<int32_t> min_cost = calc_min_cost(*machine);
    if (min_cost.has_value()) {
      ans += *min_cost;
    }
  }
  std::cout << ans << std::endl;
}
