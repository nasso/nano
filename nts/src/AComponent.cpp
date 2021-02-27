/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** AComponent
*/

#include "nts/AComponent.hpp"
#include <string>

namespace nts {

AComponent::AComponent()
{
}

AComponent::AComponent(Pinout pinout)
{
    for (const auto& pin : pinout) {
        pinMode(pin.first, pin.second);
    }
}

void AComponent::pinMode(PinId pin, PinMode flags)
{
    if (flags == NONE) {
        m_pinout.erase(pin);
        m_pins.erase(pin);
    } else {
        m_pinout[pin] = flags;
        m_pins[pin];
    }
}

const Pinout& AComponent::pinout() const
{
    return m_pinout;
}

Tristate AComponent::read(PinId pin) const
{
    try {
        return m_pins.at(pin);
    } catch (...) {
        throw std::out_of_range("No such pin: " + std::to_string(pin));
    }
}

void AComponent::write(PinId pin, Tristate value)
{
    try {
        m_pins.at(pin) = value;
    } catch (...) {
        throw std::out_of_range("No such pin: " + std::to_string(pin));
    }
}

}
