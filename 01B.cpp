#include <bits/stdc++.h>

int main() {
  std::vector<int32_t> list1, list2;
  int32_t number1, number2;
  while (std::cin >> number1 >> number2) {
    list1.push_back(number1);
    list2.push_back(number2);
  }
  int32_t nread = list1.size();
  std::map<int32_t, int32_t> freq_in_list2;
  for (int32_t i = 0; i < nread; i++) {
    freq_in_list2[list2[i]]++;
  }
  int64_t ans = 0;
  for (int32_t i = 0; i < nread; i++) {
    ans += list1[i] * freq_in_list2[list1[i]];
  }
  std::cout << ans << std::endl;
}
