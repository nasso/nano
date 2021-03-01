/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/ComboComponentFactory.hpp"

namespace nts {

void ComboComponentFactory::add(std::unique_ptr<IComponentFactory> factory)
{
    m_factories.push_back(std::move(factory));
}

std::unique_ptr<IComponent> ComboComponentFactory::createComponent(
    const std::string& name)
{
    for (auto& factory : m_factories) {
        try {
            return factory->createComponent(name);
        } catch (...) {
        }
    }

    throw std::runtime_error("Error can't create component " + name);
}

}
