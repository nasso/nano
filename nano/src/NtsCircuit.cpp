/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** NtsCircuit
*/

#include "nts/NtsCircuit.hpp"
#include "nts/BuiltInComponentFactory.hpp"
#include "nts/ComboComponentFactory.hpp"
#include "nts/NtsComponentFactory.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

namespace nts {

NtsCircuit::NtsCircuit(const std::string& source)
{
    std::istringstream iss(source);
    BuiltInComponentFactory builtins;

    build(iss, builtins);
}

NtsCircuit::NtsCircuit(const std::string& source, IComponentFactory& factory)
{
    std::istringstream iss(source);

    build(iss, factory);
}

NtsCircuit::NtsCircuit(std::istream& in)
{
    BuiltInComponentFactory builtins;

    build(in, builtins);
}

NtsCircuit::NtsCircuit(std::istream& in, IComponentFactory& factory)
{
    build(in, factory);
}

PinId NtsCircuit::input(const std::string& pinName) const
{
    return m_pins.at(pinName);
}

const NtsCircuit::PinMap& NtsCircuit::pins() const
{
    return m_pins;
}

void NtsCircuit::cycle(std::uint64_t maxIterations)
{
    while (maxIterations-- && !stable()) {
        tick();
    }

    if (!stable()) {
        throw std::runtime_error("couldn't stabilize component");
    }

    for (PinId pin : m_clocks) {
        write(pin, !read(pin));
    }
}

void NtsCircuit::build(std::istream& in, IComponentFactory& factory)
{
    const std::regex comment_r("(#.*)");
    const std::regex trim_r("^\\s*|\\s*$");
    const std::regex sec_links_r("^\\.links\\:$");
    const std::regex sec_chipsets_r("^\\.chipsets\\:$");
    const std::regex link_r("^([^:]+):(\\d+)\\s+([^:]+):(\\d+)$");
    const std::regex chip_r("^(\\w+)\\s+([^:]+)$");

    struct Pin {
        std::string chip;
        PinId id;
    };

    using Link = std::pair<Pin, Pin>;

    enum {
        LINKS,
        CHIPSETS,
    } section;

    std::vector<Link> links;

    PinId pinCounter = 0;
    std::string line;
    std::smatch m;

    while (std::getline(in, line)) {
        line = std::regex_replace(line, comment_r, "");
        line = std::regex_replace(line, trim_r, "");

        if (line.empty()) {
            continue;
        }

        if (std::regex_match(line, sec_chipsets_r)) {
            section = CHIPSETS;
        } else if (std::regex_match(line, sec_links_r)) {
            section = LINKS;
        } else if (section == CHIPSETS && std::regex_match(line, m, chip_r)) {
            std::string type(m[1]);
            std::string name(m[2]);

            if (type == "ignored") {
                pinCounter++;
            } else if (type == "input") {
                pinMode(++pinCounter, PinMode::INPUT);
                m_pins.emplace(name, pinCounter);
            } else if (type == "clock") {
                pinMode(++pinCounter, PinMode::INPUT);
                m_pins.emplace(name, pinCounter);
                m_clocks.insert(pinCounter);
            } else if (type == "output") {
                pinMode(++pinCounter, PinMode::OUTPUT);
                m_pins.emplace(name, pinCounter);
            } else {
                insert(name, factory.createComponent(type).unwrap());
            }
        } else if (section == LINKS && std::regex_match(line, m, link_r)) {
            links.push_back({
                { m[1], std::stoul(m[2]) },
                { m[3], std::stoul(m[4]) },
            });
        } else {
            throw std::runtime_error("syntax error: " + line);
        }
    }

    for (const auto& link : links) {
        bool firstIsPin = m_pins.find(link.first.chip) != m_pins.end();
        bool secondIsPin = m_pins.find(link.second.chip) != m_pins.end();

        if (firstIsPin && link.first.id != 1) {
            throw std::runtime_error("invalid pin: " + link.first.chip + ":"
                + std::to_string(link.first.id));
        }

        if (secondIsPin && link.second.id != 1) {
            throw std::runtime_error("invalid pin: " + link.second.chip + ":"
                + std::to_string(link.second.id));
        }

        if (firstIsPin && secondIsPin) {
            connect(m_pins.at(link.first.chip), m_pins.at(link.second.chip));
        } else if (firstIsPin) {
            connect(m_pins.at(link.first.chip), link.second.chip,
                link.second.id);
        } else if (secondIsPin) {
            connect(m_pins.at(link.second.chip), link.first.chip,
                link.first.id);
        } else {
            connect(link.first.chip, link.first.id, link.second.chip,
                link.second.id);
        }
    }
}

}

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(nts_ntscircuit)
{
    using Circuit = nts::Circuit<std::string>;

    emscripten::register_vector<std::string>("vector<std::string>");
    emscripten::register_map<std::string, nts::PinId>("PinMap");

    emscripten::class_<nts::NtsCircuit, emscripten::base<Circuit>>("NtsCircuit")
        .constructor<std::string>()
        .constructor<std::string, nts::IComponentFactory&>()
        .property("pins", &nts::NtsCircuit::pins);
}
#endif
