#include <bits/stdc++.h>

using Stones = std::vector<int64_t>;

Stones stones;

void readStones() {
  int64_t stone;
  while (std::cin >> stone) {
    stones.push_back(stone);
  }
}

std::map<std::pair<int64_t, int32_t>, int64_t> memo;
int64_t n_stones_after_blinking(int64_t stone, int32_t ntimes) {
  auto state = std::make_pair(stone, ntimes);
  if (memo.count(state)) {
    return memo[state];
  }
  int64_t& ans = memo[state];
  if (ntimes == 0) {
    ans = 1;
  } else if (stone == 0) {
    ans = n_stones_after_blinking(1, ntimes - 1);
  } else if (std::to_string(stone).size() % 2 == 0) {
    std::string stone_str = std::to_string(stone);
    int32_t len = stone_str.size() / 2;
    int64_t l = stoll(stone_str.substr(0, len));
    int64_t r = stoll(stone_str.substr(len));
    ans = n_stones_after_blinking(l, ntimes - 1) +
          n_stones_after_blinking(r, ntimes - 1);
  } else {
    assert(stone <= LLONG_MAX / 2024);
    ans = n_stones_after_blinking(stone * 2024, ntimes - 1);
  }
  return ans;
}

int main() {
  readStones();
  int64_t ans = 0;
  for (auto stone : stones) {
    ans += n_stones_after_blinking(stone, 75);
  }
  std::cout << ans << std::endl;
}
