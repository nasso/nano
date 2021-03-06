/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** nts_utils
*/

#ifndef NTS_UTILS_HPP_
#define NTS_UTILS_HPP_

#include "nts/NtsCircuit.hpp"
#include <string>
#include <vector>

nts::NtsCircuit loadNts(const std::string& path,
    const std::vector<std::string>& includePaths = { "components" });

void stabilize(nts::IComponent& component);

#endif /* !NTS_UTILS_HPP_ */
