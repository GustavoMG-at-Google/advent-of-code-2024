#include <bits/stdc++.h>

using Schematic = std::vector<std::string>;
Schematic ReadSchematic() {
  Schematic schematic;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty()) {
    schematic.push_back(line);
  }
  return schematic;
}

int32_t Rows() { return 7; }
int32_t Cols() { return 5; }

using Heights = std::vector<int32_t>;
Heights Parse(const Schematic& schematic) {
  Heights heights(Cols(), 0);
  for (int32_t i = 1; i < Rows() - 1; i++) {
    for (int32_t j = 0; j < Cols(); j++) {
      if (schematic[i][j] == '#') {
        heights[j]++;
      }
    }
  }
  return heights;
}

bool IsLock(const Schematic& schematic) { return schematic[0][0] == '#'; }

std::vector<Heights> locks, keys;
void Read() {
  while (!std::cin.eof()) {
    Schematic schematic = ReadSchematic();
    Heights heights = Parse(schematic);
    (IsLock(schematic) ? locks : keys).push_back(heights);
  }
}

bool Fit(const Heights& lock, const Heights& key) {
  for (int32_t i = 0; i < Cols(); i++) {
    if (lock[i] + key[i] > Rows() - 2) {
      return false;
    }
  }
  return true;
}

int32_t CountMatching() {
  int32_t ans = 0;
  for (const Heights& lock : locks) {
    for (const Heights& key : keys) {
      if (Fit(lock, key)) {
        ans++;
      }
    }
  }
  return ans;
}

int main() {
  Read();
  std::cout << CountMatching() << std::endl;
}
