#include <bits/stdc++.h>

int32_t A;
int32_t B;
int32_t C;

int32_t PC;

std::vector<int32_t> program;

void LoadRegister(int32_t& reg) {
  static const std::string prefix = "Register ?: ";
  std::string line;
  std::getline(std::cin, line);
  reg = std::stoi(line.substr(prefix.size()));
}

void LoadRegisters() {
  LoadRegister(A);
  LoadRegister(B);
  LoadRegister(C);
}

void LoadProgram() {
  static const std::string prefix = "Program: ";
  std::string line;
  std::getline(std::cin, line);
  std::getline(std::cin, line);
  for (char c : line.substr(prefix.size())) {
    if (c != ',') {
      program.push_back(c - '0');
    }
  }
}

int32_t Literal(int32_t arg) { return arg; }
int32_t Combo(int32_t arg) {
  if (arg < 4) return arg;
  if (arg == 4) return A;
  if (arg == 5) return B;
  if (arg == 6) return C;
  std::cout << "Combo 7 undefined" << std::endl;
  std::exit(0);
}

void Adv(int32_t arg) { A >>= Combo(arg); }

void Bxl(int32_t arg) { B ^= Literal(arg); }

void Bst(int32_t arg) { B = Combo(arg) % 8; }

void Jnz(int32_t arg) {
  if (A != 0) PC = Literal(arg) - 2;
}

void Bxc(int32_t arg) { B ^= C; }

std::vector<int32_t> output;
void Out(int32_t arg) { output.push_back(Combo(arg) % 8); }

void Bdv(int32_t arg) { B = A >> Combo(arg); }

void Cdv(int32_t arg) { C = A >> Combo(arg); }

void ExecuteInstruction() {
  int32_t operation = program[PC];
  int32_t arg = program[PC + 1];
  if (operation == 0)
    Adv(arg);
  else if (operation == 1)
    Bxl(arg);
  else if (operation == 2)
    Bst(arg);
  else if (operation == 3)
    Jnz(arg);
  else if (operation == 4)
    Bxc(arg);
  else if (operation == 5)
    Out(arg);
  else if (operation == 6)
    Bdv(arg);
  else if (operation == 7)
    Cdv(arg);
  else {
    std::cout << "Bad operation" << std::endl;
    exit(0);
  }
}

void ExecuteProgram() {
  while (PC < program.size()) {
    ExecuteInstruction();
    PC += 2;
  }
}

int main() {
  LoadRegisters();
  LoadProgram();
  ExecuteProgram();
  for (int32_t x : output) {
    std::cout << x << ",";
  }
}
