#include <doctest/doctest.h>

#include <array>
#include <monkey/parser.hpp>
#include <string_view>

using monkey::ast::LetStatement;
using monkey::lexer::Lexer;
using monkey::parser::Parser;

static void CheckParserErrors(const Parser& p);
static void TestLetStatement(const monkey::ast::Statement* stmt,
                             std::string_view name);

TEST_CASE("Parser: let statements") {
  constexpr std::string_view kInput = R"(
    let x = 5;
    let y = 10;
    let foobar = 838383;
  )";

  auto l = Lexer{kInput};
  auto p = Parser{std::move(l)};

  auto program = p.ParseProgram();
  CheckParserErrors(p);
  REQUIRE_EQ(program.statements.size(), 3);

  struct Test {
    std::string_view expected_identifier;
  };

  constexpr std::array kTests = {
      Test{"x"},
      Test{"y"},
      Test{"foobar"},
  };

  for (std::size_t i = 0; i < kTests.size(); ++i) {
    const auto& tt = kTests[i];
    const auto* stmt = program.statements[i].get();
    TestLetStatement(stmt, tt.expected_identifier);
  }
}

static void CheckParserErrors(const Parser& p) {
  CHECK(p.Errors().empty());
  for (const auto& err : p.Errors()) {
    FAIL_CHECK(err);
  }
}

static void TestLetStatement(const monkey::ast::Statement* stmt,
                             std::string_view name) {
  CHECK_EQ(stmt->TokenLiteral(), "let");
  const auto* let_stmt = dynamic_cast<const LetStatement*>(stmt);
  REQUIRE_NE(let_stmt, nullptr);
  CHECK_EQ(let_stmt->name.value, name);
  CHECK_EQ(let_stmt->name.TokenLiteral(), name);
}
