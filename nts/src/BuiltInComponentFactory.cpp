/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/BuiltInComponentFactory.hpp"
#include "nts/AndGate.hpp"
#include "nts/ClockComponent.hpp"
#include "nts/ConstComponent.hpp"
#include "nts/NotGate.hpp"
#include <fstream>
#include <stdexcept>

namespace nts {

BuiltInComponentFactory::BuiltInComponentFactory()
{
    m_scf.add("and", std::make_unique<AndGate>);
    m_scf.add("not", std::make_unique<NotGate>);
    m_scf.add("true", []() {
        return std::make_unique<ConstComponent>(Tristate::TRUE);
    });
    m_scf.add("false", []() {
        return std::make_unique<ConstComponent>(Tristate::FALSE);
    });
}

IComponentFactory::Output BuiltInComponentFactory::createComponent(
    const IComponentFactory::Name& name)
{
    return m_scf.createComponent(name);
}

}
