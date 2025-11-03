#include "ControlStick.hpp"


namespace arduino {
  /* --------------------------------------------------Constructors----------------------------------------------- */
  ControlStick::Coords::Coords() noexcept : x(ControlStick::DEFAULT_COORD), y(ControlStick::DEFAULT_COORD) {}

  ControlStick::ControlStick() noexcept : radio(RF24(6, 7)) {
    this->radio.begin();
    this->radio.openReadingPipe(1, ControlStick::PIPE_IN);
    this->radio.setPALevel(RF24_PA_LOW);
    this->radio.startListening();
  }

  /* ----------------------------------------------------Methods-------------------------------------------------- */
  void ControlStick::_updateCoords(void) noexcept {
    if (this->radio.available()) {
      this->radio.read(&this->coords, sizeof(ControlStick::Coords));

      // Check if we're receiving valid joystick coords (not 0,0 garbage)
      if (this->coords.x > ControlStick::MIN_COORD && this->coords.x < ControlStick::MAX_COORD && 
          this->coords.y > ControlStick::MIN_COORD && this->coords.y < ControlStick::MAX_COORD) {
        // Do nothing if the updated coords are valid
        return;
      }

      // Reset the coordinates to their default values if they are invalid
      this->coords = Coords();
    }
  }

  std::int32_t ControlStick::x(void) noexcept {
    this->_updateCoords();
    return this->coords.x;
  }

  std::int32_t ControlStick::y(void) noexcept {
    this->_updateCoords();
    return this->coords.y;
  }

} // namespace arduino
