#include "monkey/token.hpp"

std::ostream& operator<<(std::ostream& os, const monkey::token::TokenType& tt) {
  return os << tt.value;
}
