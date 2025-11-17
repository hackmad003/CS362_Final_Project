#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <functional>

#include <Arduino.h>

#include "Pin.hpp"

namespace arduino {
  class Button {
  private:
    /* --------------------------------------------Fields (Private)--------------------------------------------- */
    Pin pin;

    std::time_t debounceTime, lastDebounceTime;

    std::uint64_t count;

    std::int32_t pressedState, unpressedState, lastSteadyState, lastFlickerableState, previousSteadyState;

    /* --------------------------------------------Methods (Private)-------------------------------------------- */
    void initialize(void) noexcept;

  public:
    /* -----------------------------------------------Count Mode------------------------------------------------ */
    enum class CountMode { COUNT_FALLING, COUNT_RISING, COUNT_BOTH };

    /* ---------------------------------------------Fields (Public)--------------------------------------------- */
    CountMode countMode;

    /* ----------------------------------------------Constructors----------------------------------------------- */
    explicit Button(const Pin& pin) noexcept;

    explicit Button(Pin&& pin) noexcept;

    Button(const Button&) noexcept = default;

    Button(Button&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~Button() noexcept = default;

    /* ------------------------------------------Overloaded Operators------------------------------------------- */
    Button& operator=(const Button&) noexcept = default;

    Button& operator=(Button&&) noexcept = default;

    Button& operator~(void) noexcept;

    [[nodiscard]] explicit operator bool(void) const noexcept;

    /* ------------------------------------------------Setters-------------------------------------------------- */
    void setPin(const Pin& pin) noexcept;

    void setPin(Pin&& pin) noexcept;

    void setDebounceTime(std::time_t debounceTime) noexcept;

    /* ------------------------------------------------Getters-------------------------------------------------- */
    [[nodiscard]] std::uint64_t getCount(void) const noexcept;

    std::int32_t getState(void) noexcept;

    /* ------------------------------------------------Methods-------------------------------------------------- */
    [[nodiscard]] bool isPressed(void) const noexcept;

    [[nodiscard]] bool isReleased(void) const noexcept;

    void resetCount(void) noexcept;

    void loop(void) noexcept;

    void onPress(std::function<void()> event) noexcept;

    void onRelease(std::function<void()> event) noexcept;

  };
} // namespace arduino


#endif // BUTTON_HPP

