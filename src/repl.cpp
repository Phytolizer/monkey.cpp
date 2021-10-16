#include "monkey/repl.hpp"

#include <istream>
#include <monkey/lexer.hpp>
#include <monkey/token.hpp>
#include <ostream>

constexpr std::string_view kPrompt = ">> ";

void monkey::repl::Start(std::istream& in, std::ostream& out) {
  while (true) {
    out << kPrompt << std::flush;
    std::string line;
    if (!std::getline(in, line)) {
      break;
    }

    auto l = lexer::Lexer{line};

    for (auto tok = l.NextToken(); tok.type != token::kEof;
         tok = l.NextToken()) {
      out << tok << "\n";
    }
  }
}
