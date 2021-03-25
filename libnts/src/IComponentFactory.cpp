/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** IComponentFactory
*/

#include "nts/IComponentFactory.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

struct IComponentFactoryWrapper
    : public emscripten::wrapper<nts::IComponentFactory> {
    EMSCRIPTEN_WRAPPER(IComponentFactoryWrapper);

    nts::IComponentFactory::Output createComponent(
        const std::string& name) noexcept
    {
        auto val = call<emscripten::val>("createComponent", name);

        if (val.isUndefined() || val.isNull()) {
            return {};
        } else {
            return val.as<std::unique_ptr<nts::IComponent>>();
        }
    }
};

EMSCRIPTEN_BINDINGS(nts_icomponentfactory)
{
    emscripten::class_<nts::IComponentFactory>("IComponentFactory")
        .function("createComponent", &nts::IComponentFactory::createComponent,
            emscripten::pure_virtual())
        .allow_subclass<IComponentFactoryWrapper>("IComponentFactoryWrapper");
}
#endif
