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
  char PeekChar();
  token::Token CreateToken(const token::TokenType& type, char literal);
  token::Token CreateToken(const token::TokenType& type, char c1, char c2);
  std::string ReadIdentifier();
  std::string ReadNumber();
  void SkipWhitespace();
};
}  // namespace monkey::lexer
