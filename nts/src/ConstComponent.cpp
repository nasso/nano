/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ConstComponent
*/

#include "nts/ConstComponent.hpp"
#include <string>

namespace nts {

const Pinout CONST_PINOUT { { 1, OUTPUT } };

ConstComponent::ConstComponent(nts::Tristate value)
    : m_value(value)
{
}

void ConstComponent::simulate()
{
    // *sleeps*
}

const Pinout& ConstComponent::pinout() const
{
    return CONST_PINOUT;
}

Tristate ConstComponent::read(PinId pin) const
{
    if (pin != 1) {
        throw std::out_of_range(std::to_string(pin) + " isn't a valid pin");
    }

    return m_value;
}

void ConstComponent::write(PinId pin, Tristate)
{
    if (pin != 1) {
        throw std::out_of_range(std::to_string(pin) + " isn't a valid pin");
    }

    // I. DON'T. CARE!!
}

void ConstComponent::display(std::ostream& os) const
{
    os << "(const " << m_value << ")";
}

}
