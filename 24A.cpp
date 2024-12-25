#include <bits/stdc++.h>

std::map<std::string, int32_t> values;

void ParseInitialValue(const std::string& line) {
  std::string variable = line.substr(0, 3);
  int32_t value = line.back() - '0';
  values[variable] = value;
}

struct Expression {
  std::string lhs, rhs, op;
};

std::map<std::string, Expression> expressions;

void ParseExpression(const std::string& line) {
  std::string lhs, rhs, op, arrow, res;
  std::stringstream line_parser(line);
  line_parser >> lhs >> op >> rhs >> arrow >> res;
  expressions[res] = {lhs, rhs, op};
}

void Read() {
  std::string line;
  while (std::getline(std::cin, line), !line.empty()) {
    ParseInitialValue(line);
  }
  while (std::getline(std::cin, line)) {
    ParseExpression(line);
  }
}

int32_t Calc(int32_t lhs, const std::string& op, int32_t rhs) {
  if (op == "OR")
    return lhs | rhs;
  else if (op == "AND")
    return lhs & rhs;
  else if (op == "XOR")
    return lhs ^ rhs;
  else
    exit(0);
}

int32_t GetValue(const std::string& variable) {
  if (values.count(variable)) {
    return values[variable];
  }
  const Expression& expression = expressions[variable];
  int32_t lhs = GetValue(expression.lhs);
  int32_t rhs = GetValue(expression.rhs);
  return values[variable] = Calc(lhs, expression.op, rhs);
}

int main() {
  Read();
  int64_t ans = 0;
  int64_t pow2 = 1;
  for (auto [variable, _] : expressions) {
    if (variable[0] == 'z') {
      ans = ans + pow2 * GetValue(variable);
      pow2 *= 2;
    }
  }
  std::cout << ans << std::endl;
}
