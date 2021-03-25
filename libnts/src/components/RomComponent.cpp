/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** RomComponent
*/

#include "nts/components/RomComponent.hpp"

namespace nts {

const PinId PINS_ADDR[] = { 8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19 };
const PinId PINS_OUT[] = { 9, 10, 11, 13, 14, 15, 16, 17 };
const PinId PIN_ENABLE_N = 18;
const PinId PIN_READ_N = 20;

RomComponent::RomComponent(std::size_t size)
    : m_data(size)
{
}

RomComponent::RomComponent(std::vector<std::uint8_t> data)
    : m_data(data)
{
    for (PinId pin : PINS_ADDR) {
        pinMode(pin, PinMode::INPUT);
    }

    for (PinId pin : PINS_OUT) {
        pinMode(pin, PinMode::OUTPUT);
    }

    pinMode(PIN_ENABLE_N, PinMode::INPUT);
    pinMode(PIN_READ_N, PinMode::INPUT);
}

void RomComponent::tick()
{
    for (PinId pin : PINS_OUT) {
        write(pin, Tristate::UNDEFINED);
    }

    if (read(PIN_ENABLE_N) != Tristate::FALSE
        || read(PIN_READ_N) != Tristate::FALSE) {
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

    if (addr < m_data.size()) {
        std::uint8_t val = m_data[addr];

        for (PinId pin : PINS_OUT) {
            write(pin, val & 1 ? Tristate::TRUE : Tristate::FALSE);
            val >>= 1;
        }
    }
    inputsClean();
}

void RomComponent::display(std::ostream& os) const
{
    os << "(rom of " << m_data.size() << " bytes)";
}

}
