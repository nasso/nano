/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NorGate
*/

#include "NorGate.hpp"
#include <iostream>

namespace nts {

NorGate::NorGate()
{
    input(1);
    input(2);
    output(3);
}

void NorGate::_compute(PinSetter set)
{
    auto a = compute(1);
    auto b = compute(2);

    if (a == UNDEFINED || b == UNDEFINED) {
        set(3, UNDEFINED);
    }

    set(3, (a == TRUE) || (b == TRUE) ? FALSE : TRUE);
}

}
