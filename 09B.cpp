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
  for (int32_t i = disk.size() - 1; i >= 0; i--) {
    if (disk[i] >= 0) {
      int32_t start = i;
      while (start >= 0 && disk[start] == disk[i]) start--;
      if (start < 0) {
        break;
      }
      start++;
      int32_t new_start = 0;
      for (; new_start < start; new_start++) {
        int32_t enough_space = true;
        for (int32_t j = 0; j < i - start + 1; j++) {
          if (disk[new_start + j] >= 0) enough_space = false;
        }
        if (enough_space) {
          break;
        }
      }
      if (new_start < start) {
        for (int32_t j = 0; j < i - start + 1; j++) {
          std::swap(disk[start + j], disk[new_start + j]);
        }
      }
      i = start;
    }
  }
  int64_t checksum = 0;
  for (int32_t i = 0; i < disk.size(); i++) {
    if (disk[i] >= 0) checksum += disk[i] * i;
  }
  std::cout << checksum << std::endl;
}
