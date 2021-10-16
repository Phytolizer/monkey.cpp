#pragma once

#include <ostream>
#include <string>
#include <string_view>

namespace monkey::token {
struct TokenType {
  std::string_view value;

  bool operator==(const TokenType& other) const;
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
constexpr TokenType kMinus = {"-"};
constexpr TokenType kSlash = {"/"};
constexpr TokenType kAsterisk = {"*"};
constexpr TokenType kBang = {"!"};

constexpr TokenType kLt = {"<"};
constexpr TokenType kGt = {">"};

constexpr TokenType kComma = {","};
constexpr TokenType kSemicolon = {";"};

constexpr TokenType kLParen = {"("};
constexpr TokenType kRParen = {")"};
constexpr TokenType kLBrace = {"{"};
constexpr TokenType kRBrace = {"}"};

constexpr TokenType kFunction = {"FUNCTION"};
constexpr TokenType kLet = {"LET"};

std::ostream& operator<<(std::ostream& os, const TokenType& tt);

TokenType LookupIdent(const std::string& ident);
}  // namespace monkey::token
