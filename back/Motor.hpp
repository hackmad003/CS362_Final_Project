#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <cstddef>
#include <cstdint>

#include <Arduino.h>

#include <Pin.hpp>

namespace arduino {
  class Motor {
  private:
    /* -------------------------------------------------Fields-------------------------------------------------- */
    Pin digitalPin1, digitalPin2, analogPin;

  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    Motor(const Pin& digitalPin1, const Pin& digitalPin2, const Pin& analogPin) noexcept;

    Motor(Pin&& digitalPin1, Pin&& digitalPin2, Pin&& analogPin) noexcept;

    Motor(const Motor& other) noexcept = default;

    Motor(Motor&& other) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~Motor() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    Motor& operator=(const Motor&) noexcept = default;

    Motor& operator=(Motor&&) noexcept = default;

    [[nodiscard]] explicit operator bool() const noexcept;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    void setDigitalPin1(const Pin& digitalPin1) noexcept;

    void setDigitalPin1(Pin&& digitalPin1) noexcept;

    void setDigitalPin2(const Pin& digitalPin2) noexcept;

    void setDigitalPin2(Pin&& digitalPin2) noexcept;

    void setAnalogPin(const Pin& analogPin) noexcept;

    void setAnalogPin(Pin&& analogPin) noexcept;

    /* ------------------------------------------------Getters-------------------------------------------------- */
    

    /* ------------------------------------------------Methods-------------------------------------------------- */
    void turnOn(void) const noexcept;

    void turnOff(void) const noexcept;

    [[nodiscard]] bool isOn(void) const noexcept;

    [[nodiscard]] bool isOff(void) const noexcept;

  };
} // namespace arduino


#endif // MOTOR_HPP

