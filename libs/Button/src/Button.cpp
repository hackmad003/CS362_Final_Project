#include "Button.hpp"

namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  Button::Button(const Pin& pin) noexcept : pin(pin) { this->initialize(); }

  Button::Button(Pin&& pin) noexcept : pin(pin) { this->initialize(); }

  /* ----------------------------------------------Overloaded Operators------------------------------------------- */
  Button& Button::operator~(void) noexcept {
    this->pin.digitalWrite(static_cast<::PinStatus>(!this->pin.digitalRead()));
    return *this;
  }

  /* ----------------------------------------------------Setters-------------------------------------------------- */
  void Button::setPin(const Pin& pin) noexcept {
    this->pin = pin;
    this->pin.digitalWrite(PinStatus::LOW);
  }

  void Button::setPin(Pin&& pin) noexcept {
    this->pin = pin;
    this->pin.digitalWrite(PinStatus::LOW);
  }

  void Button::setDebounceTime(std::time_t debounceTime) noexcept { this->debounceTime = debounceTime; }

  /* ----------------------------------------------------Getters-------------------------------------------------- */
  [[nodiscard]] std::uint64_t Button::getCount() const noexcept { return this->count; }
  
  std::int32_t Button::getState(void) noexcept { return this->pin.digitalRead(); }

  /* -----------------------------------------------Methods (Private)--------------------------------------------- */
  void Button::initialize(void) noexcept {
    this->pin.digitalWrite(PinStatus::LOW);
    this->debounceTime = this->lastDebounceTime = this->count = 0;
    this->countMode = CountMode::COUNT_FALLING;
    PinMode pinMode = this->pin.getMode();

    if (pinMode != PinMode::INPUT_PULLUP && pinMode != PinMode::INPUT_PULLDOWN) {
      this->pin.setMode(PinMode::OUTPUT);
    }

    if (pinMode == PinMode::INPUT_PULLDOWN) {
      this->pressedState = HIGH;
      this->unpressedState = LOW;
    } else {
      this->pressedState = LOW;
      this->unpressedState = HIGH;
    }

    this->previousSteadyState = this->lastSteadyState = this->lastFlickerableState = this->pin.digitalRead();
  }

  /* ------------------------------------------------Methods (Public)--------------------------------------------- */
  [[nodiscard]] bool Button::isPressed(void) const noexcept {
    return this->previousSteadyState == this->unpressedState && this->lastSteadyState == this->pressedState;
  }

  [[nodiscard]] bool Button::isReleased(void) const noexcept {
    return this->previousSteadyState == this->pressedState && this->lastSteadyState == this->unpressedState;
  }

  void Button::resetCount(void) noexcept { this->count = 0; }

  void Button::loop(void) noexcept {
    // Read the state of the switch/button:
    std::int32_t currentState = this->pin.digitalRead();
    std::time_t currentTime = millis();

    // Check to see if the button was pressed
    // (i.e. the input went from LOW to HIGH), and it's been long enough
    // since the last press to ignore any noise:

    // If the button changed, due to noise or pressing:
    if (currentState != this->lastFlickerableState) {
      // Reset the debouncing timer
      this->lastDebounceTime = currentTime;

      // Save the the last flickerable state
      this->lastFlickerableState = currentState;
    }

    if ((currentTime - this->lastDebounceTime) >= this->debounceTime) {
      // Whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // Save the the steady state
      this->previousSteadyState = this->lastSteadyState;
      this->lastSteadyState = currentState;
    }

    if (this->previousSteadyState != this->lastSteadyState) {
      switch (this->countMode) {
        case CountMode::COUNT_BOTH: this->count++; break;

        case CountMode::COUNT_FALLING:
          if (this->previousSteadyState == HIGH && this->lastSteadyState == LOW)
            this->count++;
          break;

        case CountMode::COUNT_RISING:
          if (this->previousSteadyState == LOW && this->lastSteadyState == HIGH)
            this->count++;
          break;
      }
    }
  }

  void Button::onPress(std::function<void()> event) noexcept {
    if (this->isPressed()) {
      event();
    }
  }

  void Button::onRelease(std::function<void()> event) noexcept {
    if (this->isReleased()) {
      event();
    }
  }

} // namespace arduino

