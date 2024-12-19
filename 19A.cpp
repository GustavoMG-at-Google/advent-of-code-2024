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

std::map<std::string, bool> memo;
bool IsPossible(const std::string& s) {
  if (memo.count(s)) {
    return memo[s];
  }
  if (s.empty()) {
    return memo[s] = true;
  }

  for (const std::string& towel : towels) {
    if (towel == s.substr(0, towel.size())) {
      if (IsPossible(s.substr(towel.size()))) {
        return memo[s] = true;
      }
    }
  }
  return memo[s] = false;
}

int main() {
  ReadTowels();
  int32_t n_possible = 0;
  std::string design;
  while (std::cin >> design) {
    if (IsPossible(design)) {
      n_possible++;
    }
  }
  std::cout << n_possible << std::endl;
}
