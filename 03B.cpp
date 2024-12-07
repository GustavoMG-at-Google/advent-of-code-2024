#include <bits/stdc++.h>

char c;
bool enabled = true;
int64_t num1, num2;

enum State {
  kStart,
  kMRead,
  kMuRead,
  kMulRead,
  kOpenParenthesisRead,
  kDigit1Read,
  kCommaRead,
  kDigit2Read,
  kDRead,
  kDoRead,
  kDoOpenRead,
  kDonRead,
  kDonApostropheRead,
  kDontRead,
  kDontOpenRead
};

int main() {
  int64_t ans = 0;
  State state = kStart;
  while (std::cin.get(c)) {
    if (state == kStart) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else {
        state = kStart;
      }
    } else if (state == kMRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == 'u') {
        state = kMuRead;
      } else {
        state = kStart;
      }
    } else if (state == kMuRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == 'l') {
        state = kMulRead;
      } else {
        state = kStart;
      }
    } else if (state == kMulRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == '(') {
        state = kOpenParenthesisRead;
      } else {
        state = kStart;
      }
    } else if (state == kOpenParenthesisRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (std::isdigit(c)) {
        num1 = c - '0';
        state = kDigit1Read;
      } else {
        state = kStart;
      }
    } else if (state == kDigit1Read) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (std::isdigit(c)) {
        num1 = num1 * 10 + (c - '0');
        state = kDigit1Read;
      } else if (c == ',') {
        state = kCommaRead;
      } else {
        state = kStart;
      }
    } else if (state == kCommaRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (std::isdigit(c)) {
        num2 = c - '0';
        state = kDigit2Read;
      } else {
        state = kStart;
      }
    } else if (state == kDigit2Read) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (std::isdigit(c)) {
        num2 = num2 * 10 + (c - '0');
        state = kDigit2Read;
      } else if (c == ')') {
        if (enabled) ans += num1 * num2;
        state = kStart;
      } else {
        state = kStart;
      }
    } else if (state == kDRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == 'o') {
        state = kDoRead;
      } else {
        state = kStart;
      }
    } else if (state == kDoRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == 'n') {
        state = kDonRead;
      } else if (c == '(') {
        state = kDoOpenRead;
      } else {
        state = kStart;
      }
    } else if (state == kDoOpenRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == ')') {
        enabled = true;
        state = kStart;
      } else {
        state = kStart;
      }
    } else if (state == kDonRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == '\'') {
        state = kDonApostropheRead;
      } else {
        state = kStart;
      }
    } else if (state == kDonApostropheRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == 't') {
        state = kDontRead;
      } else {
        state = kStart;
      }
    } else if (state == kDontRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == '(') {
        state = kDontOpenRead;
      } else {
        state = kStart;
      }
    } else if (state == kDontOpenRead) {
      if (c == 'm') {
        state = kMRead;
      } else if (c == 'd') {
        state = kDRead;
      } else if (c == ')') {
        enabled = false;
        state = kStart;
      } else {
        state = kStart;
      }
    }
  }
  std::cout << ans << std::endl;
}
