#include "Joystick.hpp"

namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  Joystick::Joystick(const Pin& xPin, const Pin& yPin) noexcept : xPin(xPin), yPin(yPin) {}

  Joystick::Joystick(Pin&& xPin, Pin&& yPin) noexcept : xPin(xPin), yPin(yPin) {}
  
  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void Joystick::setXPin(const Pin& xPin) noexcept {
    this->xPin = xPin;
    this->xPin.analogWrite(0);
  }

  void Joystick::setXPin(Pin&& xPin) noexcept {
    this->xPin = xPin;
    this->xPin.analogWrite(0);
  }

  void Joystick::setYPin(const Pin& yPin) noexcept {
    this->yPin = yPin;
    this->yPin.analogWrite(0);
  }

  void Joystick::setYPin(Pin&& yPin) noexcept {
    this->yPin = yPin;
    this->yPin.analogWrite(0);
  }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  [[nodiscard]] std::int32_t Joystick::getX(void) const noexcept { return this->xPin.analogRead(); }
    
  [[nodiscard]] std::int32_t Joystick::getY(void) const noexcept { return this->yPin.analogRead(); }  

} // namespace arduino

