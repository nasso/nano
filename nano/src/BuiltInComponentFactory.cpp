/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/BuiltInComponentFactory.hpp"
#include "nts/components/AndGate.hpp"
#include "nts/components/ConstComponent.hpp"
#include "nts/components/NotGate.hpp"
#include "nts/components/DecoderComponent.hpp"
#include <fstream>
#include <stdexcept>

namespace nts {

BuiltInComponentFactory::BuiltInComponentFactory() noexcept
{
    m_scf.add("and", std::make_unique<AndGate>);
    m_scf.add("not", std::make_unique<NotGate>);
    m_scf.add("true", []() {
        return std::make_unique<ConstComponent>(Tristate::TRUE);
    });
    m_scf.add("false", []() {
        return std::make_unique<ConstComponent>(Tristate::FALSE);
    });
    m_scf.add("4514", std::make_unique<DecoderComponent>);
}

BuiltInComponentFactory::Output BuiltInComponentFactory::createComponent(
    const std::string& name) noexcept
{
    return m_scf.createComponent(name);
}

}

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(nts_builtincomponentfactory)
{
    emscripten::class_<nts::BuiltInComponentFactory,
        emscripten::base<nts::IComponentFactory>>("BuiltInComponentFactory")
        .constructor<>()
        .function("createComponent",
            &nts::BuiltInComponentFactory::createComponent);
}
#endif
