/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NotGate
*/

#include "nts/NotGate.hpp"
#include <iostream>

namespace nts {

NotGate::NotGate()
{
    pinMode(1, PinMode::INPUT);
    pinMode(2, PinMode::OUTPUT);
}

void NotGate::simulate()
{
    write(2, !read(1));
}

void NotGate::display(std::ostream& os) const
{
    auto a = read(1);

    os << "(!" << read(1) << ")";
}

}
