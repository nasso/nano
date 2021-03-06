/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ComponentFactory
*/

#include "nts/NtsComponentFactory.hpp"
#include "nts/BuiltInComponentFactory.hpp"
#include "nts/ComboComponentFactory.hpp"
#include "nts/NtsCircuit.hpp"
#include <exception>
#include <fstream>
#include <memory>

namespace nts {

NtsComponentFactory::NtsComponentFactory(std::string dirpath) noexcept
    : m_dirpath(dirpath)
{
}

NtsComponentFactory::NtsComponentFactory(const NtsComponentFactory& base,
    const std::string& except) noexcept
    : m_dirpath(base.m_dirpath)
    , m_exceptions { base.m_exceptions }
{
    m_exceptions.insert(except);
}

NtsComponentFactory::Output NtsComponentFactory::createComponent(
    const std::string& name) noexcept
{
    std::string fname = m_dirpath;

    if (!m_dirpath.empty() && m_dirpath[m_dirpath.size() - 1] != '/') {
        fname += '/';
    }

    fname += name + ".nts";

    if (m_exceptions.find(fname) != m_exceptions.end()) {
        // cyclic!
        return {};
    }

    std::unique_ptr<NtsComponentFactory> subfactory(new NtsComponentFactory(
        *this, name));

    ComboComponentFactory mcf;
    mcf.add(std::make_unique<BuiltInComponentFactory>());
    mcf.add(std::move(subfactory));

    std::ifstream file(fname);

    if (!file.is_open()) {
        return {};
    }

    try {
        return { std::make_unique<NtsCircuit>(file, mcf) };
    } catch (...) {
        return {};
    }
}

}
