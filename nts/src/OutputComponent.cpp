/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"

namespace nts {

OutputComponent::OutputComponent()
{
    input(1);
}

OutputComponent::operator nts::Tristate() const
{
    return read();
}

void OutputComponent::_compute(PinSetter)
{
    m_value = compute(1);
}

nts::Tristate OutputComponent::read() const
{
    return m_value;
}

}
