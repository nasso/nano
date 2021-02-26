/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/MultiComponentFactory.hpp"
#include <stdexcept>

void nts::MultiComponentFactory::addFactory(
    std::unique_ptr<IComponentFactory> factory)
{
    m_factories.push_back(std::move(factory));
}

std::unique_ptr<nts::IComponent> nts::MultiComponentFactory::createComponent(
    const std::string& name)
{
    for (auto& factory : m_factories) {
        try {
            return factory->createComponent(name);
        } catch (std::exception&) {
        }
    }

    throw std::runtime_error("Error can't create component " + name);
}
