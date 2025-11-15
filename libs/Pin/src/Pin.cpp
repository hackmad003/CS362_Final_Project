#include "Pin.hpp"

namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  Pin::Pin(pin_size_t number, PinMode mode) noexcept
    : number(number), mode(mode) { pinMode(this->number, this->mode); }

  Pin::Pin(pin_size_t number, PinMode mode, std::int32_t status) noexcept
    : number(number), mode(mode) {}

  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void Pin::setNumber(pin_size_t number) noexcept {
    this->number = number;
    pinMode(this->number, this->mode);
  }

  void Pin::setMode(PinMode mode) noexcept {
    this->mode = mode;
    pinMode(this->number, this->mode);
  }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  [[nodiscard]] pin_size_t Pin::getNumber(void) const noexcept { return this->number; }

  [[nodiscard]] PinMode Pin::getMode(void) const noexcept { return this->mode; }
  
  /* ----------------------------------------------------Methods-------------------------------------------------- */
  [[nodiscard]] ::PinStatus Pin::digitalRead(void) const noexcept { return ::digitalRead(this->number); }

  [[nodiscard]] void Pin::digitalWrite(::PinStatus status) const noexcept { ::digitalWrite(this->number, status); }

  [[nodiscard]] std::int32_t Pin::analogRead(void) const noexcept { return ::analogRead(this->number); }

  [[nodiscard]] void Pin::analogWrite(std::int32_t status) const noexcept { ::analogWrite(this->number, status); }

} // arduino

