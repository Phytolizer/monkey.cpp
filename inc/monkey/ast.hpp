#pragma once

#include <memory>
#include <monkey/token.hpp>
#include <string>
#include <vector>

namespace monkey::ast {
struct Node {
  virtual ~Node() = default;
  virtual std::string TokenLiteral() const = 0;
};

struct Statement : Node {};
struct Expression : Node {};

struct Program : Node {
  std::vector<std::unique_ptr<Statement>> statements;

  std::string TokenLiteral() const override;
};

struct Identifier : Expression {
  token::Token token;
  std::string value;

  Identifier() = default;
  Identifier(token::Token token, std::string value);

  std::string TokenLiteral() const override;
};

struct LetStatement : Statement {
  token::Token token;
  Identifier name;
  std::unique_ptr<Expression> value;

  explicit LetStatement(token::Token token);

  std::string TokenLiteral() const override;
};

struct ReturnStatement : Statement {
  token::Token token;
  std::unique_ptr<Expression> return_value;

  explicit ReturnStatement(token::Token token);

  std::string TokenLiteral() const override;
};
}  // namespace monkey::ast
