#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;
using Map = std::vector<std::string>;

Map map;
Coord og_guard;
Coord guard;

void readMap() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int32_t guard_in_row = line.find("^");
    if (guard_in_row != std::string::npos) {
      og_guard = {map.size(), guard_in_row};
      line[guard_in_row] = '.';
    }
    map.push_back(line);
  }
}

bool inside() {
  return 0 <= guard.first && guard.first < map.size() && 0 <= guard.second &&
         guard.second < map.front().size();
}

bool blocked() { return inside() && map[guard.first][guard.second] == '#'; }

int32_t dx[] = {-1, 0, 1, 0};
int32_t dy[] = {0, 1, 0, -1};
int32_t dir = 0;

void act() {
  Coord guard_snapshot = guard;
  guard.first += dx[dir];
  guard.second += dy[dir];
  if (blocked()) {
    guard = guard_snapshot;
    dir = (dir + 1) % 4;
  }
}

using State = std::tuple<Coord, int32_t>;

bool loops() {
  guard = og_guard;
  dir = 0;
  std::set<State> visited;
  while (inside() && !visited.count({guard, dir})) {
    visited.insert({guard, dir});
    act();
  }
  return visited.count({guard, dir});
}

class ProgressBar {
 private:
  int32_t total;
  int32_t processed = 0;
  int32_t last_percent = 0;

 public:
  ProgressBar(int32_t total) : total(total) {}
  void advance() {
    processed++;
    int32_t percent = processed * 100 / total;
    if (last_percent < percent) {
      std::cout << percent << std::endl;
      last_percent = percent;
    }
  }
};

int main() {
  readMap();
  int32_t nrows = map.size();
  int32_t ncols = map.front().size();
  int32_t ans = 0;
  ProgressBar progress(nrows * ncols);
  for (int i = 0; i < nrows; i++) {
    for (int j = 0; j < ncols; j++) {
      if (map[i][j] != '#' && std::make_pair(i, j) != og_guard) {
        map[i][j] = '#';
        if (loops()) {
          ans++;
        }
        map[i][j] = '.';
      }
      progress.advance();
    }
  }
  std::cout << ans << std::endl;
}
