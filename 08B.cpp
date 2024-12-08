#include <bits/stdc++.h>

struct Coord {
  int32_t x, y;
};
Coord operator+(const Coord& lhs, const Coord& rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}
Coord operator-(const Coord& lhs, const Coord& rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}
Coord operator/(const Coord& lhs, int32_t k) { return {lhs.x / k, lhs.y / k}; }
bool operator<(const Coord& lhs, const Coord& rhs) {
  return lhs.x < rhs.x || lhs.x == rhs.x && lhs.y < rhs.y;
}
bool operator!=(const Coord& lhs, const Coord& rhs) {
  return lhs < rhs || rhs < lhs;
}

std::vector<std::string> map;
std::string line;
int32_t n_rows, n_cols;

bool isAntenna(int row, int col) { return map[row][col] != '.'; }

bool isInside(Coord coord) {
  return 0 <= coord.x && coord.x < n_rows && 0 <= coord.y && coord.y < n_cols;
}

int main() {
  while (std::getline(std::cin, line)) {
    map.push_back(line);
  }
  n_rows = map.size();
  n_cols = map.front().size();

  std::map<char, std::vector<Coord>> antennas_by_freq;
  for (int32_t i = 0; i < n_rows; i++) {
    for (int32_t j = 0; j < n_cols; j++) {
      if (isAntenna(i, j)) {
        antennas_by_freq[map[i][j]].push_back({i, j});
      }
    }
  }

  std::set<Coord> antinodes;
  for (const auto& [freq, antennas] : antennas_by_freq) {
    for (const auto& antenna_1 : antennas) {
      for (const auto& antenna_2 : antennas) {
        if (antenna_1 != antenna_2) {
          Coord delta = antenna_2 - antenna_1;
          int32_t d = std::__gcd(std::abs(delta.x), std::abs(delta.y));
          delta = delta / d;
          for (Coord antinode = antenna_1; isInside(antinode);
               antinode = antinode + delta) {
            antinodes.insert(antinode);
          }
        }
      }
    }
  }

  std::cout << antinodes.size() << std::endl;
}
