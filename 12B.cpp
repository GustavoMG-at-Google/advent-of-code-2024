#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;

struct Map {
  std::vector<std::string> cells;
  void read() {
    std::string row;
    while (std::getline(std::cin, row)) {
      cells.push_back(row);
    }
  }
  int32_t nrows() { return cells.size(); }
  int32_t ncols() { return cells.front().size(); }
  bool inside(const Coord& coord) {
    return 0 <= coord.first && coord.first < nrows() && 0 <= coord.second &&
           coord.second < ncols();
  }
  char at(const Coord& coord) { return cells[coord.first][coord.second]; }
};
Map map;

int32_t dx[] = {-1, 0, 1, 0};
int32_t dy[] = {0, 1, 0, -1};
Coord next_coord_in_dir(const Coord& c, int32_t dir) {
  return Coord(c.first + dx[dir], c.second + dy[dir]);
}

bool is_connected(const Coord& c, const Coord& other) {
  return map.inside(c) && map.inside(other) && map.at(c) == map.at(other);
}

std::set<Coord> visited;
int32_t area_of_cc, sides_of_cc;
void explorecc(Coord c) {
  if (visited.count(c)) return;
  visited.insert(c);
  area_of_cc++;
  for (int32_t d = 0; d < 4; d++) {
    Coord next_coord = next_coord_in_dir(c, d);
    if (is_connected(c, next_coord)) {
      explorecc(next_coord);
    } else {
      Coord parent_coord = next_coord_in_dir(c, 1 - d % 2);
      Coord next_parent_coord = next_coord_in_dir(parent_coord, d);
      bool duplicated = is_connected(c, parent_coord) &&
                        !is_connected(parent_coord, next_parent_coord);
      if (!duplicated) {
        sides_of_cc++;
      }
    }
  }
}

int main() {
  map.read();
  int64_t ans = 0;
  for (int32_t row = 0; row < map.nrows(); row++) {
    for (int32_t col = 0; col < map.ncols(); col++) {
      Coord coord(row, col);
      if (!visited.count(coord)) {
        area_of_cc = 0;
        sides_of_cc = 0;
        explorecc(coord);
        ans += area_of_cc * sides_of_cc;
      }
    }
  }
  std::cout << ans << std::endl;
}
