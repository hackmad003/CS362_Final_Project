#ifndef PIN_HPP
#define PIN_HPP

#include <cstddef>
#include <cstdint>

#include <Arduino.h>


namespace arduino {
  class Pin {
  protected:
    /* -------------------------------------------------Fields-------------------------------------------------- */
    pin_size_t number;

    PinMode mode;

  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    explicit Pin(PinMode mode) noexcept;

    Pin(pin_size_t number, PinMode mode) noexcept;

    Pin(pin_size_t number, std::int32_t status, PinMode mode) noexcept;

    Pin(const Pin&) noexcept = default;

    Pin(Pin&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~Pin() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    Pin& operator=(const Pin&) noexcept = default;

    Pin& operator=(Pin&&) noexcept = default;

    [[nodiscard]] explicit operator bool(void) const noexcept;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    virtual void setNumber(pin_size_t number) noexcept = 0;

    void setMode(PinMode mode) noexcept;

    /* ------------------------------------------------Getters-------------------------------------------------- */
    [[nodiscard]] pin_size_t getNumber(void) const noexcept;

    [[nodiscard]] PinMode getMode(void) const noexcept;

    /* ------------------------------------------------Methods-------------------------------------------------- */
    [[nodiscard]] virtual std::int32_t read(void) const noexcept = 0;

    virtual void write(std::int32_t status) const noexcept = 0;

  };
} // arduino


#endif // PIN_HPP
