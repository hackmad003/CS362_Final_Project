#include "Pin.hpp"


namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  Pin::Pin(PinMode mode) noexcept : number(0), mode(mode) { pinMode(this->number, this->mode); }

  Pin::Pin(pin_size_t number, PinMode mode) noexcept 
    : number(number), mode(mode) { pinMode(this->number, this->mode); }

  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void Pin::setMode(PinMode mode) noexcept {
    this->mode = mode;
    pinMode(this->number, this->mode);
  }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  [[nodiscard]] pin_size_t Pin::getNumber(void) const noexcept { return this->number; }

  [[nodiscard]] PinMode Pin::getMode(void) const noexcept { return this->mode; }

} // arduino
