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

        if (in.comp) {
            return in.comp->compute(in.pin);
        } else {
            return UNDEFINED;
        }
    } else if (m_outputs.find(pin) != m_outputs.end()) {
        return m_outputs.at(pin).value;
    } else {
        throw std::runtime_error("pin not found: " + std::to_string(pin));
    }
}

void AComponent::simulate(std::size_t tick)
{
    if (tick == m_currentTick) {
        return;
    }

    m_currentTick = tick;

    std::set<IComponent*> dirty;

    _compute([&](std::size_t output, nts::Tristate value) {
        if (m_outputs.find(output) != m_outputs.end()) {
            auto& out = m_outputs.at(output);

            if (out.value != value) {
                out.value = value;

                for (auto& child : out.children) {
                    dirty.insert(child.comp);
                }
            }
        } else {
            throw new std::runtime_error("output not found: "
                + std::to_string(output));
        }
    });

    while (!dirty.empty()) {
        auto& comp = *dirty.begin();

        comp->simulate(tick);

        dirty.erase(comp);
    }
}

void AComponent::setLink(std::size_t pin, nts::IComponent& other,
    std::size_t otherPin)
{
    if (m_inputs.find(pin) != m_inputs.end()) {
        auto& in = m_inputs.at(pin);

        // only perform the link if it isn't already set
        if (in.comp != &other || in.pin != otherPin) {
            // connecting an input replaces the old connection
            // we need to break the old link explicitly to notify in.comp
            if (in.comp) {
                unsetLink(pin, *in.comp, in.pin);
            }

            in.comp = &other;
            in.pin = otherPin;

            // since the link wasn't known, tell the other component about it!
            other.setLink(otherPin, *this, pin);
        }
    } else if (m_outputs.find(pin) != m_outputs.end()) {
        auto& out = m_outputs.at(pin);

        // same as inputs, only link if the link isn't already present
        if (out.children.find({ &other, otherPin }) == out.children.end()) {
            out.children.insert({ &other, otherPin });

            other.setLink(otherPin, *this, pin);
        }
    } else {
        throw new std::runtime_error("pin not found: " + std::to_string(pin));
    }
}

void AComponent::unsetLink(std::size_t pin, nts::IComponent& other,
    std::size_t otherPin)
{
    if (m_inputs.find(pin) != m_inputs.end()) {
        auto& in = m_inputs.at(pin);

        // only disconnect if it is connected
        if (in.comp == &other && in.pin == otherPin) {
            in.comp = NULL;

            // disconnect from the other side
            other.unsetLink(otherPin, *this, pin);
        }
    } else if (m_outputs.find(pin) != m_outputs.end()) {
        auto& out = m_outputs.at(pin);

        // only disconnect if it is connected
        if (out.children.find({ &other, otherPin }) != out.children.end()) {
            out.children.erase({ &other, otherPin });

            // disconnect from the other side
            other.unsetLink(otherPin, *this, pin);
        }
    } else {
        throw new std::runtime_error("pin not found: " + std::to_string(pin));
    }
}

void AComponent::input(std::size_t pin)
{
    remove(pin);
    m_inputs[pin].comp = NULL;
}

void AComponent::output(std::size_t pin)
{
    remove(pin);
    m_outputs[pin].value = UNDEFINED;
}

void AComponent::remove(std::size_t pin)
{
    if (m_outputs.find(pin) != m_outputs.end()) {
        auto& out = m_outputs.at(pin);

        while (!out.children.empty()) {
            auto& child = *out.children.begin();

            unsetLink(pin, *child.comp, child.pin);
        }

        m_outputs.erase(pin);
    } else if (m_inputs.find(pin) != m_inputs.end()) {
        auto& in = m_inputs.at(pin);

        unsetLink(pin, *in.comp, in.pin);

        m_inputs.erase(pin);
    }
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
