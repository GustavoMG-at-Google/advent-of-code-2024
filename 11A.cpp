#include <bits/stdc++.h>

using Stones = std::vector<int64_t>;

Stones stones;

void readStones() {
  int64_t stone;
  while (std::cin >> stone) {
    stones.push_back(stone);
  }
}

Stones new_stones;

void transform(int64_t stone) {
  if (stone == 0) {
    new_stones.push_back(1);
  } else if (std::to_string(stone).size() % 2 == 0) {
    std::string stone_str = std::to_string(stone);
    int32_t len = stone_str.size() / 2;
    new_stones.push_back(stoll(stone_str.substr(0, len)));
    new_stones.push_back(stoll(stone_str.substr(len)));
  } else {
    assert(stone <= LLONG_MAX / 2024);
    new_stones.push_back(stone * 2024);
  }
}

void blink() {
  new_stones.clear();
  for (const auto& stone : stones) {
    transform(stone);
  }
  stones = new_stones;
}

int main() {
  readStones();
  for (int32_t i = 0; i < 25; i++) {
    blink();
  }
  std::cout << stones.size() << std::endl;
}
