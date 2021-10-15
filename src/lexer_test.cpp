#include <gtest/gtest.h>

#include <monkey/lexer.hpp>
#include <monkey/token.hpp>
#include <string_view>

using monkey::lexer::Lexer;

TEST(Lexer, NextToken) {
  constexpr std::string_view kInput = "=+(){},;";
  struct Test {
    monkey::token::TokenType expected_type;
    std::string_view expected_literal;
  };

  constexpr std::array kTests = {
      Test{monkey::token::kAssign, "="}, Test{monkey::token::kPlus, "+"},
      Test{monkey::token::kLParen, "("}, Test{monkey::token::kRParen, ")"},
      Test{monkey::token::kLBrace, "{"}, Test{monkey::token::kRBrace, "}"},
      Test{monkey::token::kComma, ","},  Test{monkey::token::kSemicolon, ";"},
  };

  auto lexer = Lexer{kInput};

  for (const auto& tt : kTests) {
    auto tok = lexer.NextToken();

    EXPECT_EQ(tok.type, tt.expected_type);
    EXPECT_EQ(tok.literal, tt.expected_literal);
  }
}
