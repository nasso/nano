/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "operator/syncAll.hpp"

void nts::AComponent::simulate(size_t tick)
{
    if (tick != m_currentTick) {
        m_currentTick = tick;
        // Reset Component
    }
}

nts::Tristate nts::AComponent::compute(size_t pin)
{
    if (pin >= m_pins.size())
        return UNDEFINED;
    return m_pins[pin].getValue();
}

void nts::AComponent::setLink(size_t pin, nts::IComponent& other, size_t otherPin)
{
    m_links[pin] = other.getPin(otherPin).asObservable().subscribe([&](nts::Tristate value) {
        static size_t tick = 0;

        if (m_currentTick == tick) {
            m_pins[pin].next(value);
            tick++;
        }
    });
}

nts::Pin& nts::AComponent::getPin(size_t pin)
{
    return m_pins[pin];
}

void nts::AComponent::_init()
{
    std::vector<rtk::Observable<nts::Tristate>> obs;

    for (size_t index : m_inputPins)
        obs.push_back(m_pins[index].asObservable());
    rtk::syncAll(obs).subscribe([&](auto) { _simulate(); });
}

void nts::AComponent::dump() const
{
}