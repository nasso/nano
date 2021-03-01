/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AndGate
*/

#include "nts/AndGate.hpp"

namespace nts {

AndGate::AndGate()
{
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
}

void AndGate::simulate()
{
    auto a = read(1);
    auto b = read(2);

    write(3, a && b);
}

void AndGate::display(std::ostream& os) const
{
    auto a = read(1);
    auto b = read(2);

    os << "(" << read(1) << " & " << read(2) << ")";
}

}
