#pragma once

#include <monkey/token.hpp>
#include <string>

namespace monkey::lexer {
struct Lexer {
 private:
  std::string input_;
  int position_ = 0;
  int read_position_ = 0;
  char ch_ = '\0';

 public:
  explicit Lexer(std::string_view input);

  token::Token NextToken();

 private:
  void ReadChar();
  token::Token CreateToken(const token::TokenType& type, char literal);
};
}  // namespace monkey::lexer
