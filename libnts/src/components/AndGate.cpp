/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AndGate
*/

#include "nts/components/AndGate.hpp"

namespace nts {

AndGate::AndGate()
{
    pinMode(1, PinMode::INPUT);
    pinMode(2, PinMode::INPUT);
    pinMode(3, PinMode::OUTPUT);
}

void AndGate::tick()
{
    auto a = read(1);
    auto b = read(2);

    write(3, a && b);
    inputsClean();
}

void AndGate::display(std::ostream& os) const
{
    auto a = read(1);
    auto b = read(2);

    os << "(" << read(1) << " & " << read(2) << ")";
}

}
