/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** NTSCircuit
*/

#include "NTSCircuit.hpp"
#include <iostream>
#include <regex>

nts::NTSCircuit::NTSCircuit(std::string filename)
    : m_file(filename)
{
    if (!m_file.is_open())
        throw std::runtime_error("Error");
    parse();
}

nts::NTSCircuit::~NTSCircuit()
{
    m_file.close();
}

void nts::NTSCircuit::create_chip(std::string& str)
{
    std::regex component_type("\\w+");
    std::string name;
    std::string type;
    std::vector<std::string> res;

    for (std::sregex_iterator it(str.begin(), str.end(), component_type), it_end; it != it_end; ++it)
        res.push_back((*it)[0]);
    if (res.size() != 2)
        throw std::runtime_error("Error with parsing config file unreconized string: " + str);
    name = res[0];
    type = res[1];
    // m_components[name] = ComponentFactory::createComponent(type)
}

void nts::NTSCircuit::create_link(std::string& str)
{
    std::regex components_r("(\\w+\\:[0-9]+)");
    std::regex component_r("\\w+");
    std::string tmp_str;
    std::vector<std::vector<std::string>> components;
    Link link;

    for (std::sregex_iterator it(str.begin(), str.end(), components_r), it_end; it != it_end; ++it) {
        std::vector<std::string> tmp;
        tmp_str = (*it)[0];
        for (std::sregex_iterator it2(tmp_str.begin(), tmp_str.end(), component_r), it2_end; it2 != it2_end; ++it2)
            tmp.push_back((*it2)[0]);
        components.push_back(tmp);
    }
    if (components.size() != 2 || components[0].size() != 2 || components[1].size() != 2)
        throw std::runtime_error("Error with parsing config file unreconized string: " + str);
    link.name1 = components[1][0];
    link.pin1 = stoi(components[1][1]);
    link.name2 = components[0][0];
    link.pin2 = stoi(components[0][1]);
    m_links.push_back(link);
}

void nts::NTSCircuit::parse_chips()
{
    std::string str;
    std::regex comment_r("(#.*)");
    std::regex trim_r("^(\\s*\\t*\\n*)");
    std::regex links_r("(\\.links\\:\\s*\t*\n*)");

    while (getline(m_file, str)) {
        str = std::regex_replace(str, comment_r, "");
        str = std::regex_replace(str, trim_r, "");
        if (str.empty())
            continue;
        else if (std::regex_match(str, links_r)) {
            parse_links();
        } else {
            create_chip(str);
        }
    }
}

void nts::NTSCircuit::parse_links()
{
    std::string str;
    std::regex comment_r("(#.*)");
    std::regex trim_r("^(\\s*\\t*\\n*)");
    std::regex chipsets_r("(\\.chipsets\\:\\s*\t*\n)");

    while (getline(m_file, str)) {
        str = std::regex_replace(str, comment_r, "");
        str = std::regex_replace(str, trim_r, "");
        if (str.empty())
            continue;
        else if (std::regex_match(str, chipsets_r)) {
            parse_chips();
        } else {
            create_link(str);
        }
    }
}

void nts::NTSCircuit::parse()
{
    std::string str;
    std::regex comment_r("(#.*)");
    std::regex links_r("(\\.links\\:\\s*\\t*\\n)");
    std::regex trim_r("^(\\s*\\t*\\n*)");
    std::regex chipsets_r("\\.chipsets\\:\\s*\\t*\\n*");

    while (getline(m_file, str)) {
        str = std::regex_replace(str, comment_r, "");
        str = std::regex_replace(str, trim_r, "");
        if (str.empty())
            continue;
        if (std::regex_match(str, chipsets_r)) {
            parse_chips();
        } else if (std::regex_match(str, links_r))
            parse_links();
        else
            throw std::runtime_error("Error with parsing config file unreconized string: " + str);
    }
    link_component();
}

void nts::NTSCircuit::link_component()
{
    for (auto link : m_links) {
        if (m_components.find(link.name1) == m_components.end())
            throw std::runtime_error("Not found component with name " + link.name1);
        if (m_components.find(link.name2) == m_components.end())
            throw std::runtime_error("Not found component with name " + link.name2);
        m_components[link.name1]->setLink(link.pin1, *m_components[link.name2], link.pin2);
    }
}