/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "BuiltInComponentFactory.hpp"
#include "AndGate.hpp"
#include "ClockComponent.hpp"
#include "ConstComponent.hpp"
#include "InputComponent.hpp"
#include "NotGate.hpp"
#include "OutputComponent.hpp"
#include <fstream>
#include <stdexcept>

namespace nts {

std::unique_ptr<nts::IComponent> BuiltInComponentFactory::createComponent(
    const std::string& name)
{
    if (name == "and") {
        return std::unique_ptr<nts::IComponent>(new AndGate);
    } else if (name == "not") {
        return std::unique_ptr<nts::IComponent>(new NotGate);
    } else if (name == "true") {
        return std::unique_ptr<nts::IComponent>(new ConstComponent(TRUE));
    } else if (name == "false") {
        return std::unique_ptr<nts::IComponent>(new ConstComponent(FALSE));
    }
    throw std::runtime_error("Error can't create component " + name);
}

}
