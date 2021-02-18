/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Tristate
*/

#include "IComponent.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const nts::Tristate& state)
{
    switch (state) {
    case nts::Tristate::UNDEFINED:
        return os << 'U';
    case nts::Tristate::TRUE:
        return os << '1';
    case nts::Tristate::FALSE:
        return os << '0';
    }
    return os;
}
