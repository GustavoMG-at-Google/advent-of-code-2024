#include <bits/stdc++.h>

std::string disk_map;
std::vector<int32_t> disk;

int main() {
  std::cin >> disk_map;
  for (int32_t i = 0; i < disk_map.size(); i++) {
    int32_t id = i % 2 == 0 ? i / 2 : -1;
    for (char j = '0'; j < disk_map[i]; j++) {
      disk.push_back(id);
    }
  }
  std::cout << std::endl;
  int32_t left = 0, right = disk.size() - 1;
  while (left < right) {
    if (disk[left] >= 0) {
      left++;
    } else if (disk[right] < 0) {
      right--;
    } else {
      std::swap(disk[left], disk[right]);
    }
  }
  int64_t checksum = 0;
  for (int32_t i = 0; i < disk.size(); i++) {
    if (disk[i] >= 0) checksum += disk[i] * i;
  }
  std::cout << checksum << std::endl;
}
