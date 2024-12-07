#include <bits/stdc++.h>

using OrderingRule = std::tuple<int32_t, int32_t>;

OrderingRule parseOrderingRule(const std::string& line) {
  std::stringstream ss(line);
  int32_t number1, number2;
  char sep;
  ss >> number1 >> sep >> number2;
  return OrderingRule{number1, number2};
}

std::optional<OrderingRule> readOrderingRule() {
  std::string line;
  std::getline(std::cin, line);
  if (line.size() > 0) return parseOrderingRule(line);
  return std::nullopt;
}

std::set<OrderingRule> readOrderingRules() {
  std::set<OrderingRule> ordering_rules;
  std::optional<OrderingRule> ordering_rule;
  while (ordering_rule = readOrderingRule(), ordering_rule.has_value()) {
    ordering_rules.insert(*ordering_rule);
  }
  return ordering_rules;
}

using Update = std::vector<int32_t>;

Update parseUpdate(const std::string& line) {
  Update update;
  std::stringstream ss(line);
  int32_t number;
  char sep;
  do {
    ss >> number;
    update.push_back(number);
  } while (ss >> sep);
  return update;
}

std::optional<Update> readUpdate() {
  std::string line;
  if (std::getline(std::cin, line)) return parseUpdate(line);
  return std::nullopt;
}

bool followsRules(const Update& update,
                  const std::set<OrderingRule>& ordering_rules) {
  for (int32_t i = 0; i < update.size(); i++) {
    for (int32_t j = 0; j < i; j++) {
      if (ordering_rules.count({update[i], update[j]})) {
        return false;
      }
    }
  }
  return true;
}

class UpdateFixer {
 private:
  const std::set<OrderingRule>& ordering_rules;
  Update og_update, fixed_update;
  std::set<int32_t> visited;

  void topoSort(int x) {
    if (visited.count(x)) return;
    visited.insert(x);
    for (int y : og_update)
      if (ordering_rules.count({x, y})) topoSort(y);
    fixed_update.push_back(x);
  }

 public:
  UpdateFixer(const Update& update,
              const std::set<OrderingRule>& ordering_rules)
      : og_update(update), ordering_rules(ordering_rules) {}

  Update fix() {
    for (int x : og_update) topoSort(x);
    return fixed_update;
  }
};

int32_t middlePage(const Update& update) { return update[update.size() / 2]; }

int main() {
  std::set<OrderingRule> ordering_rules = readOrderingRules();
  std::optional<Update> update;
  int32_t ans = 0;
  while (update = readUpdate(), update.has_value()) {
    if (!followsRules(*update, ordering_rules)) {
      UpdateFixer fixer(*update, ordering_rules);
      Update fixed_update = fixer.fix();
      ans += middlePage(fixed_update);
    }
  }
  std::cout << ans << std::endl;
}
