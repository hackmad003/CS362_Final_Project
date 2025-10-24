#include "AnalogPin.hpp"


namespace arduino {

  /* --------------------------------------------------Constructors----------------------------------------------- */
  AnalogPin::AnalogPin(pin_size_t number, PinMode mode) noexcept : Pin(number, mode) {}

  AnalogPin::AnalogPin(pin_size_t number, std::int32_t status, PinMode mode) noexcept : Pin(number, mode) {
    analogWrite(this->number, status);
  }

  /* ----------------------------------------------Overloaded Operators------------------------------------------- */
  [[nodiscard]] bool AnalogPin::operator==(const AnalogPin& rhs) const noexcept {
    return this->number == rhs.number && 
           analogRead(this->number) == analogRead(rhs.number) && 
           this->mode == rhs.mode;
  }

  [[nodiscard]] bool AnalogPin::operator==(AnalogPin&& rhs) const noexcept {
    return this->number == rhs.number && 
           analogRead(this->number) == analogRead(rhs.number) && 
           this->mode == rhs.mode;
  }

  [[nodiscard]] bool AnalogPin::operator!=(const AnalogPin& rhs) const noexcept { return !(*this == rhs); }

  [[nodiscard]] bool AnalogPin::operator!=(AnalogPin&& rhs) const noexcept { return !(*this == rhs); }

  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void AnalogPin::setNumber(pin_size_t number) noexcept {
    this->number = number;
    pinMode(this->number, this->mode);
  }

  /* ----------------------------------------------------Methods-------------------------------------------------- */
  [[nodiscard]] std::int32_t AnalogPin::read(void) const noexcept { return analogRead(this->number); }

  [[nodiscard]] void AnalogPin::write(std::int32_t status) const noexcept { analogWrite(this->number, status); }

} // namespace arduino
