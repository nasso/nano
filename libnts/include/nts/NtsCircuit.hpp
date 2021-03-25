/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** NtsCircuit
*/

#ifndef NTSCIRCUIT_HPP_
#define NTSCIRCUIT_HPP_

#include "Circuit.hpp"
#include "IComponentFactory.hpp"
#include <fstream>
#include <istream>
#include <string>
#include <unordered_set>

#ifdef __EMSCRIPTEN__
#include <map>
#else
#include <unordered_map>
#endif

namespace nts {

class NtsCircuit : public Circuit<std::string> {
public:
#ifdef __EMSCRIPTEN__
    using PinMap = std::map<std::string, PinId>;
#else
    using PinMap = std::unordered_map<std::string, PinId>;
#endif

    NtsCircuit(const std::string& source);
    NtsCircuit(const std::string& source, IComponentFactory& factory);
    NtsCircuit(std::istream& in);
    NtsCircuit(std::istream& in, IComponentFactory& factory);

    PinId input(const std::string& pinName) const;
    const PinMap& pins() const;

    void cycle(std::uint64_t maxIterations = 200);

private:
    void build(std::istream& in, IComponentFactory& factory);

    PinMap m_pins;
    std::unordered_set<PinId> m_clocks;
};

}

#endif /* !NTSCIRCUIT_HPP_ */
