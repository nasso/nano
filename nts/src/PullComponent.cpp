/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** PullComponent
*/

#include "PullComponent.hpp"
#include "AComponent.hpp"

namespace nts {

PullComponent::PullComponent(PullDirection direction)
    : m_dir(direction)
{
    input(1);
    output(2);
    simulate(1);
}

void PullComponent::_compute(PinSetter set)
{
    auto in = compute(1);

    if (in == UNDEFINED) {
        set(2, m_dir == UP ? TRUE : FALSE);
    } else {
        set(2, in);
    }
}

}
