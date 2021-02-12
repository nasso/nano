/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

namespace nts {

InputComponent::InputComponent(nts::Tristate value)
{
    output(1);
    *this = value;
}

InputComponent& InputComponent::operator=(nts::Tristate value)
{
    m_value = value;
    return *this;
}

void InputComponent::_compute(PinSetter set)
{
    set(1, m_value);
}

}
