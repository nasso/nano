/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** main
*/

#include "Relp.hpp"
#include <iostream>

int main()
{
    try {
        nts::MainCircuit circuit("test.nts");

        Relp::run(circuit);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return (84);
    }
    return (0);
}
