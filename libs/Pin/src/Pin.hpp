#ifndef PIN_HPP
#define PIN_HPP

#include <cstddef>
#include <cstdint>

#include <Arduino.h>

namespace arduino {
  class Pin {
  private:
    /* -------------------------------------------------Fields-------------------------------------------------- */
    pin_size_t number;

    PinMode mode;

  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    Pin(pin_size_t number, PinMode mode) noexcept;

    Pin(pin_size_t number, PinMode mode, std::int32_t status) noexcept;

    Pin(const Pin&) noexcept = default;

    Pin(Pin&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~Pin() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    Pin& operator=(const Pin&) noexcept = default;

    Pin& operator=(Pin&&) noexcept = default;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    void setNumber(pin_size_t number) noexcept;

    void setMode(PinMode mode) noexcept;

    /* ------------------------------------------------Getters-------------------------------------------------- */
    [[nodiscard]] pin_size_t getNumber(void) const noexcept;

    [[nodiscard]] PinMode getMode(void) const noexcept;

    /* ------------------------------------------------Methods-------------------------------------------------- */
    [[nodiscard]] PinStatus digitalRead(void) const noexcept;

    [[nodiscard]] std::int32_t analogRead(void) const noexcept;

    void digitalWrite(PinStatus status) const noexcept;

    void analogWrite(std::int32_t status) const noexcept;

  };
} // arduino


#endif // PIN_HPP

