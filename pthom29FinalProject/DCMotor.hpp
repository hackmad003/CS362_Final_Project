#ifndef DC_MOTOR_HPP
#define DC_MOTOR_HPP

#include <cstddef>
#include <cstdint>

#include "AnalogPin.hpp"


namespace arduino {
	class DCMotor {
	private:
		AnalogPin speedPin;

    

	public:
		/* ----------------------------------------------Constructors----------------------------------------------- */
		DCMotor(const AnalogPin& speedPin) noexcept;

		DCMotor(AnalogPin&& speedPin) noexcept;

		DCMotor(const DCMotor&) noexcept = default;

		DCMotor(DCMotor&&) noexcept = default;

		/* -----------------------------------------------Destructor------------------------------------------------ */
		~DCMotor() noexcept = default;

		/* ------------------------------------------Overloaded Operators------------------------------------------- */
		DCMotor& operator=(const DCMotor&) noexcept = default;

		DCMotor& operator=(DCMotor&&) noexcept = default;

		/* ------------------------------------------------Setters-------------------------------------------------- */
		void setSpeedPin(const AnalogPin& speedPin) noexcept;

		void setSpeedPin(AnalogPin&& speedPin) noexcept;

    void setSpeedPin(pin_size_t pinNumber) noexcept;

    void setSpeedPin(pin_size_t pinNumber, std::uint8_t speed);

		void setSpeed(std::uint8_t speed) noexcept;

		/* ------------------------------------------------Getters-------------------------------------------------- */
		[[nodiscard]] std::uint8_t getSpeed(void) const noexcept;

	};

} // namespace arduino

#endif // DC_MOTOR_HPP

