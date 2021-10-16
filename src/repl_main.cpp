#include <array>
#include <iostream>
#include <monkey/repl.hpp>
#include <monkey/repl/user.hpp>

int main() {
  std::cout << "Hello ";
  monkey::repl::PrintUser();
  std::cout << "! This is the Monkey programming language!\n";
  std::cout << "Feel free to type in commands\n";
  monkey::repl::Start(std::cin, std::cout);
  return 0;
}
