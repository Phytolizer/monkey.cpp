#include "monkey/ast.hpp"

std::string monkey::ast::Program::TokenLiteral() const {
  if (statements.empty()) {
    return "";
  }
  return statements[0].TokenLiteral();
}

std::string monkey::ast::Identifier::TokenLiteral() const {
  return token.literal;
}

std::string monkey::ast::LetStatement::TokenLiteral() const {
  return token.literal;
}
