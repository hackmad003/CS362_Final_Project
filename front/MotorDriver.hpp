#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include <cstddef>
#include <cstdint>

#include <Arduino.h>

#include "Motor.hpp"

namespace arduino {
  class MotorDriver {
  private:
    /* -------------------------------------------------Fields-------------------------------------------------- */
    Motor leftMotor, rightMotor;

  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    MotorDriver(const Motor& leftMotor, const Motor& rightMotor) noexcept;

    MotorDriver(Motor&& leftMotor, Motor&& rightMotor) noexcept;

    MotorDriver(const MotorDriver& other) noexcept = default;

    MotorDriver(MotorDriver&& other) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~MotorDriver() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    MotorDriver& operator=(const MotorDriver&) noexcept = default;

    MotorDriver& operator=(MotorDriver&&) noexcept = default;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    void setLeftMotor(const Motor& leftMotor) noexcept;

    void setLeftMotor(Motor&& leftMotor) noexcept;

    void setRightMotor(const Motor& rightMotor) noexcept;

    void setRightMotor(Motor&& rightMotor) noexcept;

    /* ------------------------------------------------Getters-------------------------------------------------- */

    /* ------------------------------------------------Methods-------------------------------------------------- */
    void forward(void) const noexcept;

    void backward(void) const noexcept;

    void left(void) const noexcept;

    void right(void) const noexcept;

    void stop(void) const noexcept;

  };
} // namespace arduino


#endif // MOTOR_HPP

