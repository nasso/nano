/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** main
*/

#include "InputComponent.hpp"
#include "NorGate.hpp"
#include <iostream>

int main()
{
    nts::InputComponent iset = nts::Tristate::FALSE;
    nts::InputComponent ireset = nts::Tristate::FALSE;
    nts::NorGate a;
    nts::NorGate b;

    a.setLink(1, iset, 1);
    a.setLink(2, b, 3);
    b.setLink(1, a, 3);
    b.setLink(2, ireset, 1);

    std::cout << "simulate" << std::endl;
    b.simulate(1);
    std::cout << "a: ";
    a.dump();
    std::cout << "b: ";
    b.dump();

    iset = nts::Tristate::TRUE;

    std::cout << "set=1" << std::endl;
    b.simulate(4);
    std::cout << "a: ";
    a.dump();
    std::cout << "b: ";
    b.dump();

    iset = nts::Tristate::FALSE;

    std::cout << "set=0" << std::endl;
    b.simulate(5);
    std::cout << "a: ";
    a.dump();
    std::cout << "b: ";
    b.dump();

    ireset = nts::Tristate::TRUE;

    std::cout << "reset=1" << std::endl;
    b.simulate(2);
    std::cout << "a: ";
    a.dump();
    std::cout << "b: ";
    b.dump();

    ireset = nts::Tristate::FALSE;

    std::cout << "reset=0" << std::endl;
    b.simulate(3);
    std::cout << "a: ";
    a.dump();
    std::cout << "b: ";
    b.dump();
}
