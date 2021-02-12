/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** NTSCircuit
*/

#ifndef NTSCIRCUIT_HPP_
#define NTSCIRCUIT_HPP_

#include "Circuit.hpp"
#include "MultiComponentFactory.hpp"
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

namespace nts {
class NTSCircuit : public Circuit {
public:
    NTSCircuit(std::string filename);
    ~NTSCircuit();

protected:
private:
    struct Link {
        std::string name1;
        std::string name2;
        size_t pin1;
        size_t pin2;
    };

    void parse();
    void parse_chips();
    void parse_links();
    void create_chip(std::string&);
    void create_link(std::string&);
    void link_component();
    std::ifstream m_file;
    std::unordered_map<std::string, std::unique_ptr<IComponent>> m_components;
    std::vector<Link> m_links;
    MultiComponentFactory m_factory;
};
}

#endif /* !NTSCIRCUIT_HPP_ */
