/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

namespace nts {

ClockComponent::ClockComponent(nts::Tristate init)
{
    *this = init;
}

ClockComponent& ClockComponent::operator=(nts::Tristate value)
{
    m_value = value;
    return *this;
}

Pinout ClockComponent::pinout() const
{
    return Pinout({ { 1, PinFlags::OUTPUT } });
}

void ClockComponent::simulate(IPinoutBuffer& buf)
{
    buf.write(1, m_value);
    m_value = !m_value;
}

void ClockComponent::display(std::ostream& os) const
{
    os << "clock " << m_value;
}

}
