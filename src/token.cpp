#include "monkey/token.hpp"

std::ostream& monkey::token::operator<<(std::ostream& os, const monkey::token::TokenType& tt) {
  return os << tt.value;
}
bool monkey::token::TokenType::operator==(const TokenType& other) const {
  return value == other.value;
}
