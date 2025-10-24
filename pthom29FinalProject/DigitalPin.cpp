#include "DigitalPin.hpp"


namespace arduino {

  /* --------------------------------------------------Constructors----------------------------------------------- */
  DigitalPin::DigitalPin(pin_size_t number, PinMode mode) noexcept : Pin(number, mode) {}

  DigitalPin::DigitalPin(pin_size_t number, PinStatus status, PinMode mode) noexcept : Pin(number, mode) {
    digitalWrite(this->number, status);
  }

  /* ----------------------------------------------Overloaded Operators------------------------------------------- */
  [[nodiscard]] bool DigitalPin::operator==(const DigitalPin& rhs) const noexcept {
    return this->number == rhs.number && 
           digitalRead(this->number) == digitalRead(rhs.number) && 
           this->mode == rhs.mode;
  }

  [[nodiscard]] bool DigitalPin::operator==(DigitalPin&& rhs) const noexcept {
    return this->number == rhs.number && 
           digitalRead(this->number) == digitalRead(rhs.number) && 
           this->mode == rhs.mode;
  }

  [[nodiscard]] bool DigitalPin::operator!=(const DigitalPin& rhs) const noexcept { return !(*this == rhs); }

  [[nodiscard]] bool DigitalPin::operator!=(DigitalPin&& rhs) const noexcept { return !(*this == rhs); }

  [[nodiscard]] DigitalPin::operator bool(void) const noexcept { return digitalRead(this->number); }

  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void DigitalPin::setNumber(pin_size_t number) noexcept {
    this->number = number;
    pinMode(this->number, this->mode);
  }

  /* ----------------------------------------------------Methods-------------------------------------------------- */
  [[nodiscard]] std::int32_t DigitalPin::read(void) const noexcept { return digitalRead(this->number); }

  [[nodiscard]] void DigitalPin::write(std::int32_t status) const noexcept { digitalWrite(this->number, status); }

} // namespace arduino
