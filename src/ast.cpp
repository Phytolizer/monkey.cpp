#include "monkey/ast.hpp"

std::string monkey::ast::Program::TokenLiteral() const {
  if (statements.empty()) {
    return "";
  }
  return statements[0]->TokenLiteral();
}

monkey::ast::Identifier::Identifier(token::Token token, std::string value)
    : token{token}, value{value} {}

std::string monkey::ast::Identifier::TokenLiteral() const {
  return token.literal;
}

monkey::ast::LetStatement::LetStatement(token::Token token) : token{token} {}
std::string monkey::ast::LetStatement::TokenLiteral() const {
  return token.literal;
}
