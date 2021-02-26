/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ConstComponent
*/

#include "nts/ConstComponent.hpp"

namespace nts {

ConstComponent::ConstComponent(nts::Tristate value)
    : m_value(value)
{
    pinMode(1, OUTPUT);
}

void ConstComponent::simulate()
{
    write(1, m_value);
}

}
