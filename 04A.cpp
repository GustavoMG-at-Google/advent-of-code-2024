#include <bits/stdc++.h>

class Board {
 private:
  std::vector<std::string> content;

 public:
  void read() {
    std::string line;
    while (std::getline(std::cin, line)) {
      content.push_back(line);
    }
  }
  int32_t nrows() const { return content.size(); }
  int32_t ncols() const { return content.front().size(); }
  bool is_inside(int32_t x, int32_t y) const {
    return 0 <= x && x < nrows() && 0 <= y && y < ncols();
  }
  char at(int32_t x, int32_t y) const { return content[x][y]; }
};

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

bool string_in_board(const std::string& needle, const Board& board, int x,
                     int y, int d) {
  bool ans = true;
  for (int i = 0; i < needle.size(); i++) {
    ans &= board.is_inside(x, y) && board.at(x, y) == needle[i];
    x += dx[d];
    y += dy[d];
  }
  return ans;
}

int main() {
  Board board;
  board.read();
  int32_t ans = 0;
  for (int d = 0; d < 8; d++) {
    for (int x = 0; x < board.nrows(); x++) {
      for (int y = 0; y < board.ncols(); y++) {
        if (string_in_board("XMAS", board, x, y, d)) {
          ans++;
        }
      }
    }
  }
  std::cout << ans << std::endl;
}
