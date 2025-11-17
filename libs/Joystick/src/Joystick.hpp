#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <cstddef>
#include <cstdint>

#include <Arduino.h>

#include "Pin.hpp"

namespace arduino {
  class Joystick {
  private:
    /* -------------------------------------------------Fields-------------------------------------------------- */
    Pin xPin, yPin;

  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    Joystick(const Pin& xPin, const Pin& yPin) noexcept;

    Joystick(Pin&& xPin, Pin&& yPin) noexcept;

    Joystick(const Joystick&) noexcept = default;

    Joystick(Joystick&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~Joystick() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    Joystick& operator=(const Joystick&) noexcept = default;

    Joystick& operator=(Joystick&&) noexcept = default;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    void setXPin(const Pin& xPin) noexcept;

    void setXPin(Pin&& xPin) noexcept;

    void setYPin(const Pin& yPin) noexcept;

    void setYPin(Pin&& yPin) noexcept;

    /* ------------------------------------------------Getters-------------------------------------------------- */
    [[nodiscard]] std::int32_t getX(void) const noexcept;
    
    [[nodiscard]] std::int32_t getY(void) const noexcept;

  };
} // namespace arduino


#endif // JOYSTICK_HPP

