/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include "AComponent.hpp"

namespace nts {

void Circuit::_compute(PinSetter set)
{
    m_internTick++;
    for (auto& in : m_inputs) {
        *in.second = compute(in.first);
        in.second->simulate(m_internTick);
    }

    for (auto& out : m_outputs) {
        set(out.first, *out.second);
    }
}

}
