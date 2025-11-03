#ifndef CONTROL_STICK_HPP
#define CONTROL_STICK_HPP

#include <cstddef>
#include <cstdint>

#include <Arduino.h>
#include <RF24.h>

namespace arduino {
  class ControlStick {
  private:
    /* -------------------------------------------------Coords----------------------------------------------- */
    struct Coords {
      /* -----------------------------------------------Fields----------------------------------------------- */
      std::int32_t x, y;

      /* --------------------------------------------Constructors-------------------------------------------- */
      Coords(void) noexcept;

      Coords(const Coords&) noexcept = default;

      Coords(Coords&&) noexcept = default;

      /* ---------------------------------------------Destructor--------------------------------------------- */
      ~Coords() noexcept = default;

      /* -----------------------------------------Overloaded Operators--------------------------------------- */
      Coords& operator=(const Coords&) noexcept = default;

      Coords& operator=(Coords&&) noexcept = default;

    };

    /* -------------------------------------------------Fields----------------------------------------------- */
    static constexpr std::int32_t DEFAULT_COORD = 512, MIN_COORD = 50, MAX_COORD = 1000;

    static constexpr std::uint64_t PIPE_IN = 0xE9E8F0F0E1LL;

    RF24 radio;

    Coords coords;

    /* ------------------------------------------------Methods----------------------------------------------- */
    void _updateCoords(void) noexcept;

  public:
    /* ----------------------------------------------Constructors-------------------------------------------- */
    ControlStick() noexcept;
    
    ControlStick(const ControlStick&) noexcept = default;

    ControlStick(ControlStick&&) noexcept = default;

    /* -----------------------------------------------Destructor--------------------------------------------- */
    ~ControlStick() noexcept = default;

    /* -------------------------------------------Overloaded Operators--------------------------------------- */
    ControlStick& operator=(const ControlStick& rhs) noexcept = default;

    ControlStick& operator=(ControlStick&& rhs) noexcept = default;

    /* ------------------------------------------------Methods----------------------------------------------- */
    std::int32_t x(void) noexcept;

    std::int32_t y(void) noexcept;

  };

} // namespace arduino

#endif // CONTROL_STICK_HPP
