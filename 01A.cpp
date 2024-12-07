#include <bits/stdc++.h>

int main() {
  std::vector<int32_t> list1, list2;
  int32_t number1, number2;
  while (std::cin >> number1 >> number2) {
    list1.push_back(number1);
    list2.push_back(number2);
  }
  int32_t nread = list1.size();
  sort(list1.begin(), list1.end());
  sort(list2.begin(), list2.end());
  int32_t ans = 0;
  for (int32_t i = 0; i < nread; i++) {
    ans += std::abs(list1[i] - list2[i]);
  }
  std::cout << ans << std::endl;
}
