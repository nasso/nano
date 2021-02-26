/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/NtsComponentFactory.hpp"
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

    return std::unique_ptr<NTSCircuit>(
        new NTSCircuit(m_dirpath + name + ".nts"));
}
