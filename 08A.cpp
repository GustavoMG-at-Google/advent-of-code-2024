#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;

std::vector<std::string> map;
std::string line;
int32_t n_rows, n_cols;

bool isAntenna(int row, int col) { return map[row][col] != '.'; }

bool isInside(Coord coord) {
  return 0 <= coord.first && coord.first < n_rows && 0 <= coord.second &&
         coord.second < n_cols;
}

Coord reflect(Coord coord1, Coord coord2) {
  return std::make_pair(2 * coord1.first - coord2.first,
                        2 * coord1.second - coord2.second);
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
        antennas_by_freq[map[i][j]].emplace_back(i, j);
      }
    }
  }

  std::set<Coord> antinodes;
  for (const auto& [freq, antennas] : antennas_by_freq) {
    for (const auto& antenna_1 : antennas) {
      for (const auto& antenna_2 : antennas) {
        if (antenna_1 != antenna_2) {
          auto antinode = reflect(antenna_1, antenna_2);
          if (isInside(antinode)) {
            antinodes.insert(antinode);
          }
        }
      }
    }
  }

  std::cout << antinodes.size() << std::endl;
}
