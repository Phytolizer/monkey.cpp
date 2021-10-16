#include "monkey/parser.hpp"

#include <sstream>

monkey::parser::Parser::Parser(monkey::lexer::Lexer&& l) : l{l} {
  NextToken();
  NextToken();
}

void monkey::parser::Parser::NextToken() {
  cur_token = peek_token;
  peek_token = l.NextToken();
}

monkey::ast::Program monkey::parser::Parser::ParseProgram() {
  ast::Program program;

  while (cur_token.type != token::kEof) {
    auto stmt = ParseStatement();
    if (stmt) {
      program.statements.emplace_back(std::move(stmt));
    }
    NextToken();
  }

  return program;
}

const std::vector<std::string>& monkey::parser::Parser::Errors() const {
  return errors;
}

std::unique_ptr<monkey::ast::Statement>
monkey::parser::Parser::ParseStatement() {
  if (cur_token.type == token::kLet) {
    return ParseLetStatement();
  }
  return nullptr;
}

std::unique_ptr<monkey::ast::LetStatement>
monkey::parser::Parser::ParseLetStatement() {
  ast::LetStatement stmt{cur_token};

  if (!ExpectPeek(token::kIdent)) {
    return nullptr;
  }

  stmt.name = ast::Identifier{cur_token, cur_token.literal};

  if (!ExpectPeek(token::kAssign)) {
    return nullptr;
  }

  // TODO
  while (!CurTokenIs(token::kSemicolon)) {
    NextToken();
  }

  return std::make_unique<ast::LetStatement>(std::move(stmt));
}

bool monkey::parser::Parser::ExpectPeek(const token::TokenType& type) {
  if (PeekTokenIs(type)) {
    NextToken();
    return true;
  }
  PeekError(type);
  return false;
}

bool monkey::parser::Parser::CurTokenIs(const token::TokenType& type) {
  return cur_token.type == type;
}

bool monkey::parser::Parser::PeekTokenIs(const token::TokenType& type) {
  return peek_token.type == type;
}

void monkey::parser::Parser::PeekError(const token::TokenType& type) {
  std::ostringstream ss;
  ss << "expected next token to be " << type << ", got " << peek_token.type
     << " instead";
  errors.emplace_back(ss.str());
}
