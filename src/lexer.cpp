#include "monkey/lexer.hpp"

#include <sstream>

monkey::lexer::Lexer::Lexer(std::string_view input) : input_{input} {
  ReadChar();
}

monkey::token::Token monkey::lexer::Lexer::NextToken() {
  token::Token tok = {.type = token::kIllegal, .literal = ""};

  switch (ch_) {
    case '=':
      tok = CreateToken(token::kAssign, ch_);
      break;
    case ';':
      tok = CreateToken(token::kSemicolon, ch_);
      break;
    case '(':
      tok = CreateToken(token::kLParen, ch_);
      break;
    case ')':
      tok = CreateToken(token::kRParen, ch_);
      break;
    case '{':
      tok = CreateToken(token::kLBrace, ch_);
      break;
    case '}':
      tok = CreateToken(token::kRBrace, ch_);
      break;
    case ',':
      tok = CreateToken(token::kComma, ch_);
      break;
    case '+':
      tok = CreateToken(token::kPlus, ch_);
      break;
    case '\0':
      tok.literal = "";
      tok.type = token::kEof;
      break;
  }

  ReadChar();
  return tok;
}

void monkey::lexer::Lexer::ReadChar() {
  if (read_position_ >= input_.size()) {
    ch_ = '\0';
  } else {
    ch_ = input_[read_position_];
  }
  position_ = read_position_;
  ++read_position_;
}

monkey::token::Token monkey::lexer::Lexer::CreateToken(
    const token::TokenType& type, char literal) {
  std::ostringstream ss;
  ss << literal;
  return token::Token{.type = type, .literal = ss.str()};
}
