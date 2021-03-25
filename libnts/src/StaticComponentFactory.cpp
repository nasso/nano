/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** StaticComponentFactory
*/

#include "nts/StaticComponentFactory.hpp"

namespace nts {

StaticComponentFactory::StaticComponentFactory()
{
}

StaticComponentFactory::Output StaticComponentFactory::createComponent(
    const std::string& name) noexcept
{
    if (m_generators.find(name) != m_generators.end()) {
        return m_generators.at(name)();
    } else {
        return {};
    }
}

void StaticComponentFactory::add(const std::string& name,
    StaticComponentFactory::Generator gen)
{
    m_generators[name] = gen;
}

}
