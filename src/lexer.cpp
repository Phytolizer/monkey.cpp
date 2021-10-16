#include "monkey/lexer.hpp"

#include <sstream>

static bool IsLetter(char ch);
static bool IsDigit(char ch);
static bool IsWhitespace(char ch);

monkey::lexer::Lexer::Lexer(std::string_view input) : input_{input} {
  ReadChar();
}

monkey::token::Token monkey::lexer::Lexer::NextToken() {
  token::Token tok = {.type = token::kIllegal, .literal = ""};

  SkipWhitespace();

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
    case '-':
      tok = CreateToken(token::kMinus, ch_);
      break;
    case '/':
      tok = CreateToken(token::kSlash, ch_);
      break;
    case '*':
      tok = CreateToken(token::kAsterisk, ch_);
      break;
    case '!':
      tok = CreateToken(token::kBang, ch_);
      break;
    case '<':
      tok = CreateToken(token::kLt, ch_);
      break;
    case '>':
      tok = CreateToken(token::kGt, ch_);
      break;
    case '\0':
      tok.literal = "";
      tok.type = token::kEof;
      break;
    default:
      if (IsLetter(ch_)) {
        tok.literal = ReadIdentifier();
        tok.type = token::LookupIdent(tok.literal);
        return tok;
      } else if (IsDigit(ch_)) {
        tok.literal = ReadNumber();
        tok.type = token::kInt;
        return tok;
      } else {
        tok = CreateToken(token::kIllegal, ch_);
      }
  }

  ReadChar();
  return tok;
}

void monkey::lexer::Lexer::ReadChar() {
  if (read_position_ >= static_cast<int>(input_.size())) {
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

std::string monkey::lexer::Lexer::ReadIdentifier() {
  int position = position_;
  while (IsLetter(ch_)) {
    ReadChar();
  }
  return input_.substr(position, position_ - position);
}

std::string monkey::lexer::Lexer::ReadNumber() {
  int position = position_;
  while (IsDigit(ch_)) {
    ReadChar();
  }
  return input_.substr(position, position_ - position);
}

void monkey::lexer::Lexer::SkipWhitespace() {
  while (IsWhitespace(ch_)) {
    ReadChar();
  }
}

static bool IsLetter(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

static bool IsDigit(char ch) { return ch >= '0' && ch <= '9'; }

static bool IsWhitespace(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}
