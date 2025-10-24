#include "DCMotor.hpp"


namespace arduino {

  /* --------------------------------------------------Constructors----------------------------------------------- */
  DCMotor::DCMotor(void) noexcept {}

  DCMotor::DCMotor(const AnalogPin& analogPin) noexcept : analogPin(analogPin) {}

  DCMotor::DCMotor(AnalogPin&& analogPin) noexcept : analogPin(analogPin) {}
  
  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void DCMotor::setAnalogPin(const AnalogPin& analogPin) noexcept {this->analogPin = analogPin; }

  void DCMotor::setAnalogPin(AnalogPin&& analogPin) noexcept { this->analogPin = analogPin; }

  // TODO
  void DCMotor::setSpeed(std::uint32_t speed) noexcept {
      //
  }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  // TODO
  [[nodiscard]] std::uint32_t DCMotor::getSpeed(void) const noexcept {
      return 0;
  }

} // namespace arduino




