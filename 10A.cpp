#include <bits/stdc++.h>

using Map = std::vector<std::string>;
Map map;
int32_t nrows, ncols;

void read_map() {
  std::string line;
  while (std::getline(std::cin, line)) {
    map.push_back(line);
  }
  nrows = map.size();
  ncols = map.front().size();
}

bool inside(int32_t row, int32_t col) {
  return 0 <= row && row < nrows && 0 <= col && col < ncols;
}

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

std::set<std::pair<int32_t, int32_t>> get_trailends(int32_t row, int32_t col) {
  if (map[row][col] == '9') {
    return {std::make_pair(row, col)};
  }
  std::set<std::pair<int32_t, int32_t>> ans;
  for (int32_t d = 0; d < 4; d++) {
    int32_t new_row = row + dx[d];
    int32_t new_col = col + dy[d];
    if (inside(new_row, new_col) &&
        map[new_row][new_col] == map[row][col] + 1) {
      for (const auto& trailend : get_trailends(new_row, new_col)) {
        ans.insert(trailend);
      }
    }
  }
  return ans;
}

int main() {
  read_map();
  int32_t ans = 0;
  for (int32_t row = 0; row < nrows; row++) {
    for (int32_t col = 0; col < ncols; col++) {
      if (map[row][col] == '0') {
        ans += get_trailends(row, col).size();
      }
    }
  }
  std::cout << ans << std::endl;
}
