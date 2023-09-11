#include <common/parser.hpp>
#include <iostream>
#include <string>

namespace parser {

void delete_puncts(std::string &text) {
  for (std::string::size_type i = 0; i < text.size(); i++) {
    if (std::ispunct(text[i])) {
      text.erase(i, 1);
    }
  }
}

} // namespace parser