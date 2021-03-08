/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/ComboComponentFactory.hpp"

namespace nts {

void ComboComponentFactory::add(
    std::unique_ptr<IComponentFactory> factory) noexcept
{
    m_factories.push_back(std::move(factory));
}

ComboComponentFactory::Output ComboComponentFactory::createComponent(
    const std::string& name) noexcept
{
    for (auto& factory : m_factories) {
        auto out = factory->createComponent(name);

        if (out) {
            return out;
        }
    }

    return {};
}

}

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

emscripten::val create(nts::ComboComponentFactory& self,
    const std::string& name)
{
    auto comp = self.createComponent(name);

    if (comp) {
        return emscripten::val(comp.unwrap());
    } else {
        return emscripten::val::undefined();
    }
}

EMSCRIPTEN_BINDINGS(nts_combocomponentfactory)
{
    emscripten::class_<nts::ComboComponentFactory,
        emscripten::base<nts::IComponentFactory>>("ComboComponentFactory")
        .constructor<>()
        .function("createComponent", &create)
        .function("add", &nts::ComboComponentFactory::add);
}
#endif
