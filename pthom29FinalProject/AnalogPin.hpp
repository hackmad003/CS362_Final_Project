#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

#include "Pin.hpp"


namespace arduino {

  class AnalogPin : public Pin {
  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    AnalogPin(pin_size_t number, PinMode mode) noexcept;

    AnalogPin(pin_size_t number, std::int32_t status, PinMode mode) noexcept;

    AnalogPin(const AnalogPin&) noexcept = default;

    AnalogPin(AnalogPin&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~AnalogPin() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    AnalogPin& operator=(const AnalogPin&) noexcept = default;

    AnalogPin& operator=(AnalogPin&&) noexcept = default;

    [[nodiscard]] bool operator==(const AnalogPin& rhs) const noexcept;

    [[nodiscard]] bool operator==(AnalogPin&& rhs) const noexcept;

    [[nodiscard]] bool operator!=(const AnalogPin& rhs) const noexcept;

    [[nodiscard]] bool operator!=(AnalogPin&& rhs) const noexcept;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    void setNumber(pin_size_t number) noexcept override;

    /* ------------------------------------------------Methods-------------------------------------------------- */
    [[nodiscard]] std::int32_t read(void) const noexcept override;

    void write(std::int32_t status) const noexcept override;

  };

} // namespace arduino


#endif // ANALOG_PIN_HPP
