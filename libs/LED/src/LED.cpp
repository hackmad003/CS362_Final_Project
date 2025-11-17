#include "LED.hpp"

namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  LED::LED(const Pin& pin) noexcept : pin(pin), color(LED::Color::WHITE) { this->setModeToOutput(); }

  LED::LED(Pin&& pin) noexcept : pin(pin), color(LED::Color::WHITE) { this->setModeToOutput(); }

  LED::LED(const Pin& pin, Color color) noexcept : pin(pin), color(color) { this->setModeToOutput(); }

  LED::LED(Pin&& pin, Color color) noexcept : pin(pin), color(color) { this->setModeToOutput(); }

  /* ----------------------------------------------Overloaded Operators------------------------------------------- */
  LED& LED::operator~(void) noexcept {
    this->pin.digitalWrite(static_cast<PinStatus>(!this->pin.digitalRead()));
    return *this;
  }

  [[nodiscard]] LED::operator bool() const noexcept { return this->pin.digitalRead() == PinStatus::HIGH; }

  /* -----------------------------------------------Setters (Private)--------------------------------------------- */
  void LED::setModeToOutput(void) noexcept {
    // Set the pin's mode to output if it is not already
    PinMode pinMode = this->pin.getMode();
    if (pinMode != PinMode::OUTPUT && pinMode != PinMode::OUTPUT_OPENDRAIN) {
      this->pin.setMode(PinMode::OUTPUT);
    }
  }

  /* ------------------------------------------------Setters (Public)--------------------------------------------- */
  void LED::setPin(const Pin& pin) noexcept {
    this->pin = pin;
    this->setModeToOutput();
  }

  void LED::setPin(Pin&& pin) noexcept {
    this->pin = pin;
    this->setModeToOutput();
  }

  void LED::setBrightness(std::int32_t brightness) noexcept { this->pin.analogWrite(brightness); }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  [[nodiscard]] Pin LED::getPin(void) const noexcept { return this->pin; }

  [[nodiscard]] std::int32_t LED::getBrightness(void) const noexcept { return this->pin.analogRead(); }

  /* ----------------------------------------------------Methods-------------------------------------------------- */
  [[nodiscard]] bool LED::isOn(void) const noexcept { return this->pin.digitalRead() == PinStatus::HIGH; }

  [[nodiscard]] bool LED::isOff(void) const noexcept { return this->pin.digitalRead() == PinStatus::LOW; }

  void LED::turnOn(void) noexcept { this->pin.digitalWrite(PinStatus::HIGH); }

  void LED::turnOff(void) noexcept { this->pin.digitalWrite(PinStatus::LOW); }

} // namespace arduino

