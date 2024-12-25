#include <bits/stdc++.h>

std::vector<std::string> expressions;
void ParseExpression(const std::string& line) { expressions.push_back(line); }

void Read() {
  std::string line;
  while (std::getline(std::cin, line), !line.empty()) {
  }
  while (std::getline(std::cin, line)) {
    ParseExpression(line);
  }
}

std::string ToString(int32_t n) {
  return std::to_string(n / 10) + std::to_string(n % 10);
}

bool StartsWith(const std::string& heystack, const std::string& needle) {
  return heystack.substr(0, needle.size()) == needle;
}

std::string FindExpression(const std::string& var1, const std::string& var2,
                           const std::string& op) {
  std::string prefix1 = var1 + " " + op + " " + var2;
  std::string prefix2 = var2 + " " + op + " " + var1;
  for (const std::string& expression : expressions) {
    if (StartsWith(expression, prefix1) || StartsWith(expression, prefix2)) {
      return expression;
    }
  }
  exit(-1);
}

std::string ExtractRes(const std::string& expression) {
  return expression.substr(expression.size() - 3);
}

void Substitute(const std::string& old_str, const std::string& new_str) {
  for (std::string& expression : expressions) {
    auto pos = expression.find(old_str);
    if (pos != std::string::npos) {
      expression.replace(pos, new_str.size(), new_str);
    }
  }
}

void SetExpression(const std::string& lhs, const std::string& op,
                   const std::string& rhs, const std::string& out) {
  std::string expression = FindExpression(lhs, rhs, op);
  std::string old_out = ExtractRes(*expression);
  Substitute(old_out, out);
  std::cout << lhs << " " << op << " " << rhs << " -> " << out << " ("
            << old_out << ")" << std::endl;
}

std::string X(int32_t id) { return "x" + ToString(id); }
std::string Y(int32_t id) { return "y" + ToString(id); }
std::string P(int32_t id) { return "p" + ToString(id); }
std::string Q(int32_t id) { return "q" + ToString(id); }
std::string R(int32_t id) { return "r" + ToString(id); }
std::string Z(int32_t id) { return "z" + ToString(id); }
std::string C(int32_t id) { return "c" + ToString(id); }

void Fix(int32_t id) {
  SetExpression(X(id), "XOR", Y(id), P(id));
  SetExpression(X(id), "AND", Y(id), Q(id));
  SetExpression(C(id - 1), "AND", P(id), R(id));
  SetExpression(C(id - 1), "XOR", P(id), Z(id));
  SetExpression(Q(id), "OR", R(id), C(id));
}

void Fix0() {
  SetExpression(X(0), "XOR", Y(0), Z(0));
  SetExpression(X(0), "AND", Y(0), C(0));
}

void Fix44() {
  SetExpression(X(44), "XOR", Y(44), P(44));
  SetExpression(X(44), "AND", Y(44), Q(44));
  SetExpression(C(43), "AND", P(44), R(44));
  SetExpression(C(43), "XOR", P(44), Z(44));
  SetExpression(Q(44), "OR", R(44), Z(45));
}

int main() {
  Read();
  Fix0();
  for (int32_t i = 1; i <= 43; i++) Fix(i);
  Fix44();
}
