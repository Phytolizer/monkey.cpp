#include <subprocess.h>

#include <array>
#include <iostream>
#include <monkey/repl.hpp>

int main() {
  constexpr std::array<const char*, 2> kCommandLine = {"uu-whoami", nullptr};
  subprocess_s subprocess;
  int result = subprocess_create(
      kCommandLine.data(),
      subprocess_option_inherit_environment | subprocess_option_no_window,
      &subprocess);
  if (result != 0) {
    std::cerr << "Error running `uu-whoami`!\n";
    return 1;
  }
  FILE* p_stdout = subprocess_stdout(&subprocess);
  int retval = 0;
  result = subprocess_join(&subprocess, &retval);
  if (result != 0) {
    std::cerr << "Error waiting on `uu-whoami`!\n";
    return 1;
  }
  if (retval != 0) {
    std::cerr << "`uu-whoami` returned " << retval << "!\n";
    return 1;
  }
  std::array<char, 32> username;
  username.fill('\0');
  fgets(username.data(), username.size(), p_stdout);
  subprocess_destroy(&subprocess);
  std::string username_str = username.data();
  std::cout << "Hello " << username_str
            << "! This is the Monkey programming language!\n";
  std::cout << "Feel free to type in commands\n";
  monkey::repl::Start(std::cin, std::cout);
  return 0;
}
