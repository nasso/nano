/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** main
*/

#include "Relp.hpp"
#include <iostream>

static void usage(const std::string& name)
{
    std::cout << "usage: " << name << " <nts_file>" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2 || argv[1] == std::string("-h")) {
        usage(argv[0]);
        return (argc == 2 && argv[1] == std::string("-h") ? 0 : 84);
    }

    try {
        nts::MainCircuit circuit(argv[1]);

        Relp::run(circuit);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return (84);
    }

    return (0);
}
