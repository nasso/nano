/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** AComponent
*/

#include "nts/AComponent.hpp"

namespace nts {

AComponent::AComponent()
{
}

AComponent::AComponent(Pinout pinout)
{
    for (auto& pin : pinout) {
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
    return m_pins.at(pin);
}

void AComponent::write(PinId pin, Tristate value)
{
    m_pins.at(pin) = value;
}

void AComponent::display(std::ostream& os) const
{
    os << "(a component)";
}

}
