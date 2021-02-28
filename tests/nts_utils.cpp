/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** nts_utils
*/

#include "nts_utils.hpp"
#include "nts/BuiltInComponentFactory.hpp"
#include "nts/ComboComponentFactory.hpp"
#include "nts/NtsCircuit.hpp"
#include "nts/NtsComponentFactory.hpp"
#include <fstream>
#include <string>
#include <vector>

nts::NtsCircuit loadNts(const std::string& path,
    const std::vector<std::string>& includePaths)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        throw new std::runtime_error("Couldn't open file: " + path);
    }

    nts::ComboComponentFactory mcf;
    mcf.add(std::make_unique<nts::BuiltInComponentFactory>());

    for (const auto& path : includePaths) {
        mcf.add(std::make_unique<nts::NtsComponentFactory>(path));
    }

    return nts::NtsCircuit(file, mcf);
}
