#include <gtest/gtest.h>

#include <monkey/lexer.hpp>
#include <monkey/token.hpp>
#include <string_view>

namespace token = monkey::token;
using monkey::lexer::Lexer;

TEST(Lexer, NextToken) {
  constexpr std::string_view kInput = R"(
    let five = 5;
    let ten = 10;

    let add = fn(x, y) {
      x + y;
    };

    let result = add(five, ten);
  )";
  struct Test {
    monkey::token::TokenType expected_type;
    std::string_view expected_literal;
  };

  constexpr std::array kTests = {
      Test{token::kLet, "let"},     Test{token::kIdent, "five"},
      Test{token::kAssign, "="},    Test{token::kInt, "5"},
      Test{token::kSemicolon, ";"}, Test{token::kLet, "let"},
      Test{token::kIdent, "ten"},   Test{token::kAssign, "="},
      Test{token::kInt, "10"},      Test{token::kSemicolon, ";"},
      Test{token::kLet, "let"},     Test{token::kIdent, "add"},
      Test{token::kAssign, "="},    Test{token::kFunction, "fn"},
      Test{token::kLParen, "("},    Test{token::kIdent, "x"},
      Test{token::kComma, ","},     Test{token::kIdent, "y"},
      Test{token::kRParen, ")"},    Test{token::kLBrace, "{"},
      Test{token::kIdent, "x"},     Test{token::kPlus, "+"},
      Test{token::kIdent, "y"},     Test{token::kSemicolon, ";"},
      Test{token::kRBrace, "}"},    Test{token::kSemicolon, ";"},
      Test{token::kLet, "let"},     Test{token::kIdent, "result"},
      Test{token::kAssign, "="},    Test{token::kIdent, "add"},
      Test{token::kLParen, "("},    Test{token::kIdent, "five"},
      Test{token::kComma, ","},     Test{token::kIdent, "ten"},
      Test{token::kRParen, ")"},    Test{token::kSemicolon, ";"},
      Test{token::kEof, ""},
  };

  auto lexer = Lexer{kInput};

  for (const auto& tt : kTests) {
    auto tok = lexer.NextToken();

    EXPECT_EQ(tok.type, tt.expected_type);
    EXPECT_EQ(tok.literal, tt.expected_literal);
  }
}
