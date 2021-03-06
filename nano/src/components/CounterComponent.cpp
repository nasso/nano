/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** CounterComponent
*/

#include "nts/components/CounterComponent.hpp"

namespace nts {

const PinId PINS_OUT[] = { 9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1 };
const PinId PIN_RESET = 2;
const PinId PIN_CLOCK = 3;

CounterComponent::CounterComponent()
{
    for (PinId pin : PINS_OUT) {
        pinMode(pin, PinMode::OUTPUT);
    }

    pinMode(PIN_RESET, PinMode::INPUT);
    pinMode(PIN_CLOCK, PinMode::INPUT);
    m_value = 0;
}

void CounterComponent::tick()
{
    if (read(PIN_RESET) == Tristate::TRUE) {
        for (PinId pin : PINS_OUT) {
            write(pin, Tristate::FALSE);
        }
        inputsClean();
        return;
    }
    if (read(PIN_CLOCK) == Tristate::UNDEFINED) {
        inputsClean();
        return;
    }

    if (read(PIN_CLOCK) == Tristate::FALSE) {
        m_value += 1;
        size_t bitIndex = 0;

        for (PinId pin : PINS_OUT) {
            write(pin,
                (m_value >> bitIndex) & 1 ? Tristate::TRUE : Tristate::FALSE);
            bitIndex++;
        }
    }
    inputsClean();
}

void CounterComponent::display(std::ostream& os) const
{
}

}
