#ifndef LED_HPP
#define LED_HPP

#include "DigitalPin.hpp"


namespace arduino {

  class LED : public DigitalPin {
  public:
    /* ----------------------------------------------Constructors----------------------------------------------- */
    explicit LED(pin_size_t pinNumber) noexcept;

    LED(pin_size_t pinNumber, bool status) noexcept;

    LED(const LED&) noexcept = default;

    LED(LED&&) noexcept = default;

    /* -----------------------------------------------Destructor------------------------------------------------ */
    ~LED() noexcept = default;

    /* ------------------------------------------------Methods-------------------------------------------------- */
    bool isOn(void) noexcept;

    bool isOff(void) noexcept;

    void turnOn(void) noexcept;

    void turnOff(void) noexcept;

    void flip(void) noexcept;
    
  };

} // namespace arduino

#endif // LED_HPP
