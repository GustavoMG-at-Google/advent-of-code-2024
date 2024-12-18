#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;

std::vector<Coord> blocks;
void ReadBlocks() {
  int32_t x, y;
  char comma;
  while (std::cin >> x >> comma >> y) {
    blocks.emplace_back(x, y);
  }
}

const int32_t SZ = 71;
bool IsInside(const Coord& coord) {
  return 0 <= coord.first && coord.first < SZ && 0 <= coord.second &&
         coord.second < SZ;
}
bool IsCorrupted(const Coord& coord) {
  return std::find(blocks.begin(), blocks.end(), coord) != blocks.end();
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

const int32_t INF = 1e4;
std::vector<int32_t> dist;
void Bfs(int32_t start) {
  dist.assign(graph.size(), INF);
  std::queue<int32_t> q;
  q.push(start);
  dist[start] = 0;
  while (!q.empty()) {
    int32_t node = q.front();
    q.pop();
    for (int32_t neighboor : graph[node]) {
      if (dist[neighboor] == INF) {
        q.push(neighboor);
        dist[neighboor] = dist[node] + 1;
      }
    }
  }
}

int main() {
  ReadBlocks();
  blocks.resize(1024);
  BuildGraph();
  int32_t start = ToNode({0, 0});
  Bfs(start);
  int32_t end = ToNode({SZ - 1, SZ - 1});
  std::cout << dist[end] << std::endl;
}
