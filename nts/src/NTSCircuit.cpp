/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** NTSCircuit
*/

#include "NTSCircuit.hpp"
#include "BuiltInComponentFactory.hpp"
#include "NTSComponentFactory.hpp"
#include <iostream>
#include <regex>
#include <vector>

namespace nts {

NTSCircuit::NTSCircuit(const std::string& filename)
    : m_file(filename)
{
    m_factory.addFactory(std::move(std::unique_ptr<IComponentFactory>(
        new BuiltInComponentFactory)));
    m_factory.addFactory(std::move(std::unique_ptr<IComponentFactory>(
        new NTSComponentFactory("./components/"))));
    if (!m_file.is_open())
        throw std::runtime_error("Error");
    parse();
}

void NTSCircuit::createChip(std::string& str)
{
    std::regex component_type("\\w+");
    std::string name;
    std::string type;
    std::vector<std::string> res;
    std::sregex_iterator it(str.begin(), str.end(), component_type);

    for (std::sregex_iterator it_end; it != it_end; ++it)
        res.push_back((*it)[0]);
    if (res.size() != 2)
        throw std::runtime_error(
            "Error with parsing config file unreconized string: " + str);
    type = res[0];
    name = res[1];
    if (type == "ignored") {
        m_currentPin++;
    } else if (type == "input") {
        m_pins.emplace(name, &input(++m_currentPin));
    } else if (type == "output") {
        m_pins.emplace(name, &output(++m_currentPin));
    } else {
        m_ownedComponents.emplace(name, m_factory.createComponent(type));
    }
}

void NTSCircuit::createLink(std::string& str)
{
    std::regex components_r("(\\w+\\:[0-9]+)");
    std::regex component_r("\\w+");
    std::string tmp_str;
    std::vector<std::vector<std::string>> components;
    std::sregex_iterator it(str.begin(), str.end(), components_r);
    Link link;

    for (std::sregex_iterator it_end; it != it_end; ++it) {
        tmp_str = (*it)[0];
        std::sregex_iterator it2(tmp_str.begin(), tmp_str.end(), component_r);
        std::vector<std::string> tmp;
        for (std::sregex_iterator it2_end; it2 != it2_end; ++it2)
            tmp.push_back((*it2)[0]);
        components.push_back(tmp);
    }
    if (components.size() != 2
        || components[0].size() != 2
        || components[1].size() != 2)
        throw std::runtime_error(
            "Error with parsing config file unreconized string: " + str);
    link.name1 = components[0][0];
    link.name2 = components[1][0];
    link.pin1 = std::stoul(components[0][1]);
    link.pin2 = std::stoul(components[1][1]);
    m_links.push_back(link);
}

void NTSCircuit::parseChips()
{
    std::string str;
    std::regex comment_r("#.*");
    std::regex trim_r("^\\s*|\\s*$");
    std::regex links_r("^\\.links\\:$");

    while (getline(m_file, str)) {
        str = std::regex_replace(str, comment_r, "");
        str = std::regex_replace(str, trim_r, "");
        if (str.empty())
            continue;
        else if (std::regex_match(str, links_r)) {
            parseLinks();
        } else {
            createChip(str);
        }
    }
}

void NTSCircuit::parseLinks()
{
    std::string str;
    std::regex comment_r("#.*");
    std::regex trim_r("^\\s*|\\s*$");
    std::regex chipsets_r("^\\.chipsets\\:$");

    while (getline(m_file, str)) {
        str = std::regex_replace(str, comment_r, "");
        str = std::regex_replace(str, trim_r, "");
        if (str.empty())
            continue;
        else if (std::regex_match(str, chipsets_r)) {
            parseChips();
        } else {
            createLink(str);
        }
    }
}

void NTSCircuit::parse()
{
    std::string str;
    std::regex comment_r("(#.*)");
    std::regex trim_r("^\\s*|\\s*$");
    std::regex links_r("^\\.links\\:$");
    std::regex chipsets_r("^\\.chipsets\\:$");

    while (getline(m_file, str)) {
        str = std::regex_replace(str, comment_r, "");
        str = std::regex_replace(str, trim_r, "");
        if (str.empty())
            continue;
        if (std::regex_match(str, chipsets_r)) {
            parseChips();
        } else if (std::regex_match(str, links_r))
            parseLinks();
        else
            throw std::runtime_error(
                "Error with parsing config file unreconized string: " + str);
    }
    link_components();
}

void NTSCircuit::link_components()
{
    for (auto link : m_links) {
        IComponent* from = nullptr;
        IComponent* to = nullptr;

        if (m_pins.find(link.name1) != m_pins.end())
            from = m_pins.at(link.name1);
        else if (m_ownedComponents.find(link.name1) != m_ownedComponents.end())
            from = m_ownedComponents.at(link.name1).get();

        if (m_pins.find(link.name2) != m_pins.end())
            to = m_pins.at(link.name2);
        else if (m_ownedComponents.find(link.name2) != m_ownedComponents.end())
            to = m_ownedComponents.at(link.name2).get();

        if (from == nullptr) {
            throw std::runtime_error("Not found component with name "
                + link.name1);
        }

        if (to == nullptr) {
            throw std::runtime_error("Not found component with name "
                + link.name2);
        }

        from->setLink(link.pin1, *to, link.pin2);
    }
}

void NTSCircuit::dump() const
{
    for (auto& c : m_ownedComponents) {
        std::cout << c.first << " ";
        c.second->dump();
    }
    AComponent::dump();
}

}
