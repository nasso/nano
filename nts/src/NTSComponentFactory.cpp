/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/NtsComponentFactory.hpp"
#include "nts/BuiltInComponentFactory.hpp"
#include "nts/NtsCircuit.hpp"
#include <fstream>
#include <stdexcept>

nts::NtsComponentFactory::NtsComponentFactory(std::string dirpath)
{
    m_dirpath = dirpath;
}

std::unique_ptr<nts::IComponent> nts::NtsComponentFactory::createComponent(
    const std::string& name)
{
    std::fstream file(m_dirpath + name + ".nts");

    if (!file.is_open())
        throw std::runtime_error("Error can't open file for component " + name);

    for (const auto& exception : m_exceptions) {
        if (exception == name)
            throw std::runtime_error("Cyclique component " + name);
    }
    std::unique_ptr<nts::NTSComponentFactory> newfacto(
        new nts::NTSComponentFactory("./components/"));
    for (const auto& exception : m_exceptions)
        newfacto->addException(exception);
    newfacto->addException(name);
    std::vector<std::unique_ptr<nts::IComponentFactory>> factories;
    factories.emplace_back(new nts::BuiltInComponentFactory);
    factories.emplace_back(std::move(newfacto));

    std::unique_ptr<NTSCircuit> component(
        new NTSCircuit(m_dirpath + name + ".nts", factories));

    return component;
}

void nts::NTSComponentFactory::addException(const std::string& name)
{
    m_exceptions.push_back(name);
}
