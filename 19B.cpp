#include <bits/stdc++.h>

std::vector<std::string> towels;
void ReadTowels() {
  std::string line;
  std::getline(std::cin, line);
  std::stringstream towel_stream(line);
  std::string towel;
  while (towel_stream >> towel) {
    if (towel.back() == ',') {
      towel.pop_back();
    }
    towels.push_back(towel);
  }
}

std::map<std::string, int64_t> memo;
int64_t CountWays(const std::string& s) {
  if (memo.count(s)) {
    return memo[s];
  }
  if (s.empty()) {
    return memo[s] = 1;
  }
  for (const std::string& towel : towels) {
    if (towel == s.substr(0, towel.size())) {
      memo[s] += CountWays(s.substr(towel.size()));
    }
  }
  return memo[s];
}

int main() {
  ReadTowels();
  int64_t sum_n_ways = 0;
  std::string design;
  while (std::cin >> design) {
    sum_n_ways += CountWays(design);
  }
  std::cout << sum_n_ways << std::endl;
}
