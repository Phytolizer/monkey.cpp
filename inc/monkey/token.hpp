#pragma once

#include <string>
#include <string_view>

namespace monkey::token {
struct TokenType {
  std::string_view value;
};

struct Token {
  TokenType type;
  std::string literal;
};

constexpr TokenType kIllegal = {"ILLEGAL"};
constexpr TokenType kEof = {"EOF"};

constexpr TokenType kIdent = {"IDENT"};
constexpr TokenType kInt = {"INT"};

constexpr TokenType kAssign = {"="};
constexpr TokenType kPlus = {"+"};

constexpr TokenType kComma = {","};
constexpr TokenType kSemicolon = {";"};

constexpr TokenType kLParen = {"("};
constexpr TokenType kRParen = {")"};
constexpr TokenType kLBrace = {"{"};
constexpr TokenType kRBrace = {"}"};

constexpr TokenType kFunction = {"FUNCTION"};
constexpr TokenType kLet = {"LET"};

}  // namespace monkey::token

std::ostream& operator<<(std::ostream& os, const monkey::token::TokenType& tt);
