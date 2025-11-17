#include "MotorDriver.hpp"

namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  MotorDriver::MotorDriver(const Motor& leftMotor, const Motor& rightMotor) noexcept
    : leftMotor(leftMotor), rightMotor(rightMotor) {}

  MotorDriver::MotorDriver(Motor&& leftMotor, Motor&& rightMotor) noexcept
    : leftMotor(leftMotor), rightMotor(rightMotor) {}

  /* ----------------------------------------------Overloaded Operators------------------------------------------- */
  
  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void MotorDriver::setLeftMotor(const Motor& leftMotor) noexcept { this->leftMotor = leftMotor; }

  void MotorDriver::setLeftMotor(Motor&& leftMotor) noexcept { this->leftMotor = leftMotor; }

  void MotorDriver::setRightMotor(const Motor& rightMotor) noexcept { this->rightMotor = rightMotor; }

  void MotorDriver::setRightMotor(Motor&& rightMotor) noexcept { this->rightMotor = rightMotor; }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  
  
  /* ----------------------------------------------------Methods-------------------------------------------------- */
  void MotorDriver::forward(void) const noexcept {
    this->leftMotor.forward();
    this->rightMotor.forward();
  }

  void MotorDriver::backward(void) const noexcept {
    this->leftMotor.backward();
    this->rightMotor.backward();
  }

  void MotorDriver::left(void) const noexcept {
    this->leftMotor.forward();
    this->rightMotor.stop();
  }

  void MotorDriver::right(void) const noexcept {
    
  }

  void MotorDriver::stop(void) const noexcept {
    this->leftMotor.stop();
    this->rightMotor.stop();
  }

} // namespace arduino
