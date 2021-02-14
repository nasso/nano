/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** LoggerComponent
*/

#include "LoggerComponent.hpp"

namespace nts {
LoggerComponent::LoggerComponent(std::ostream& output_s)
    : m_output(output_s)
{
    for (int i = 1; i <= 10; i++)
        input(i);
}

void LoggerComponent::_compute(PinSetter)
{
    char val = 0;
    Tristate tmp = UNDEFINED;

    if (compute(9) != TRUE || compute(10) != FALSE)
        return;
    for (int i = 8; i > 0; i--) {
        tmp = compute(i);
        if (tmp == UNDEFINED)
            return;
        val = (val << 1) + tmp;
    }
    std::cout << ((int)val) << std::endl;
    m_output << val;
}
}
