#include <bits/stdc++.h>

using Report = std::vector<int32_t>;

Report parse_report(const std::string& line) {
  std::stringstream ss(line);
  Report report;
  int32_t level;
  while (ss >> level) {
    report.push_back(level);
  }
  return report;
}

std::optional<Report> read_report() {
  std::string line;
  if (std::getline(std::cin, line)) {
    return parse_report(line);
  }
  return std::nullopt;
}

bool is_report_safe(Report report) {
  if (report.size() <= 1) return true;
  if (report.front() > report.back()) {
    std::reverse(report.begin(), report.end());
  }
  for (int32_t i = 1; i < report.size(); i++) {
    int32_t delta = report[i] - report[i - 1];
    if (delta < 1 || 3 < delta) return false;
  }
  return true;
}

int main() {
  int32_t n_safe = 0;
  while (std::optional<Report> report = read_report()) {
    if (is_report_safe(*report)) {
      n_safe++;
    }
  }
  std::cout << n_safe << std::endl;
}
