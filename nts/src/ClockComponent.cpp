/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#include "nts/ClockComponent.hpp"

namespace nts {

ClockComponent::ClockComponent(nts::Tristate init)
{
    *this = init;
    pinMode(1, PinMode::OUTPUT);
}

ClockComponent& ClockComponent::operator=(nts::Tristate value)
{
    m_value = value;
    return *this;
}

void ClockComponent::simulate()
{
    write(1, m_value);
    m_value = !m_value;
}

void ClockComponent::display(std::ostream& out) const
{
    out << "(clock " << m_value << ")";
}

}
