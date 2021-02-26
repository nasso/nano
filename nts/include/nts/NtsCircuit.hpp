/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** NtsCircuit
*/

#ifndef NTSCIRCUIT_HPP_
#define NTSCIRCUIT_HPP_

#include "Circuit.hpp"
#include "MultiComponentFactory.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace nts {

class NtsCircuit : public Circuit<std::string> {
public:
    NtsCircuit(const std::string& filename);

    PinId input(const std::string& pinName);

private:
    std::map<std::string, PinId> m_pins;
};

}

#endif /* !NTSCIRCUIT_HPP_ */
