#include <bits/stdc++.h>

using Connection = std::pair<std::string, std::string>;

std::pair<std::string, std::string> ExtractComputers(
    const std::string& conn_str) {
  std::string a = conn_str.substr(0, 2);
  std::string b = conn_str.substr(3, 2);
  return {a, b};
}

std::set<Connection> connections;
std::set<std::string> computers;

void Read() {
  std::string conn_str;
  while (std::cin >> conn_str) {
    auto [a, b] = ExtractComputers(conn_str);
    computers.insert(a);
    computers.insert(b);
    connections.insert({a, b});
    connections.insert({b, a});
  }
}

bool IsTriangle(const std::string& a, const std::string& b,
                const std::string& c) {
  return connections.count({a, b}) && connections.count({b, c}) &&
         connections.count({a, c});
}

bool IsCannonical(const std::string& a, const std::string& b,
                  const std::string& c) {
  return a < b && b < c;
}

bool StartsWithT(const std::string& a) { return a[0] == 't'; }

bool AnyStartsWithT(const std::vector<std::string>& a) {
  return std::count_if(a.begin(), a.end(), StartsWithT);
}

int32_t CountTriangles() {
  int32_t n_triangles = 0;
  for (const std::string& a : computers) {
    for (const std::string& b : computers) {
      for (const std::string& c : computers) {
        if (IsCannonical(a, b, c) && IsTriangle(a, b, c) &&
            AnyStartsWithT({a, b, c})) {
          n_triangles++;
        }
      }
    }
  }
  return n_triangles;
}

int main() {
  Read();
  std::cout << CountTriangles() << std::endl;
}
