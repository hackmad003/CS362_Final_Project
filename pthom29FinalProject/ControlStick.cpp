#include "ControlStick.hpp"


namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  ControlStick::ControlStick(const AnalogPin& vrxPin, const AnalogPin& vryPin, const DigitalPin& swPin)
    noexcept : vrxPin(vrxPin), vryPin(vryPin), swPin(swPin) {}

  ControlStick::ControlStick(AnalogPin&& vrxPin, AnalogPin&& vryPin, DigitalPin&& swPin)
    noexcept : vrxPin(vrxPin), vryPin(vryPin), swPin(swPin) {}

  /* ----------------------------------------------Overloaded Operators------------------------------------------- */
  [[nodiscard]] ControlStick::operator bool(void) const noexcept { return this->swPin.read() != 0; }

  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void ControlStick::setVrxPin(const AnalogPin& vrxPin) noexcept { this->vrxPin = vrxPin; }

  void ControlStick::setVrxPin(AnalogPin&& vrxPin) noexcept { this->vrxPin = vrxPin; }

  void ControlStick::setVryPin(const AnalogPin& vryPin) noexcept { this->vryPin = vryPin; }

  void ControlStick::setVryPin(AnalogPin&& vryPin) noexcept { this->vrxPin = vrxPin; }

  void ControlStick::setSwPin(const DigitalPin& swPin) noexcept { this->swPin = swPin; }
    
  void ControlStick::setSwPim(DigitalPin&& swPin) noexcept { this->swPin = swPin; }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  [[nodiscard]] std::int32_t ControlStick::getX(void) const noexcept { return this->vrxPin.read(); }

  [[nodiscard]] std::int32_t ControlStick::getY(void) const noexcept { return this->vryPin.read(); }

  /* ----------------------------------------------------Methods-------------------------------------------------- */
  [[nodiscard]] bool ControlStick::isPressed(void) const noexcept { return this->swPin.read() != 0; }

} // namespace arduino
