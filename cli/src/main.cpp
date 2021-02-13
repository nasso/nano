/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** main
*/

#include "InputComponent.hpp"
#include "NTSCircuit.hpp"
#include "NorGate.hpp"
#include <iostream>

int main()
{
    // std::size_t tick = 0;
    // nts::InputComponent iset = nts::Tristate::FALSE;
    // nts::InputComponent ireset = nts::Tristate::FALSE;
    // nts::NorGate a;
    // nts::NorGate b;

    // a.setLink(1, iset, 1);
    // a.setLink(2, b, 3);
    // b.setLink(1, a, 3);
    // b.setLink(2, ireset, 1);

    // std::cout << "simulate" << std::endl;
    // iset.simulate(++tick);
    // ireset.simulate(++tick);
    // std::cout << "a: ";
    // a.dump();
    // std::cout << "b: ";
    // b.dump();

    // iset = nts::Tristate::TRUE;

    // std::cout << "set=1" << std::endl;
    // iset.simulate(++tick);
    // ireset.simulate(++tick);
    // std::cout << "a: ";
    // a.dump();
    // std::cout << "b: ";
    // b.dump();

    // iset = nts::Tristate::FALSE;

    // std::cout << "set=0" << std::endl;
    // iset.simulate(++tick);
    // ireset.simulate(++tick);
    // std::cout << "a: ";
    // a.dump();
    // std::cout << "b: ";
    // b.dump();

    // ireset = nts::Tristate::TRUE;

    // std::cout << "reset=1" << std::endl;
    // iset.simulate(++tick);
    // ireset.simulate(++tick);
    // std::cout << "a: ";
    // a.dump();
    // std::cout << "b: ";
    // b.dump();

    // ireset = nts::Tristate::FALSE;

    // std::cout << "reset=0" << std::endl;
    // iset.simulate(++tick);
    // ireset.simulate(++tick);
    // std::cout << "a: ";
    // a.dump();
    // std::cout << "b: ";
    // b.dump();

    try {
        nts::InputComponent inputs[8] = {
            nts::Tristate::TRUE,
            nts::Tristate::TRUE,
            nts::Tristate::FALSE,
            nts::Tristate::FALSE,
            nts::Tristate::UNDEFINED,
            nts::Tristate::FALSE,
            nts::Tristate::TRUE,
            nts::Tristate::UNDEFINED,
        };
        nts::NTSCircuit m("4081_and.nts");

        std::size_t i = 0;
        m.setLink(1, inputs[i++], 1);
        m.setLink(2, inputs[i++], 1);
        m.setLink(5, inputs[i++], 1);
        m.setLink(6, inputs[i++], 1);
        m.setLink(7, inputs[i++], 1);
        m.setLink(8, inputs[i++], 1);
        m.setLink(11, inputs[i++], 1);
        m.setLink(12, inputs[i++], 1);

        std::size_t tick = 0;
        for (auto& in : inputs) {
            in.simulate(++tick);
        }

        m.dump();
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}
