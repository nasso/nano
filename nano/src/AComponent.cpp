/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** AComponent
*/

#include "nts/AComponent.hpp"
#include <string>

namespace nts {

AComponent::AComponent()
{
}

AComponent::AComponent(Pinout pinout)
{
    for (const auto& pin : pinout) {
        pinMode(pin.first, pin.second);
    }
}

void AComponent::pinMode(PinId pin, PinMode flags)
{
    if (flags == PinMode::NONE) {
        m_pinout.erase(pin);
        m_pins.erase(pin);
    } else {
        m_pinout[pin] = flags;
        m_pins[pin] = Tristate::UNDEFINED;
    }
}

const Pinout& AComponent::pinout() const
{
    return m_pinout;
}

Tristate AComponent::read(PinId pin) const
{
    try {
        return m_pins.at(pin);
    } catch (...) {
        throw std::out_of_range("No such pin: " + std::to_string(pin));
    }
}

void AComponent::write(PinId pin, Tristate value)
{
    try {
        Tristate& pinval = m_pins.at(pin);

        if (!m_inputsDirty
            && pinval != value
            && m_pinout.at(pin) == PinMode::INPUT) {
            m_inputsDirty = true;
        }

        pinval = value;
    } catch (...) {
        throw std::out_of_range("No such pin: " + std::to_string(pin));
    }
}

bool AComponent::inputsDirty() const
{
    return m_inputsDirty;
}

void AComponent::inputsClean()
{
    m_inputsDirty = false;
}

bool AComponent::stable() const
{
    return !m_inputsDirty;
}

}

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

struct AComponentWrapper : public emscripten::wrapper<nts::AComponent> {
    EMSCRIPTEN_WRAPPER(AComponentWrapper);

    void tick()
    {
        return call<void>("tick");
    }

    void display(std::ostream& os) const
    {
        os << "(js component)";
    }
};

EMSCRIPTEN_BINDINGS(nts_acomponent)
{
    emscripten::class_<nts::AComponent,
        emscripten::base<nts::IComponent>>("AComponent")
        .property("stable", &nts::AComponent::stable)
        .property("pinout", &nts::AComponent::pinout)
        .function("tick", &nts::AComponent::tick,
            emscripten::pure_virtual())
        .function("read", &nts::AComponent::read)
        .function("write", &nts::AComponent::write)
        .function("pinMode", &nts::AComponent::pinMode)
        .allow_subclass<AComponentWrapper>("AComponentWrapper");
}
#endif
