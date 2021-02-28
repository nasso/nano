/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Tristate
*/

#include "nts/Tristate.hpp"
#include <iostream>

nts::Tristate operator&&(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::Tristate::FALSE || b == nts::Tristate::FALSE) {
        return nts::Tristate::FALSE;
    } else if (a == nts::Tristate::UNDEFINED || b == nts::Tristate::UNDEFINED) {
        return nts::Tristate::UNDEFINED;
    } else {
        return nts::Tristate::TRUE;
    }
}

nts::Tristate operator||(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::Tristate::TRUE || b == nts::Tristate::TRUE) {
        return nts::Tristate::TRUE;
    } else if (a == nts::Tristate::UNDEFINED || b == nts::Tristate::UNDEFINED) {
        return nts::Tristate::UNDEFINED;
    } else {
        return nts::Tristate::FALSE;
    }
}

nts::Tristate operator!(nts::Tristate a)
{
    switch (a) {
    case nts::Tristate::FALSE:
        return nts::Tristate::TRUE;
    case nts::Tristate::TRUE:
        return nts::Tristate::FALSE;
    default:
        return nts::Tristate::UNDEFINED;
    }
}

std::ostream& operator<<(std::ostream& os, const nts::Tristate& state)
{
    if (state == nts::Tristate::FALSE) {
        return os << '0';
    } else if (state == nts::Tristate::TRUE) {
        return os << '1';
    } else {
        return os << 'U';
    }
}
