/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** circuit
*/

#include "Circuit.hpp"
#include "AndGate.hpp"
#include "NotGate.hpp"
#include <criterion/criterion.h>
#include <memory>

Test(circuit, empty)
{
    nts::Circuit<int> circuit;
}

Test(circuit, single_component)
{
    nts::Circuit<std::string> circuit;
    auto and_gate_ptr = new nts::AndGate;
    std::unique_ptr<nts::AndGate> and_gate(and_gate_ptr);

    circuit.insert("and", std::move(and_gate));
    cr_assert_eq(&circuit["and"], and_gate_ptr);
}

Test(circuit, single_component_pinout)
{
    nts::Circuit<std::string> circuit;
    std::unique_ptr<nts::AndGate> and_gate(new nts::AndGate);

    circuit.insert("and", std::move(and_gate));
    circuit.connect(1, "and", 1);
    circuit.connect(2, "and", 2);
    circuit.connect(3, "and", 3);

    auto pinout = circuit.pinout();
    cr_assert(pinout.at(1) & nts::PinMode::INPUT);
    cr_assert(pinout.at(2) & nts::PinMode::INPUT);
    cr_assert(pinout.at(3) & nts::PinMode::OUTPUT);
    cr_assert_eq(pinout.size(), 3);
}

Test(circuit, single_component_simulation)
{
    nts::Circuit<std::string> circuit;
    std::unique_ptr<nts::AndGate> and_gate(new nts::AndGate);

    circuit.insert("and", std::move(and_gate));
    circuit.connect(1, "and", 1);
    circuit.connect(2, "and", 2);
    circuit.connect(3, "and", 3);

    circuit.write(1, nts::Tristate::FALSE);
    circuit.write(2, nts::Tristate::TRUE);
    circuit.simulate();
    cr_assert_eq(circuit.read(3), nts::Tristate::FALSE);

    circuit.write(1, nts::Tristate::TRUE);
    circuit.simulate();
    cr_assert_eq(circuit.read(3), nts::Tristate::TRUE);
}

Test(circuit, multi_component_simulation)
{
    nts::Circuit<std::string> circuit;
    std::unique_ptr<nts::IComponent> and_gate(new nts::AndGate);
    std::unique_ptr<nts::IComponent> not_gate(new nts::NotGate);

    circuit.insert("and", std::move(and_gate));
    circuit.insert("not", std::move(not_gate));
    circuit.connect(1, "and", 1);
    circuit.connect(2, "and", 2);
    circuit.connect("and", 3, "not", 1);
    circuit.connect(3, "not", 2);

    circuit.write(1, nts::Tristate::FALSE);
    circuit.write(2, nts::Tristate::TRUE);
    circuit.simulate();
    cr_assert_eq(circuit.read(3), nts::Tristate::TRUE);

    circuit.write(1, nts::Tristate::TRUE);
    circuit.simulate();
    cr_assert_eq(circuit.read(3), nts::Tristate::FALSE);

    circuit.write(1, nts::Tristate::UNDEFINED);
    circuit.simulate();
    cr_assert_eq(circuit.read(3), nts::Tristate::UNDEFINED);
}
