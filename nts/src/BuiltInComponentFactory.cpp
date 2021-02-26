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

std::unique_ptr<nts::IComponent> BuiltInComponentFactory::createComponent(
    const std::string& name)
{
    if (name == "and") {
        return std::make_unique<AndGate>();
    } else if (name == "not") {
        return std::make_unique<NotGate>();
    } else if (name == "true") {
        return std::make_unique<ConstComponent>(Tristate::TRUE);
    } else if (name == "false") {
        return std::make_unique<ConstComponent>(Tristate::FALSE);
    }

    throw std::runtime_error("Error can't create component " + name);
}

}
