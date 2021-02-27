/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** LoggerComponent
*/

#include "nts/LoggerComponent.hpp"

namespace nts {

const PinId PIN_DATA[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
const PinId PIN_CLOCK = 9;
const PinId PIN_INHIBIT = 10;

LoggerComponent::LoggerComponent(std::ostream& out)
    : m_output(out)
{
    for (PinId pin : PIN_DATA) {
        pinMode(pin, INPUT);
    }

    pinMode(PIN_CLOCK, INPUT);
    pinMode(PIN_INHIBIT, INPUT);
}

void LoggerComponent::simulate()
{
    auto clock = read(PIN_CLOCK);
    auto inhibit = read(PIN_INHIBIT);

    if (clock == Tristate::FALSE) {
        m_rising = true;
    }

    if (clock == Tristate::TRUE && inhibit == Tristate::FALSE && m_rising) {
        m_rising = false;

        std::uint8_t val = 0;
        std::size_t bitIndex = 0;

        for (PinId pin : PIN_DATA) {
            Tristate bit = read(pin);

            if (bit == Tristate::UNDEFINED) {
                return;
            }

            val |= (bit == Tristate::TRUE) << bitIndex;

            bitIndex++;
        }

        m_output << val;
    }
}

void LoggerComponent::display(std::ostream& os) const
{
    os << "(logger)";
}

}
