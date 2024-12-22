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

int main() {
  int64_t ans = 0;
  while (std::cin >> secret) {
    for (int64_t i = 0; i < 2000; i++) {
      next();
    }
    ans += secret;
  }
  std::cout << ans << std::endl;
}
