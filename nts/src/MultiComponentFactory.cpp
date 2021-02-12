/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "MultiComponentFactory.hpp"
#include <stdexcept>

nts::MultiComponentFactory::MultiComponentFactory(std::vector<std::shared_ptr<IComponentFactory>> factories)
{
    m_factories = factories;
}

std::unique_ptr<nts::IComponent> nts::MultiComponentFactory::createComponent(const std::string& name)
{
    for (auto factory : m_factories) {
        try {
            return factory->createComponent(name);
        } catch (std::exception) {
        }
    }
    throw std::runtime_error("Error can't create component " + name);
}
