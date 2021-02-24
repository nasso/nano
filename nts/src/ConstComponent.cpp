/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ConstComponent
*/

#include "ConstComponent.hpp"

namespace nts {

ConstComponent::ConstComponent(nts::Tristate value)
    : m_value(value)
{
}

Pinout ConstComponent::pinout() const
{
    return Pinout({ { 1, PinUsage::OUTPUT } });
}

void ConstComponent::simulate(IPinoutBuffer& pinout)
{
    pinout.write(1, m_value);
}

void ConstComponent::display(std::ostream& os) const
{
    os << "const " << m_value;
}

}
