#include <bits/stdc++.h>

std::vector<int32_t> program{2, 4, 1, 2, 7, 5, 1, 7, 4, 4, 0, 3, 5, 5, 3, 0};
std::optional<int64_t> dfs(int64_t A, int pos) {
  if (pos < 0) return A;
  for (int32_t B = 0; B < 8; B++) {
    A = A * 8 + B;
    int64_t C = (A >> (B ^ 2)) % 8;
    int64_t out = B ^ 5 ^ C;
    if (out == program[pos]) {
      std::optional<int64_t> ans = dfs(A, pos - 1);
      if (ans.has_value()) return *ans;
    }
    A /= 8;
  }
  return std::nullopt;
}

int main() {
  std::optional<int64_t> ans = dfs(0, program.size() - 1);
  if (ans.has_value()) std::cout << *ans << std::endl;
}
