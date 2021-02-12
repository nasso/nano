/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AndGate
*/

#include "AndGate.hpp"

namespace nts {

AndGate::AndGate()
{
    input(1);
    input(2);
    output(3);
}

void AndGate::_compute(PinSetter set)
{
    auto a = compute(1);
    auto b = compute(2);

    if (a == FALSE || b == FALSE) {
        set(3, FALSE);
    } else if (a == UNDEFINED || b == UNDEFINED) {
        set(3, UNDEFINED);
    } else {
        set(3, TRUE);
    }
}

}
