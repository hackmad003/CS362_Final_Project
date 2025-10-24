#ifndef CONTROL_STICK_HPP
#define CONTROL_STICK_HPP

#include <cstddef>
#include <cstdint>

#include "DigitalPin.hpp"
#include "AnalogPin.hpp"


namespace arduino {
  class ControlStick {
  private:
    /* -------------------------------------------------Fields----------------------------------------------- */
    AnalogPin vrxPin;
    AnalogPin vryPin;
    DigitalPin swPin;

  public:
    /* ----------------------------------------------Constructors-------------------------------------------- */
    ControlStick(void) noexcept;

    ControlStick(const AnalogPin& vrxPin, const AnalogPin& vryPin, const DigitalPin& swPin) noexcept;
    ControlStick(AnalogPin&& vrxPin, AnalogPin&& vryPin, DigitalPin&& swPin) noexcept;

    ControlStick(const ControlStick&) noexcept = default;

    ConstrolStick(ControlStick&&) noexcept = default;

    /* -----------------------------------------------Destructor--------------------------------------------- */
    ~ControlStick() noexcept = default;

    /* -------------------------------------------Overloaded Operators--------------------------------------- */
    ControlStick& operator=(const ControlStick&) noexcept = default;

    ControlStick& operator=(ControlStick&&) noexcept = default;

    [[nodiscard]] explicit operator bool(void) const noexcept;

    /* ------------------------------------------------Setters----------------------------------------------- */
    void setVrxPin(const AnalogPin& vrxPin) noexcept;

    void setVrxPin(AnalogPin&& vrxPin) noexcept;

    void setVryPin(const AnalogPin& vryPin) noexcept;

    void setVryPin(AnalogPin&& vryPin) noexcept;

    void setSwPin(const DigitalPin& swPin) noexcept;
    void setSwPim(DigitalPin&& swPin) noexcept;
    
    /* ------------------------------------------------Getters----------------------------------------------- */
    [[nodiscard]] std::int32_t getXCoord(void) const noexcept;

    [[nodiscard]] std::int32_t getYCoord(void) const noexcept;

    /* ------------------------------------------------Methods----------------------------------------------- */
    [[nodiscard]] bool isPressed(void) const noexcept;


  };

} // namespace arduino

#endif // CONTROL_STICK_HPP
