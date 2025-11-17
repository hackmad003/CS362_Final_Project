#include "Motor.hpp"

namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  Motor::Motor(const Pin& digitalPin1, const Pin& digitalPin2, const Pin& analogPin) noexcept
    : digitalPin1(digitalPin1), digitalPin2(digitalPin2), analogPin(analogPin) {
    this->digitalPin1.setMode(PinMode::OUTPUT);
    this->digitalPin2.setMode(PinMode::OUTPUT);
    this->analogPin.setMode(PinMode::OUTPUT);
  }

  Motor::Motor(Pin&& digitalPin1, Pin&& digitalPin2, Pin&& analogPin) noexcept
    : digitalPin1(digitalPin1), digitalPin2(digitalPin2), analogPin(analogPin) {
    this->digitalPin1.setMode(PinMode::OUTPUT);
    this->digitalPin2.setMode(PinMode::OUTPUT);
    this->analogPin.setMode(PinMode::OUTPUT);
  }

  /* ----------------------------------------------Overloaded Operators------------------------------------------- */
  
  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void Motor::setDigitalPin1(const Pin& digitalPin1) noexcept {
    this->digitalPin1 = digitalPin1;
    this->digitalPin1.setMode(PinMode::OUTPUT);
  }

  void Motor::setDigitalPin1(Pin&& digitalPin1) noexcept {
    this->digitalPin1 = digitalPin1;
    this->digitalPin1.setMode(PinMode::OUTPUT);
  }

  void Motor::setDigitalPin2(const Pin& digitalPin2) noexcept {
    this->digitalPin2 = digitalPin2;
    this->digitalPin2.setMode(PinMode::OUTPUT);
  }

  void Motor::setDigitalPin2(Pin&& digitalPin2) noexcept {
    this->digitalPin2 = digitalPin2;
    this->digitalPin2.setMode(PinMode::OUTPUT);
  }

  void Motor::setAnalogPin(const Pin& analogPin) noexcept {
    this->analogPin = analogPin;
    this->analogPin.setMode(PinMode::OUTPUT);
  }

  void Motor::setAnalogPin(Pin&& analogPin) noexcept {
    this->analogPin = analogPin;
    this->analogPin.setMode(PinMode::OUTPUT);
  }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  
  
  /* ----------------------------------------------------Methods-------------------------------------------------- */
  void Motor::forward(void) const noexcept {
    this->digitalPin1.digitalWrite(PinStatus::LOW); // IN1
    this->digitalPin2.digitalWrite(PinStatus::HIGH); // IN2
    this->analogPin.analogWrite(150);
  }

  void Motor::backward(void) const noexcept {
    this->digitalPin1.digitalWrite(PinStatus::HIGH); // IN1
    this->digitalPin2.digitalWrite(PinStatus::LOW); // IN2
    this->analogPin.analogWrite(150);
  }

  void Motor::stop(void) const noexcept {
    this->digitalPin1.digitalWrite(PinStatus::LOW); // IN1
    this->digitalPin2.digitalWrite(PinStatus::LOW); // IN2
    this->analogPin.analogWrite(0);
  }

} // namespace arduino
