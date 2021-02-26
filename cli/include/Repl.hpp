/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Repl
*/

#ifndef REPL_HPP_
#define REPL_HPP_

#include "nts/NtsCircuit.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Repl {
public:
    Repl(const std::string& path, const std::vector<std::string>& includePaths);

    void run(std::istream& in, std::ostream& out);

private:
    using TristateMap = std::map<std::string, nts::Tristate>;

    void eval(const std::string& command, std::ostream& out);
    void display(std::ostream& out);
    void tick();
    void readPins(TristateMap& dest, nts::PinMode filter);

    TristateMap m_inputs;
    TristateMap m_outputs;

    std::size_t m_tick = 0;
    nts::NtsCircuit m_circuit;
    bool m_shouldQuit;
};

#endif /* !REPL_HPP_ */
