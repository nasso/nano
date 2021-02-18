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

    if (a == Tristate::FALSE || b == Tristate::FALSE) {
        set(3, Tristate::FALSE);
    } else if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED) {
        set(3, Tristate::UNDEFINED);
    } else {
        set(3, Tristate::TRUE);
    }
}

}
