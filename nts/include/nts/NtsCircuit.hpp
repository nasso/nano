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
#include <unordered_map>
#include <unordered_set>

namespace nts {

class NtsCircuit : public Circuit<std::string> {
public:
    using PinMap = std::unordered_map<std::string, PinId>;

    NtsCircuit(const std::string& path,
        const std::vector<std::string>& includePaths = {});
    NtsCircuit(std::istream& in, IComponentFactory& factory);
    NtsCircuit(std::istream& in);

    PinId input(const std::string& pinName) const;
    const PinMap& pins() const;

    virtual void simulate() override;

private:
    void build(std::istream& in, IComponentFactory& factory);

    PinMap m_pins;
    std::unordered_set<PinId> m_clocks;
};

}

#endif /* !NTSCIRCUIT_HPP_ */
