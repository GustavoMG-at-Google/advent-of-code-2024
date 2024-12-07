#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;
using Map = std::vector<std::string>;

Map map;
Coord guard;

void readMap() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int32_t guard_in_row = line.find("^");
    if (guard_in_row != std::string::npos) {
      guard = {map.size(), guard_in_row};
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
  Coord og_guard = guard;
  guard.first += dx[dir];
  guard.second += dy[dir];
  if (blocked()) {
    guard = og_guard;
    dir = (dir + 1) % 4;
  }
}

int main() {
  readMap();
  std::set<Coord> visited;
  while (inside()) {
    visited.insert(guard);
    act();
  }
  std::cout << visited.size() << std::endl;
}
