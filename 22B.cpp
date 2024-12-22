#include <bits/stdc++.h>

int64_t secret;
void mix(int64_t n) { secret ^= n; }
void prune() { secret &= (1 << 24) - 1; }
void next() {
  mix(secret << 6);
  prune();
  mix(secret >> 5);
  prune();
  mix(secret << 11);
  prune();
}

using Bananas = std::map<std::vector<int64_t>, int64_t>;
Bananas bananas_from_all_monkeys;
void PrecalcBananas() {
  std::vector<int64_t> pattern;
  std::set<std::vector<int64_t>> patterns;
  int64_t prev_units = secret % 10;
  for (int64_t i = 0; i < 2000; i++) {
    next();
    int64_t units = secret % 10;
    int64_t delta = units - prev_units;
    pattern.push_back(delta);
    if (pattern.size() > 4) pattern.erase(pattern.begin());
    if (pattern.size() == 4 && !patterns.count(pattern)) {
      patterns.insert(pattern);
      bananas_from_all_monkeys[pattern] += units;
    }
    prev_units = units;
  }
}

int main() {
  while (std::cin >> secret) {
    PrecalcBananas();
  }
  int64_t max_bananas = 0;
  for (int64_t a = -9; a <= 9; a++) {
    for (int64_t b = -9; b <= 9; b++) {
      for (int64_t c = -9; c <= 9; c++) {
        for (int64_t d = -9; d <= 9; d++) {
          std::vector<int64_t> pattern{a, b, c, d};
          int64_t bananas = bananas_from_all_monkeys[pattern];
          max_bananas = std::max(max_bananas, bananas);
        }
      }
    }
  }
  std::cout << max_bananas << std::endl;
}
