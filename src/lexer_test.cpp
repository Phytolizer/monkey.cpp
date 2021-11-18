#include <doctest/doctest.h>

#include <array>
#include <monkey/lexer.hpp>
#include <monkey/token.hpp>
#include <string_view>

namespace token = monkey::token;
using monkey::lexer::Lexer;

TEST_CASE("Lexer: next token") {
  constexpr std::string_view kInput = R"(
    let five = 5;
    let ten = 10;

    let add = fn(x, y) {
      x + y;
    };

    let result = add(five, ten);

    !-/*5;
    5 < 10 > 5;

    if (5 < 10) {
      return true;
    } else {
      return false;
    }

    10 == 10;
    10 != 9;
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
      Test{token::kBang, "!"},      Test{token::kMinus, "-"},
      Test{token::kSlash, "/"},     Test{token::kAsterisk, "*"},
      Test{token::kInt, "5"},       Test{token::kSemicolon, ";"},
      Test{token::kInt, "5"},       Test{token::kLt, "<"},
      Test{token::kInt, "10"},      Test{token::kGt, ">"},
      Test{token::kInt, "5"},       Test{token::kSemicolon, ";"},
      Test{token::kIf, "if"},       Test{token::kLParen, "("},
      Test{token::kInt, "5"},       Test{token::kLt, "<"},
      Test{token::kInt, "10"},      Test{token::kRParen, ")"},
      Test{token::kLBrace, "{"},    Test{token::kReturn, "return"},
      Test{token::kTrue, "true"},   Test{token::kSemicolon, ";"},
      Test{token::kRBrace, "}"},    Test{token::kElse, "else"},
      Test{token::kLBrace, "{"},    Test{token::kReturn, "return"},
      Test{token::kFalse, "false"}, Test{token::kSemicolon, ";"},
      Test{token::kRBrace, "}"},    Test{token::kInt, "10"},
      Test{token::kEq, "=="},       Test{token::kInt, "10"},
      Test{token::kSemicolon, ";"}, Test{token::kInt, "10"},
      Test{token::kNotEq, "!="},    Test{token::kInt, "9"},
      Test{token::kSemicolon, ";"}, Test{token::kEof, ""},
  };

  auto lexer = Lexer{kInput};

  for (const auto& tt : kTests) {
    auto tok = lexer.NextToken();

    CHECK_EQ(tok.type, tt.expected_type);
    CHECK_EQ(tok.literal, tt.expected_literal);
  }
}
