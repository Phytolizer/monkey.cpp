#pragma once

#include <string>
#include <vector>

#include "monkey/ast.hpp"
#include "monkey/lexer.hpp"
#include "monkey/token.hpp"
namespace monkey::parser {
struct Parser {
  lexer::Lexer l;
  std::vector<std::string> errors;

  token::Token cur_token;
  token::Token peek_token;

  explicit Parser(lexer::Lexer&& l);

  ast::Program ParseProgram();

  const std::vector<std::string>& Errors() const;

 private:
  void NextToken();
  std::unique_ptr<ast::Statement> ParseStatement();
  std::unique_ptr<ast::LetStatement> ParseLetStatement();
  bool ExpectPeek(const token::TokenType& type);
  bool CurTokenIs(const token::TokenType& type);
  bool PeekTokenIs(const token::TokenType& type);
  void PeekError(const token::TokenType& type);
};
}  // namespace monkey::parser
