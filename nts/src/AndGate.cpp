/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AndGate
*/

#include "AndGate.hpp"

namespace nts {

void AndGate::_compute(std::size_t)
{
    auto a = compute(1);
    auto b = compute(2);

    if (a == UNDEFINED || b == UNDEFINED) {
        set(3, UNDEFINED);
    } else {
        set(3, a == TRUE && b == TRUE ? TRUE : FALSE);
    }
}

}
