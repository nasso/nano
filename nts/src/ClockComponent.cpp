/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

namespace nts {

ClockComponent::ClockComponent()
{
    output(1);
}

ClockComponent& ClockComponent::operator=(nts::Tristate value)
{
    m_value = value;
    return *this;
}

void ClockComponent::_compute(PinSetter set)
{
    set(1, m_value);
    if (m_value != Tristate::UNDEFINED) {
        m_value = m_value == Tristate::TRUE ? Tristate::FALSE : Tristate::TRUE;
    }
}

}
