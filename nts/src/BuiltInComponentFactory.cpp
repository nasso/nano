/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "BuiltInComponentFactory.hpp"
#include "AndGate.hpp"
#include "InputComponent.hpp"
#include "NotGate.hpp"
#include "OutputComponent.hpp"
#include "PullComponent.hpp"
#include <fstream>
#include <stdexcept>

nts::BuiltInComponentFactory::BuiltInComponentFactory()
{
}

std::unique_ptr<nts::IComponent> nts::BuiltInComponentFactory::createComponent(const std::string& name)
{
    if (name == "input") {
        return std::unique_ptr<nts::IComponent>(new InputComponent);
    } else if (name == "output") {
        return std::unique_ptr<nts::IComponent>(new OutputComponent);
    } else if (name == "and") {
        return std::unique_ptr<nts::IComponent>(new AndGate);
    } else if (name == "not") {
        return std::unique_ptr<nts::IComponent>(new NotGate);
    } else if (name == "pullup") {
        return std::unique_ptr<nts::IComponent>(
            new PullComponent(PullComponent::UP));
    } else if (name == "pulldown") {
        return std::unique_ptr<nts::IComponent>(
            new PullComponent(PullComponent::DOWN));
    }
    throw std::runtime_error("Error can't create component " + name);
}
