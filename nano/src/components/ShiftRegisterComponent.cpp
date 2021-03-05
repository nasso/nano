/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ShiftRegisterComponent
*/

#include "nts/components/ShiftRegisterComponent.hpp"

namespace nts {

const PinId PINS_OUT[] = { 4, 5, 6, 7, 14, 13, 12, 11 };
const PinId PIN_STROBE = 1;
const PinId PIN_DATA = 2;
const PinId PIN_CLOCK = 3;
const PinId PIN_OUTPUT_ENABLE = 15;
const PinId PIN_LAST_STAGE = 10;
const PinId PIN_LAST_STAGE_PRIME = 9;

ShiftRegisterComponent::ShiftRegisterComponent()
{
    for (PinId pin : PINS_OUT) {
        pinMode(pin, PinMode::OUTPUT);
    }

    pinMode(PIN_STROBE, PinMode::INPUT);
    pinMode(PIN_DATA, PinMode::INPUT);
    pinMode(PIN_CLOCK, PinMode::INPUT);
    pinMode(PIN_OUTPUT_ENABLE, PinMode::INPUT);
    pinMode(PIN_LAST_STAGE, PinMode::OUTPUT);
    pinMode(PIN_LAST_STAGE_PRIME, PinMode::OUTPUT);
}

void ShiftRegisterComponent::tick()
{
    for (PinId pin : PINS_OUT) {
        write(pin, Tristate::UNDEFINED);
    }

    if (read(PIN_INHIB) == Tristate::UNDEFINED) {
        inputsClean();
        return;
    }

    if (read(PIN_INHIB) == Tristate::TRUE) {
        for (PinId pin : PINS_OUT) {
            write(pin, Tristate::FALSE);
        }
        inputsClean();
        return;
    }

    short value = 0;
    std::size_t bitIndex = 0;

    for (PinId pin : PINS_ADDR) {
        Tristate bit = read(pin);

        if (bit == Tristate::UNDEFINED) {
            inputsClean();
            return;
        }

        value |= (bit == Tristate::TRUE) << bitIndex;
        bitIndex++;
    }
    for (PinId pin : PINS_OUT) {
        write(pin, Tristate::FALSE);
    }
    write(PINS_OUT[value], Tristate::TRUE);
    inputsClean();
}

void ShiftRegisterComponent::display(std::ostream& os) const
{

}

}
