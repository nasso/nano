/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "NTSComponentFactory.hpp"
#include "NTSCircuit.hpp"
#include <fstream>
#include <stdexcept>

nts::NTSComponentFactory::NTSComponentFactory(std::string dirpath)
{
    m_dirpath = dirpath;
}

std::unique_ptr<nts::IComponent> nts::NTSComponentFactory::createComponent(const std::string& name)
{
    std::fstream file(m_dirpath + name);

    if (file.is_open())
        throw std::runtime_error("Error can't open file for component " + name);
    return std::unique_ptr<NTSCircuit>(new NTSCircuit(m_dirpath + name));
}
