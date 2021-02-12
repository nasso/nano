/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NotGate
*/

#include "NotGate.hpp"

namespace nts {

NotGate::NotGate()
{
    input(1);
    output(2);
}

void NotGate::_compute(PinSetter set)
{
    auto in = compute(1);

    switch (in) {
    case UNDEFINED:
        set(2, UNDEFINED);
        break;
    case TRUE:
        set(2, FALSE);
        break;
    case FALSE:
        set(2, TRUE);
        break;
    }
}

}
