#include <array>
#include <iostream>

#include "monkey/repl/user.hpp"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(__linux__)
#include <unistd.h>
#else
#error "Unsupported platform"
#endif

void monkey::repl::PrintUser() {
#if defined(_WIN32)
  std::array<wchar_t, 32> buf;
  buf.fill(L'\0');
  int ret = GetUserNameW(buf.data(), buf.size());
  if (ret == 0) {
    std::cerr << GetLastError() << "\n";
    return;
  }
  std::wcout << buf.data();
#elif defined(__linux__)
  std::array<char, 32> buf;
  buf.fill('\0');
  int ret = getlogin_r(buf.data(), buf.size());
  if (ret != 0) {
    std::perror("getlogin_r");
    return;
  }
  std::cout << buf.data();
#endif
}
