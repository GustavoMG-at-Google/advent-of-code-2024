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

std::map<std::set<std::string>, std::string> memo;
std::string LargestClique(const std::set<std::string>& computers) {
  if (memo.count(computers)) {
    return memo[computers];
  }

  if (computers.empty()) {
    return memo[computers] = "";
  }

  std::string first = *computers.begin();
  std::set<std::string> neighbors;
  for (const std::string& computer : computers) {
    if (connections.count({first, computer})) {
      neighbors.insert(computer);
    }
  }
  std::string clique_with_first = first + "," + LargestClique(neighbors);

  std::set<std::string> not_first(++computers.begin(), computers.end());
  std::string clique_without_first = LargestClique(not_first);

  return memo[computers] =
             clique_with_first.size() > clique_without_first.size()
                 ? clique_with_first
                 : clique_without_first;
}

int main() {
  Read();
  std::cout << LargestClique(computers) << std::endl;
}
