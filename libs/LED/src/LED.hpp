#ifndef LED_HPP
#define LED_HPP

#include <cstddef>
#include <cstdint>

#include <Arduino.h>

#include "Pin.hpp"

namespace arduino {
  class LED {
  private:
    /* -------------------------------------------Setters (Private)--------------------------------------------- */
    void setModeToOutput(void) noexcept;

    /* -------------------------------------------Fields (Private)---------------------------------------------- */
    Pin pin;

    std::uint16_t lastValue, currentValue;

  public:
    /* -------------------------------------------------Colors-------------------------------------------------- */
    enum class Color { WHITE, YELLOW, GREEN, BLUE, RED };

    /* ---------------------------------------------Fields (Public)--------------------------------------------- */
    Color color;

    /* ----------------------------------------------Constructors----------------------------------------------- */
    explicit LED(const Pin& pin) noexcept;

    explicit LED(Pin&& pin) noexcept;

    LED(const Pin& pin, Color color) noexcept;

    LED(Pin&& pin, Color color) noexcept;

    LED(const LED&) noexcept = default;

    LED(LED&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~LED() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    LED& operator=(const LED&) noexcept = default;

    LED& operator=(LED&&) noexcept = default;

    LED& operator~(void) noexcept;

    [[nodiscard]] explicit operator bool(void) const noexcept;

    /* --------------------------------------------Setters (Public)--------------------------------------------- */
    void setPin(const Pin& pin) noexcept;

    void setPin(Pin&& pin) noexcept;

    /* ------------------------------------------------Getters-------------------------------------------------- */
    [[nodiscard]] Pin getPin(void) const noexcept;

    [[nodiscard]] std::int32_t getBrightness(void) const noexcept;

    /* ------------------------------------------------Methods-------------------------------------------------- */
    [[nodiscard]] bool isOn(void) const noexcept;

    [[nodiscard]] bool isOff(void) const noexcept;

    void turnOn(void) noexcept;

    void turnOff(void) noexcept;

    void setBrightness(std::int32_t brightness) noexcept;

  };
} // arduino


#endif // LED_HPP

