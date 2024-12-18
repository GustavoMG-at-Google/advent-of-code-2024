#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;

std::vector<Coord> blocks_to_fall;
void ReadBlocks() {
  int32_t x, y;
  char comma;
  while (std::cin >> x >> comma >> y) {
    blocks_to_fall.emplace_back(x, y);
  }
}

const int32_t SZ = 71;
bool IsInside(const Coord& coord) {
  return 0 <= coord.first && coord.first < SZ && 0 <= coord.second &&
         coord.second < SZ;
}
std::set<Coord> blocks_fallen;
bool IsCorrupted(const Coord& coord) {
  return blocks_fallen.find(coord) != blocks_fallen.end();
}
bool IsTraversable(const Coord& coord, const Coord& neighboor) {
  return !IsCorrupted(coord) && IsInside(neighboor) && !IsCorrupted(neighboor);
}
int32_t dx[] = {0, 1, 0, -1};
int32_t dy[] = {-1, 0, 1, 0};
Coord Neighboor(const Coord& coord, int32_t dir) {
  return {coord.first + dx[dir], coord.second + dy[dir]};
}

int32_t ToNode(const Coord& coord) { return coord.first * SZ + coord.second; }
Coord ToCoord(int32_t node) { return {node / SZ, node % SZ}; }

using Graph = std::vector<std::vector<int32_t>>;

Graph graph;
void BuildGraph() {
  graph.resize(SZ * SZ);
  for (int32_t i = 0; i < SZ; i++) {
    for (int32_t j = 0; j < SZ; j++) {
      for (int32_t d = 0; d < 4; d++) {
        Coord coord(i, j);
        Coord neighboor = Neighboor(coord, d);
        if (IsTraversable(coord, neighboor)) {
          graph[ToNode(coord)].push_back(ToNode(neighboor));
        }
      }
    }
  }
}

int32_t start = ToNode({0, 0});
int32_t end = ToNode({SZ - 1, SZ - 1});
std::set<int32_t> visited;
void Dfs(int32_t node) {
  visited.insert(node);
  for (int32_t neighboor : graph[node]) {
    if (!visited.count(neighboor) && !IsCorrupted(ToCoord(neighboor))) {
      Dfs(neighboor);
    }
  }
}

int main() {
  ReadBlocks();
  blocks_fallen.insert(blocks_to_fall.begin(), blocks_to_fall.begin() + 1024);
  BuildGraph();
  for (int32_t i = 1024; i < blocks_to_fall.size(); i++) {
    blocks_fallen.insert(blocks_to_fall[i]);
    visited.clear();
    Dfs(start);
    if (!visited.count(end)) {
      std::cout << blocks_to_fall[i].first << "," << blocks_to_fall[i].second
                << std::endl;
      break;
    }
  }
}
