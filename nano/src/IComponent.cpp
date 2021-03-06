/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IComponent
*/

#include "nts/IComponent.hpp"

std::ostream& operator<<(std::ostream& os, const nts::IComponent& comp)
{
    comp.display(os);
    return os;
}

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

struct IComponentWrapper : public emscripten::wrapper<nts::IComponent> {
    EMSCRIPTEN_WRAPPER(IComponentWrapper);

    void tick() override
    {
        return call<void>("tick");
    }

    bool stable() const override
    {
        return call<bool>("stable");
    }

    const nts::Pinout& pinout() const override
    {
        return call<const nts::Pinout&>("pinout");
    }

    nts::Tristate read(nts::PinId pin) const override
    {
        return call<nts::Tristate>("pinout", pin);
    }

    void write(nts::PinId pin, nts::Tristate value) override
    {
        return call<void>("write", pin, value);
    }

    void display(std::ostream& os) const override
    {
        os << "(js component)";
    }
};

EMSCRIPTEN_BINDINGS(nts_icomponent)
{
    emscripten::class_<nts::IComponent>("IComponent")
        .function("tick", &nts::IComponent::tick, emscripten::pure_virtual())
        .function("stable", &nts::IComponent::stable,
            emscripten::pure_virtual())
        .function("pinout", &nts::IComponent::pinout,
            emscripten::pure_virtual())
        .function("read", &nts::IComponent::read, emscripten::pure_virtual())
        .function("write", &nts::IComponent::write, emscripten::pure_virtual())
        .allow_subclass<IComponentWrapper>("IComponentWrapper");
}
#endif
