/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** MainCircuit
*/

#include "MainCircuit.hpp"
#include <iostream>

nts::MainCircuit::MainCircuit(const std::string& filename)
    : NTSCircuit(filename)
{
    m_tick = 0;
}

nts::MainCircuit::~MainCircuit()
{
}

void nts::MainCircuit::setInputPin(const std::string& name, nts::Tristate state)
{
    if (m_pins.find(name) == m_pins.end()) {
        std::cout << "Component " << name << " doesn't exist" << std::endl;
        return;
    }
    if (!dynamic_cast<const nts::InputComponent*>(m_pins[name])) {
        std::cout << "Component " << name << " is not an input" << std::endl;
        return;
    }
    nts::InputComponent& input = *dynamic_cast<nts::InputComponent*>(m_pins[name]);
    input = state;
}

void nts::MainCircuit::display() const
{
    std::cout << "tick: " << m_tick << std::endl;
    std::cout << "input(s):" << std::endl;
    for (auto& pin : m_pins) {
        if (dynamic_cast<const nts::InputComponent*>(pin.second)) {
            std::cout << "\t" << pin.first << ": " << pin.second->compute(1) << std::endl;
        }
    }
    std::cout << "output(s):" << std::endl;
    for (auto& pin : m_pins) {
        if (dynamic_cast<const nts::OutputComponent*>(pin.second)) {
            std::cout << "\t" << pin.first << ": " << pin.second->compute(1) << std::endl;
        }
    }
}

void nts::MainCircuit::simulate()
{
    nts::InputComponent* input;

    m_tick++;
    for (auto& pin : m_pins) {
        input = dynamic_cast<nts::InputComponent*>(pin.second);
        if (input)
            input->simulate(m_tick);
    }
}
