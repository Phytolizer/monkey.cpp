#include "monkey/token.hpp"

#include <unordered_map>

static const std::unordered_map<std::string, monkey::token::TokenType>
    kKeywords = {
        {"fn", monkey::token::kFunction},
        {"let", monkey::token::kLet},
};

std::ostream& monkey::token::operator<<(std::ostream& os,
                                        const monkey::token::TokenType& tt) {
  return os << tt.value;
}
bool monkey::token::TokenType::operator==(const TokenType& other) const {
  return value == other.value;
}

monkey::token::TokenType monkey::token::LookupIdent(const std::string& ident) {
  auto it = kKeywords.find(ident);
  if (it != kKeywords.end()) {
    return it->second;
  }
  return kIdent;
}
