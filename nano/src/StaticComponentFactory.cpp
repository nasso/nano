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

IComponentFactory::Output StaticComponentFactory::createComponent(
    const IComponentFactory::Name& name)
{
    return m_generators.at(name)();
}

void StaticComponentFactory::add(const IComponentFactory::Name& name,
    StaticComponentFactory::Generator gen)
{
    m_generators[name] = gen;
}

}
