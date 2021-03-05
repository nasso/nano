/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** DecoderComponent
*/

#include "nts/components/DecoderComponent.hpp"

namespace nts {

const PinId PINS_ADDR[] = { 21, 22, 3, 2 };
const PinId PINS_OUT[] = { 11, 10, 9, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15 };
const PinId PIN_INHIB = 23;

DecoderComponent::DecoderComponent()
{
    for (PinId pin : PINS_ADDR) {
        pinMode(pin, PinMode::INPUT);
    }

    for (PinId pin : PINS_OUT) {
        pinMode(pin, PinMode::OUTPUT);
    }

    pinMode(PIN_INHIB, PinMode::INPUT);
}

void DecoderComponent::tick()
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

void DecoderComponent::display(std::ostream& os) const
{

}

}
