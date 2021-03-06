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
    if (read(PIN_CLOCK) == Tristate::UNDEFINED
        || read(PIN_OUTPUT_ENABLE) == Tristate::UNDEFINED) {
        inputsClean();
        return;
    }

    if (read(PIN_CLOCK) == Tristate::TRUE) {
        if (read(PIN_OUTPUT_ENABLE) == Tristate::FALSE) {
            write(PIN_LAST_STAGE, read(PINS_OUT[6]));
            for (PinId pin : PINS_OUT) {
                write(pin, Tristate::UNDEFINED);
            }
            inputsClean();
            return;
        }
        if (read(PIN_STROBE) == Tristate::UNDEFINED) {
            for (PinId pin : PINS_OUT) {
                write(pin, Tristate::UNDEFINED);
            }
            inputsClean();
            return;
        }
        if (read(PIN_STROBE) == Tristate::FALSE) {
            write(PIN_LAST_STAGE, read(PINS_OUT[6]));
            inputsClean();
            return;
        }
        if (read(PIN_DATA) == Tristate::UNDEFINED) {
            inputsClean();
            return;
        }
        size_t index = 7;
        while (index > 0) {
            write(PINS_OUT[index], read(PINS_OUT[index - 1]));
            index--;
        }
        write(PINS_OUT[0], read(PIN_DATA));
        write(PIN_LAST_STAGE, read(PINS_OUT[6]));
    } else if (read(PIN_CLOCK) == Tristate::FALSE) {
        if (read(PIN_OUTPUT_ENABLE) == Tristate::FALSE) {
            write(PIN_LAST_STAGE_PRIME, read(PINS_OUT[6]));
            for (PinId pin : PINS_OUT) {
                write(pin, Tristate::UNDEFINED);
            }
            inputsClean();
            return;
        }
        if (read(PIN_STROBE) == Tristate::TRUE
        && read(PIN_DATA) == Tristate::TRUE) {
            write(PIN_LAST_STAGE_PRIME, read(PINS_OUT[6]));
        }
    }
    inputsClean();
}

void ShiftRegisterComponent::display(std::ostream& os) const
{
}

}
