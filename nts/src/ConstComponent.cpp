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
    output(1);
    simulate(1);
}

void ConstComponent::_compute(PinSetter set)
{
    set(1, m_value);
}

}
