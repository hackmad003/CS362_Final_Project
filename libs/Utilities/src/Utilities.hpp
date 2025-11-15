#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstddef>
#include <ctime>
#include <functional>

#include <Arduino.h>

namespace arduino {
  /* ---------------------------------------------------Functions------------------------------------------------- */
  void millisDelay(std::time_t interval, std::time_t& previous, std::function<void()> lambda) noexcept;

} // namespace arduino


#endif // UTILITIES_HPP

