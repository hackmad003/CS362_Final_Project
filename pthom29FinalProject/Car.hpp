#ifndef CAR_HPP
#define CAR_HPP

// C/C++ includes
#include <cstddef>
#include <cstdint>
#include <array>

// 3rd party includes
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>

// Local includes
#include "DigitalPin.hpp"
#include "AnalogPin.hpp"
#include "ControlStick.hpp"

namespace arduino {

  class Car {
  private:
    /* -------------------------------------------------Fields-------------------------------------------------- */
    ControlStick controlStick;

    AnalogPin ENA, ENB;

    DigitalPin frontLeftWheel, frontRightWheel, backLeftWheel, backRightWheel;

  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    Car() noexcept;

    Car(Car&&) noexcept = default;

    Car(const Car&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~Car() noexcept = default;

    /* -------------------------------------------Overloaded Operators------------------------------------------ */
    Car& operator=(const Car&) noexcept = default;

    Car& operator=(Car&&) noexcept = default;

    /* -------------------------------------------------Setters------------------------------------------------- */

    /* -------------------------------------------------Getters------------------------------------------------- */

    /* -------------------------------------------------Methods------------------------------------------------- */
    void moveForward(void) noexcept;

    void moveBackward(void) noexcept;

    void moveLeft(void) noexcept;

    void moveRight(void) noexcept;

    void stop(void) noexcept;

  };

} // namespace arduino

#endif // CAR_HPP
