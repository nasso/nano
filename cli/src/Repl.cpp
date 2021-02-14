/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Relp
*/

#include "IInputComponent.hpp"
#include "Relp.hpp"
#include <iostream>
#include <regex>
#include <signal.h>
#include <string>

bool Relp::m_stopLoop = false;

void dump(const nts::MainCircuit& circuit)
{
    circuit.dump();
}

void display(const nts::MainCircuit& circuit)
{
    circuit.display();
}

void loop(nts::MainCircuit& circuit)
{
    signal(SIGINT, [](int) {
        Relp::m_stopLoop = true;
    });
    while (!Relp::m_stopLoop) {
        circuit.simulate();
        circuit.display();
    }
    signal(SIGINT, NULL);
}

void simulate(nts::MainCircuit& circuit)
{
    circuit.simulate();
}

void set_component(nts::MainCircuit& circuit, std::string component, std::string value)
{
    std::regex trim_r("^\\s*|\\s*$");

    component = std::regex_replace(component, trim_r, "");
    value = std::regex_replace(value, trim_r, "");

    if (value == "0")
        circuit.setInputPin(component, nts::FALSE);
    else if (value == "1")
        circuit.setInputPin(component, nts::TRUE);
    else if (value == "U")
        circuit.setInputPin(component, nts::UNDEFINED);
    else
        std::cout << "Value: " << value << " is not a valid value (must be 0, 1 or U)" << std::endl;
}

bool exec(nts::MainCircuit& circuit, std::string input)
{
    if (input == "exit") {
        return 1;
    } else if (input == "display") {
        display(circuit);
    } else if (input == "simulate") {
        simulate(circuit);
    } else if (input == "loop") {
        loop(circuit);
    } else if (input == "dump") {
        dump(circuit);
    } else if (std::regex_match(input, std::regex("\\w+\\s*\\t*=\\s*\\t*.+"))) {
        set_component(circuit, input.substr(0, input.find("=")), input.substr(input.find("=") + 1, input.length()));
    } else {
        std::cout << "Unknown command " + input << std::endl;
    }
    return 0;
}

void Relp::run(nts::MainCircuit& circuit)
{
    std::string input;

    std::cout << "> ";
    while (std::getline(std::cin, input)) {
        if (exec(circuit, input))
            return;
        std::cout << "> ";
    }
}