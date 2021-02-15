/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_set>

namespace nts {

AComponent::~AComponent()
{
    while (!m_inputs.empty()) {
        remove((*m_inputs.begin()).first);
    }

    while (!m_outputs.empty()) {
        remove((*m_outputs.begin()).first);
    }
}

nts::Tristate AComponent::compute(std::size_t pin) const
{
    if (m_inputs.find(pin) != m_inputs.end()) {
        return m_inputs.at(pin).value;
    } else if (m_outputs.find(pin) != m_outputs.end()) {
        return m_outputs.at(pin).value;
    } else {
        throw std::runtime_error("pin not found: " + std::to_string(pin));
    }
}

nts::Tristate AComponent::compute(std::size_t pin)
{
    const auto& const_self = *this;

    return const_self.compute(pin);
}

void AComponent::simulate(std::size_t tick)
{
    bool inputsDirty = false;

    // read inputs
    for (auto& input : m_inputs) {
        auto& in = input.second;
        auto val = in.link.comp
            ? in.link.comp->compute(in.link.pin)
            : UNDEFINED;

        inputsDirty |= in.value != val;
        in.value = val;
    }

    // if there's nothing to do, skip!
    if (tick == m_currentTick && !inputsDirty) {
        return;
    }

    m_currentTick = tick;

    std::unordered_set<IComponent*> dirty;

    // consider all new links as dirty and needing to be simulated
    for (auto& out : m_outputs) {
        while (!out.second.newlinks.empty()) {
            auto& link = *out.second.newlinks.begin();

            dirty.insert(link.comp);
            out.second.links.insert(link);
            out.second.newlinks.erase(link);
        }
    }

    // delegate computation to the implementation
    _compute(
        [&](std::size_t output, nts::Tristate value) {
            if (m_outputs.find(output) != m_outputs.end()) {
                auto& out = m_outputs.at(output);

                if (out.value != value) {
                    out.value = value;

                    for (auto& link : out.links) {
                        dirty.insert(link.comp);
                    }
                }
            } else {
                throw std::runtime_error("output not found: "
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
        if (in.link.comp != &other || in.link.pin != otherPin) {
            // connecting an input replaces the old connection
            // we need to break the old link explicitly to notify in.link.comp
            if (in.link.comp) {
                unsetLink(pin, *in.link.comp, in.link.pin);
            }

            in.link.comp = &other;
            in.link.pin = otherPin;

            // since the link wasn't known, tell the other component about it!
            other.setLink(otherPin, *this, pin);
        }
    } else if (m_outputs.find(pin) != m_outputs.end()) {
        auto& out = m_outputs.at(pin);

        // same as inputs, only link if the link isn't already present
        if (out.links.find({ &other, otherPin }) == out.links.end()
            && out.newlinks.find({ &other, otherPin }) == out.newlinks.end()) {
            out.newlinks.insert({ &other, otherPin });

            other.setLink(otherPin, *this, pin);
        }
    } else {
        throw std::runtime_error("pin not found: " + std::to_string(pin));
    }
}

void AComponent::unsetLink(std::size_t pin, nts::IComponent& other,
    std::size_t otherPin)
{
    if (m_inputs.find(pin) != m_inputs.end()) {
        auto& in = m_inputs.at(pin);

        // only disconnect if it is connected
        if (in.link.comp == &other && in.link.pin == otherPin) {
            in.link.comp = nullptr;

            // disconnect from the other side
            other.unsetLink(otherPin, *this, pin);
        }
    } else if (m_outputs.find(pin) != m_outputs.end()) {
        auto& out = m_outputs.at(pin);

        // only disconnect if it is connected
        if (out.links.find({ &other, otherPin }) != out.links.end()
            || out.newlinks.find({ &other, otherPin }) != out.newlinks.end()) {
            out.newlinks.erase({ &other, otherPin });
            out.links.erase({ &other, otherPin });

            // disconnect from the other side
            other.unsetLink(otherPin, *this, pin);
        }
    } else {
        throw std::runtime_error("pin not found: " + std::to_string(pin));
    }
}

void AComponent::input(std::size_t pin)
{
    remove(pin);
    m_inputs[pin].link.comp = nullptr;
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

        while (!out.links.empty()) {
            auto& link = *out.links.begin();

            if (link.comp) {
                unsetLink(pin, *link.comp, link.pin);
            }
        }

        while (!out.newlinks.empty()) {
            auto& link = *out.newlinks.begin();

            if (link.comp) {
                unsetLink(pin, *link.comp, link.pin);
            }
        }

        m_outputs.erase(pin);
    } else if (m_inputs.find(pin) != m_inputs.end()) {
        auto& in = m_inputs.at(pin);

        if (in.link.comp) {
            unsetLink(pin, *in.link.comp, in.link.pin);
        }

        m_inputs.erase(pin);
    }
}

void AComponent::dump() const
{
    std::cout << *this << '\n';
}

void AComponent::dump(std::ostream& os) const
{
    bool first = true;

    os << "(component (";
    for (auto& pin : m_inputs) {
        if (!first)
            os << " ";
        first = false;
        os << "(" << pin.first << " " << compute(pin.first) << ")";
    }
    os << ") (";
    first = true;
    for (auto& pin : m_outputs) {
        if (!first)
            os << " ";
        first = false;
        os << "(" << pin.first << " " << compute(pin.first) << ")";
    }
    os << "))";
}

bool AComponent::Link::operator==(const Link& other) const
{
    return comp == other.comp && pin == other.pin;
}

}
