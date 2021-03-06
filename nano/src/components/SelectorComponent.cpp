/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** SelectorComponent
*/

#include "nts/components/SelectorComponent.hpp"

namespace nts {

const PinId PINS_ADDR[] = {11, 12, 13};
const PinId PINS_IN[] = { 1, 2, 3, 4, 5 , 6, 7, 9};
const PinId PIN_OUT = 14;
const PinId PIN_OUTPUT_ENABLE = 15;
const PinId PIN_INHIBIT = 10;

SelectorComponent::SelectorComponent()
{
    for (PinId pin : PINS_ADDR) {
        pinMode(pin, PinMode::INPUT);
    }
    for (PinId pin : PINS_IN) {
        pinMode(pin, PinMode::INPUT);
    }
    pinMode(PIN_OUT, PinMode::OUTPUT);
    pinMode(PIN_OUTPUT_ENABLE, PinMode::INPUT);
    pinMode(PIN_INHIBIT, PinMode::INPUT);
}

void SelectorComponent::tick()
{
    if (read(PIN_OUTPUT_ENABLE) == Tristate::UNDEFINED) {
        inputsClean();
        return;
    }
    if (read(PIN_OUTPUT_ENABLE) == Tristate::TRUE) {
            write(PIN_OUT, Tristate::UNDEFINED);
        inputsClean();
        return;
    }
    if (read(PIN_INHIBIT) == Tristate::UNDEFINED) {
        inputsClean();
        return;
    }

    if (read(PIN_INHIBIT) == Tristate::TRUE) {
        write(PIN_OUT, Tristate::FALSE);
        inputsClean();
        return;
    }
    std::size_t addr = 0;
    std::size_t bitIndex = 0;

    for (PinId pin : PINS_ADDR) {
        Tristate bit = read(pin);

        if (bit == Tristate::UNDEFINED) {
            inputsClean();
            return;
        }

        addr |= (bit == Tristate::TRUE) << bitIndex;
        bitIndex++;
    }
    write(PIN_OUT, read(PINS_IN[addr]));
    inputsClean();
}

void SelectorComponent::display(std::ostream& os) const
{
}

}
