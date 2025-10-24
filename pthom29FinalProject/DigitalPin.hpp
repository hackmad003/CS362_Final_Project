#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

#include "Pin.hpp"


namespace arduino {
  
  class DigitalPin : public Pin {
  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    DigitalPin(pin_size_t number, PinMode mode) noexcept;

    DigitalPin(pin_size_t number, PinStatus status, PinMode mode) noexcept;

    DigitalPin(const DigitalPin&) noexcept = default;

    DigitalPin(DigitalPin&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~DigitalPin() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    DigitalPin& operator=(const DigitalPin&) noexcept = default;

    DigitalPin& operator=(DigitalPin&&) noexcept = default;

    [[nodiscard]] bool operator==(const DigitalPin& rhs) const noexcept;

    [[nodiscard]] bool operator==(DigitalPin&& rhs) const noexcept;

    [[nodiscard]] bool operator!=(const DigitalPin& rhs) const noexcept;

    [[nodiscard]] bool operator!=(DigitalPin&& rhs) const noexcept;

    [[nodiscard]] explicit operator bool(void) const noexcept;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    void setNumber(pin_size_t number) noexcept override;

    /* ------------------------------------------------Methods-------------------------------------------------- */
    [[nodiscard]] std::int32_t read(void) const noexcept override;

    void write(std::int32_t status) const noexcept override;

  };

} // namespace arduino


#endif // DIGITAL_PIN_HPP
