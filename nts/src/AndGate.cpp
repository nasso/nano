/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AndGate
*/

#include "AndGate.hpp"
#include "IComponent.hpp"

namespace nts {

Pinout AndGate::pinout() const
{
    return Pinout({
        { 1, PinUsage::INPUT },
        { 2, PinUsage::INPUT },
        { 3, PinUsage::OUTPUT },
    });
}

void AndGate::simulate(IPinoutBuffer& pinout)
{
    auto a = pinout.read(1);
    auto b = pinout.read(2);

    pinout.write(3, a && b);
}

void AndGate::display(std::ostream& os) const
{
    os << "and";
}

}
