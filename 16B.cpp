#include <bits/stdc++.h>

using Coord = std::pair<int32_t, int32_t>;

struct Maze {
  std::vector<std::string> map;

  int32_t cols() const { return map.size(); }

  int32_t rows() const { return map.front().size(); }

  int32_t isWall(const Coord& coord) const {
    return map[coord.first][coord.second] == '#';
  }

  Coord find(char c) const {
    for (int32_t i = 0; i < rows(); i++) {
      for (int32_t j = 0; j < cols(); j++) {
        if (map[i][j] == c) {
          return {i, j};
        }
      }
    }
    return {0, 0};
  }

  Coord start() const { return find('S'); }

  Coord end() const { return find('E'); }
};

Maze readMaze() {
  Maze maze;
  std::string line;
  while (std::getline(std::cin, line)) {
    maze.map.push_back(line);
  }
  return maze;
}

using Edge = std::pair<int32_t, int32_t>;
using Graph = std::vector<std::vector<Edge>>;

int32_t dx[] = {-1, 0, 1, 0};
int32_t dy[] = {0, 1, 0, -1};
const int32_t advance_cost = 1;
const int32_t turn_cost = 1000;

struct GraphTranslator {
  const Maze& maze;
  GraphTranslator(const Maze& maze) : maze(maze) {}
  int32_t nodeId(const Coord& coord, int32_t dir) const {
    return (coord.first * maze.cols() + coord.second) * 4 + dir;
  }
  Graph graph() const {
    Graph g(maze.rows() * maze.cols() * 4);
    for (int32_t i = 1; i < maze.rows() - 1; i++) {
      for (int32_t j = 1; j < maze.cols() - 1; j++) {
        for (int32_t d = 0; d < 4; d++) {
          Coord coord(i, j);
          if (maze.isWall(coord)) continue;
          int32_t node_id = nodeId(coord, d);
          int32_t turn_cw_id = nodeId(coord, (d + 1) % 4);
          int32_t turn_ccw_id = nodeId(coord, (d + 3) % 4);
          g[node_id].emplace_back(turn_cost, turn_cw_id);
          g[node_id].emplace_back(turn_cost, turn_ccw_id);
          Coord next(coord.first + dx[d], coord.second + dy[d]);
          int32_t advance_id = nodeId(next, d);
          if (!maze.isWall(next)) {
            g[node_id].emplace_back(advance_cost, advance_id);
          }
        }
      }
    }
    return g;
  }
};

const int32_t inf = 1e9;
std::vector<int32_t> dijkstra(const Graph& g, int32_t start) {
  std::vector<int32_t> dist(g.size(), inf);
  std::set<Edge> to_process;
  dist[start] = 0;
  to_process.emplace(0, start);
  while (!to_process.empty()) {
    const auto [d_start_node, node] = *to_process.begin();
    to_process.erase(to_process.begin());
    for (const auto& [d_node_next, next] : g[node]) {
      int32_t d_start_next = d_start_node + d_node_next;
      if (d_start_next < dist[next]) {
        to_process.erase({dist[next], next});
        dist[next] = d_start_next;
        to_process.emplace(d_start_next, next);
      }
    }
  }
  return dist;
}

int32_t distAnyDir(const std::vector<int32_t>& dist,
                   const GraphTranslator& translator, Coord coord) {
  int32_t ans = inf;
  for (int32_t d = 0; d < 4; d++) {
    int32_t node_id = translator.nodeId(coord, d);
    if (dist[node_id] < ans) {
      ans = dist[node_id];
    }
  }
  return ans;
}

void printDist(const std::vector<int32_t>& dist,
               const GraphTranslator& translator, const Maze& maze) {
  for (int32_t i = 0; i < maze.rows(); i++) {
    for (int32_t j = 0; j < maze.cols(); j++) {
      int32_t ans = distAnyDir(dist, translator, {i, j});
      std::cout << std::setw(10) << std::setfill(' ') << ans << " ";
    }
    std::cout << std::endl;
  }
}

std::set<int32_t> in_path;
std::set<int32_t> vis;
void findInPath(int32_t node, const std::vector<int32_t>& dist,
                const Graph& g) {
  vis.insert(node);
  bool node_in_path = false;
  for (const auto& [dist_next, next] : g[node]) {
    if (dist[node] + dist_next == dist[next]) {
      if (!vis.count(next)) findInPath(next, dist, g);
      if (in_path.count(next)) {
        node_in_path = true;
      }
    }
  }
  if (node_in_path) {
    in_path.insert(node);
  }
}

int main() {
  Maze maze = readMaze();
  GraphTranslator translator(maze);
  Graph g = translator.graph();
  int32_t start_id = translator.nodeId(maze.start(), 1);
  std::vector<int32_t> dist = dijkstra(g, start_id);
  Coord end = maze.end();
  int32_t min_dist = distAnyDir(dist, translator, end);
  for (int32_t d = 0; d < 4; d++) {
    int32_t end_id = translator.nodeId(end, d);
    if (dist[end_id] == min_dist) {
      in_path.insert(end_id);
    }
    vis.insert(end_id);
  }
  findInPath(start_id, dist, g);
  std::set<int32_t> in_path_coord;
  for (auto node : in_path) {
    in_path_coord.insert(node / 4);
  }
  std::cout << in_path_coord.size() << std::endl;
}
