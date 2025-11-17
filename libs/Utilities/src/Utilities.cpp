#include "Utilities.hpp"

namespace arduino {
  /* ---------------------------------------------------Functions------------------------------------------------- */
  void millisDelay(std::time_t interval, std::time_t& previous, std::function<void()> lambda) noexcept {
    std::time_t current = millis();

    if (current - previous >= interval) {
      previous = current;
      lambda();
    }
  }

} // namespace arduino

