/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NotGate
*/

#include "NotGate.hpp"
#include <iostream>

namespace nts {

Pinout NotGate::pinout() const
{
    return Pinout({
        { 1, PinFlags::INPUT },
        { 2, PinFlags::OUTPUT },
    });
}

void NotGate::simulate(IPinoutBuffer& pinout)
{
    pinout.write(2, !pinout.read(1));
}

void NotGate::display(std::ostream& os) const
{
    os << "not";
}

}
