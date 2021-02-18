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
    case Tristate::UNDEFINED:
        set(2, Tristate::UNDEFINED);
        break;
    case Tristate::TRUE:
        set(2, Tristate::FALSE);
        break;
    case Tristate::FALSE:
        set(2, Tristate::TRUE);
        break;
    }
}

}
