#include <bits/stdc++.h>

using KeyMap = std::vector<std::string>;

KeyMap num_pad{"789", "456", "123", " 0A"};
KeyMap direction_pad{" ^A", "<v>"};

int64_t Rows(const KeyMap& map) { return map.size(); }
int64_t Cols(const KeyMap& map) { return map.front().size(); }
int64_t Inside(const KeyMap& map, int64_t row, int64_t col) {
  return 0 <= row && row < Rows(map) && 0 <= col && col < Cols(map) &&
         map[row][col] != ' ';
}

using Graph = std::map<int64_t, std::vector<std::pair<int64_t, int64_t>>>;
std::map<int64_t, int64_t> Dijkstra(Graph& g, int64_t start) {
  std::set<std::pair<int64_t, int64_t>> to_visit;
  std::map<int64_t, int64_t> dist;
  dist[start] = 0;
  to_visit.emplace(0, start);
  while (!to_visit.empty()) {
    int64_t node = to_visit.begin()->second;
    to_visit.erase(to_visit.begin());
    for (const auto& [node_neighbor, neighbor] : g[node]) {
      int64_t new_dist_neighbor = dist[node] + node_neighbor;
      if (!dist.count(neighbor) || new_dist_neighbor < dist[neighbor]) {
        to_visit.erase({dist[neighbor], neighbor});
        dist[neighbor] = new_dist_neighbor;
        to_visit.emplace(new_dist_neighbor, neighbor);
      }
    }
  }
  return dist;
}

std::vector<std::tuple<char, int64_t, int64_t>> delta{
    {'^', -1, 0}, {'>', 0, 1}, {'v', 1, 0}, {'<', 0, -1}, {'A', 0, 0}};

int64_t Node(char key1, char key2) { return key1 * 128 + key2; }

using Matrix = std::map<char, std::map<char, int64_t>>;
Graph BuildGraph(Matrix& distance, const KeyMap& map) {
  Graph g;
  for (int64_t row = 0; row < Rows(map); row++) {
    for (int64_t col = 0; col < Cols(map); col++) {
      for (auto [last_dir, _, __] : delta) {
        for (auto [dir, dx, dy] : delta) {
          if (Inside(map, row, col) && Inside(map, row + dx, col + dy)) {
            g[Node(last_dir, map[row][col])].emplace_back(
                distance[last_dir][dir], Node(dir, map[row + dx][col + dy]));
          }
        }
      }
    }
  }
  return g;
}

Matrix Distance(Matrix direction_distance, const KeyMap& key_map) {
  Graph graph = BuildGraph(direction_distance, key_map);
  Matrix ans;
  for (int64_t row = 0; row < Rows(key_map); row++) {
    for (int64_t col = 0; col < Cols(key_map); col++) {
      if (!Inside(key_map, row, col)) continue;
      std::map<int64_t, int64_t> dists =
          Dijkstra(graph, Node('A', key_map[row][col]));

      for (int64_t row2 = 0; row2 < Rows(key_map); row2++) {
        for (int64_t col2 = 0; col2 < Cols(key_map); col2++) {
          if (!Inside(key_map, row2, col2)) continue;
          ans[key_map[row][col]][key_map[row2][col2]] =
              dists[Node('A', key_map[row2][col2])];
        }
      }
      ans[key_map[row][col]][key_map[row][col]] = 1;
    }
  }
  return ans;
}

Matrix OgMatrix() {
  Matrix matrix;
  for (auto [dir1, _, __] : delta) {
    for (auto [dir2, _, __] : delta) {
      matrix[dir1][dir2] = 1;
    }
  }
  return matrix;
}

void Print(const Matrix& matrix) {
  for (const auto& [from, tos] : matrix) {
    std::cout << "\t" << from;
  }
  std::cout << std::endl;
  for (const auto& [from, tos] : matrix) {
    std::cout << from;
    for (const auto& [to, dist] : tos) {
      std::cout << "\t" << dist;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  std::string code;
  Matrix dist = OgMatrix();
  for (int64_t i = 0; i < 25; i++) {
    dist = Distance(dist, direction_pad);
  }
  dist = Distance(dist, num_pad);
  int64_t ans = 0;
  while (std::cin >> code) {
    int64_t total_d = 0;
    char last_char = 'A';
    for (char c : code) {
      total_d += dist[last_char][c];
      last_char = c;
    }
    int64_t num = std::stoi(code.substr(0, 3));
    ans += total_d * num;
  }
  std::cout << ans << std::endl;
}
