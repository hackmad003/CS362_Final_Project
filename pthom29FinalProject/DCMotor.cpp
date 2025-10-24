#include "DCMotor.hpp"


namespace arduino {

  /* --------------------------------------------------Constructors----------------------------------------------- */
  DCMotor::DCMotor(const AnalogPin& speedPin) noexcept : speedPin(speedPin) {}

  DCMotor::DCMotor(AnalogPin&& speedPin) noexcept : speedPin(speedPin) {}
  
  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void DCMotor::setSpeedPin(const AnalogPin& speedPin) noexcept {this->speedPin = speedPin; }

  void DCMotor::setSpeedPin(AnalogPin&& speedPin) noexcept { this->speedPin = speedPin; }

  void DCMotor::setSpeedPin(pin_size_t pinNumber) noexcept { this->speedPin.setNumber(pinNumber); }

  void DCMotor::setSpeedPin(pin_size_t pinNumber, std::uint8_t speed) noexcept {
    this->speedPin.setNumber(pinNumber);
    this->speedPin.write(speed);
  }

  void DCMotor::setSpeed(std::uint8_t speed) noexcept { this->speedPin.write(speed); }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  [[nodiscard]] std::uint8_t DCMotor::getSpeed(void) const noexcept {
    return static_cast<std::uint8_t>(this->speedPin.read());
  }

} // namespace arduino




