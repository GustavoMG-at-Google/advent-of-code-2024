#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;

Coord start, end;
int32_t rows, cols;
std::vector<std::string> maze;

void ReadMaze() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int32_t start_col = line.find("S");
    if (start_col != std::string::npos) {
      start = {maze.size(), start_col};
      line[start_col] = '.';
    }
    int32_t end_col = line.find("E");
    if (end_col != std::string::npos) {
      end = {maze.size(), end_col};
      line[end_col] = '.';
    }
    maze.push_back(line);
  }
  rows = maze.size();
  cols = maze.front().size();
}

int32_t dx[] = {-1, 0, 1, 0};
int32_t dy[] = {0, 1, 0, -1};
Coord Advance(const Coord& coord, int32_t dir) {
  return {coord.first + dx[dir], coord.second + dy[dir]};
}

bool Inside(const Coord& coord) {
  return 0 <= coord.first && coord.first < rows && 0 <= coord.second &&
         coord.second < cols;
}
bool Space(const Coord& coord) {
  return Inside(coord) && maze[coord.first][coord.second] == '.';
}

int32_t inf = 1e6;
void Bfs(std::map<Coord, int32_t>& dist, const Coord& start) {
  std::queue<Coord> to_visit;
  to_visit.push(start);
  dist[start] = 0;
  while (!to_visit.empty()) {
    Coord node = to_visit.front();
    to_visit.pop();
    for (int32_t dir = 0; dir < 4; dir++) {
      Coord neighboor = Advance(node, dir);
      if (Space(node) && Space(neighboor) && !dist.count(neighboor)) {
        to_visit.push(neighboor);
        dist[neighboor] = dist[node] + 1;
      }
    }
  }
}

std::map<Coord, int32_t> dist_end, dist_start;

int32_t Manhattan(const Coord& a, const Coord& b) {
  return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int32_t ShortcutDist(const Coord& a, const Coord& b) {
  return dist_start[a] + dist_end[b] + Manhattan(a, b);
}

int32_t ShortcutSaving(const Coord& a, const Coord& b) {
  return dist_start[end] - ShortcutDist(a, b);
}

int32_t LIM = 2;

bool Shortcut(const Coord& a, const Coord& b) {
  return Space(a) && Space(b) && Manhattan(a, b) <= LIM &&
         ShortcutSaving(a, b) > 0;
}

std::map<int32_t, int32_t> shortcuts;
void FindShortcuts() {
  for (int32_t row = 0; row < rows; row++) {
    for (int32_t col = 0; col < cols; col++) {
      for (int32_t row2 = row - LIM; row2 <= row + LIM; row2++) {
        for (int32_t col2 = col - LIM; col2 <= col + LIM; col2++) {
          Coord a{row, col};
          Coord b{row2, col2};
          if (Shortcut(a, b)) {
            shortcuts[ShortcutSaving(a, b)]++;
          }
        }
      }
    }
  }
}

int main() {
  ReadMaze();
  Bfs(dist_start, start);
  Bfs(dist_end, end);
  FindShortcuts();
  int32_t ans = 0;
  for (const auto [saving, n] : shortcuts) {
    if (saving >= 100) ans += n;
  }
  std::cout << ans << std::endl;
}
