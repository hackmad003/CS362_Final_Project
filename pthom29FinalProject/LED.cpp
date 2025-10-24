#include "LED.hpp"


namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  LED::LED(pin_size_t pinNumber) noexcept : DigitalPin(pinNumber, OUTPUT) {}

  LED::LED(pin_size_t pinNumber, bool status) noexcept 
    : DigitalPin(pinNumber, static_cast<PinStatus>(status), OUTPUT) {}

  /* ----------------------------------------------------Methods-------------------------------------------------- */
  bool LED::isOn(void) noexcept { return static_cast<bool>(digitalRead(this->number)); }

  bool LED::isOff(void) noexcept { return !this->isOn(); }

  void LED::turnOn(void) noexcept { digitalWrite(this->number, HIGH); }

  void LED::turnOff(void) noexcept { digitalWrite(this->number, LOW); }

  void LED::flip(void) noexcept {
    digitalWrite(this->number, !static_cast<bool>(digitalRead(this->number)));
  }

} // namespace arduino
