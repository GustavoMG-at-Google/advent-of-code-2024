#include <bits/stdc++.h>

using Terms = std::vector<int64_t>;

Terms parseTerms(const std::string& line) {
  std::stringstream parser(line);
  int64_t term;
  char colon;
  Terms terms;
  parser >> term >> colon;
  terms.push_back(term);
  while (parser >> term) {
    terms.push_back(term);
  }
  return terms;
}

bool canAssignOperations(const Terms& terms, int64_t partial_result,
                         int32_t to_process) {
  if (partial_result > terms[0]) {
    return false;
  }
  if (to_process == terms.size()) {
    return terms[0] == partial_result;
  }
  return canAssignOperations(terms, partial_result + terms[to_process],
                             to_process + 1) ||
         canAssignOperations(terms, partial_result * terms[to_process],
                             to_process + 1);
}

int main() {
  std::string line;
  int64_t ans = 0;
  while (std::getline(std::cin, line)) {
    Terms terms = parseTerms(line);
    if (canAssignOperations(terms, terms[1], 2)) {
      ans += terms[0];
    }
  }
  std::cout << ans << std::endl;
}
