/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include "AComponent.hpp"

namespace nts {

InputComponent& Circuit::input(std::size_t pin)
{
    AComponent::input(pin);

    m_outputs.erase(pin);
    m_inputs.erase(pin);

    return m_inputs[pin];
}

OutputComponent& Circuit::output(std::size_t pin)
{
    AComponent::output(pin);

    m_inputs.erase(pin);
    m_outputs.erase(pin);

    return m_outputs[pin];
}

void Circuit::_compute(PinSetter set)
{
    for (auto& in : m_inputs) {
        in.second = compute(in.first);
        in.second.simulate(++m_internTick);
    }

    for (auto& out : m_outputs) {
        set(out.first, out.second);
    }
}

}
