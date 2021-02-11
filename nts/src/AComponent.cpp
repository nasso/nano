/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include <iostream>

namespace nts {

nts::Tristate AComponent::compute(std::size_t pin) const
{
    if (m_inputs.find(pin) != m_inputs.end()) {
        auto& in = m_inputs.at(pin);

        return in.component.compute(in.output);
    } else if (m_outputs.find(pin) != m_outputs.end()) {
        return m_outputs.at(pin);
    } else {
        return UNDEFINED;
    }
}

void AComponent::simulate(std::size_t tick)
{
    if (tick == m_currentTick) {
        return;
    }

    if (!m_simulating) {
        m_simulating = true;

        for (auto& input : m_inputs) {
            input.second.component.simulate(tick);
        }

        m_simulating = false;
        m_currentTick = tick;

        _compute(tick);
    } else {
        // cyclic - do nothing
    }
}

void AComponent::setLink(std::size_t pin, nts::IComponent& other,
    std::size_t otherPin)
{
    m_inputs.insert({ pin, { other, otherPin } });
}

void AComponent::set(std::size_t output, nts::Tristate value)
{
    m_outputs[output] = value;
}

void AComponent::dump() const
{
    bool first = true;

    std::cout << "(";
    for (auto& in : m_inputs) {
        if (!first)
            std::cout << " ";
        first = false;
        std::cout << in.first << ":" << compute(in.first);
    }
    std::cout << ")";

    std::cout << " -> ";
    first = true;

    std::cout << "(";
    for (auto& out : m_outputs) {
        if (!first)
            std::cout << " ";
        first = false;
        std::cout << out.first << ":" << compute(out.first);
    }
    std::cout << ")" << std::endl;
}

}
