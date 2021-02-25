/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** circuit
*/

#include "Circuit.hpp"
#include "AndGate.hpp"
#include "NotGate.hpp"
#include "assert_truth.hpp"
#include <criterion/criterion.h>
#include <memory>

const auto U = nts::Tristate::UNDEFINED;
const auto F = nts::Tristate::FALSE;
const auto T = nts::Tristate::TRUE;

const GateSpec<2, 1> AND_GATE_SPEC = {
    /*.inputs = */ { 1, 2 },
    /*.outputs = */ { 3 },
    /*.truthTable = */ {
        { { U, U }, { U } },
        { { U, F }, { F } },
        { { U, T }, { U } },
        { { F, U }, { F } },
        { { F, F }, { F } },
        { { F, T }, { F } },
        { { T, U }, { U } },
        { { T, F }, { F } },
        { { T, T }, { T } },
    },
};

const GateSpec<2, 1> NAND_GATE_SPEC = {
    /*.inputs = */ { 1, 2 },
    /*.outputs = */ { 3 },
    /*.truthTable = */ {
        { { U, U }, { U } },
        { { U, F }, { T } },
        { { U, T }, { U } },
        { { F, U }, { T } },
        { { F, F }, { T } },
        { { F, T }, { T } },
        { { T, U }, { U } },
        { { T, F }, { T } },
        { { T, T }, { F } },
    },
};

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

    assert_truth(circuit, AND_GATE_SPEC);
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

    assert_truth(circuit, NAND_GATE_SPEC);
}

Test(circuit, remove_component)
{
    nts::Circuit<std::string> circuit;
    auto and_gate_ptr = new nts::AndGate;
    std::unique_ptr<nts::IComponent> and_gate(and_gate_ptr);

    circuit.insert("and", std::move(and_gate));

    and_gate = circuit.remove("and");

    cr_assert_eq(and_gate.get(), and_gate_ptr);
}

Test(circuit, remove_link_pinout)
{
    nts::Circuit<std::string> circuit;
    std::unique_ptr<nts::AndGate> and_gate(new nts::AndGate);
    std::unique_ptr<nts::IComponent> not_gate(new nts::NotGate);

    circuit.insert("and", std::move(and_gate));
    circuit.connect(1, "and", 1);
    circuit.connect(2, "and", 2);
    circuit.connect(3, "and", 3);
    circuit.disconnect(3, "and", 3);

    auto pinout = circuit.pinout();
    cr_assert(pinout.at(1) & nts::PinMode::INPUT);
    cr_assert(pinout.at(2) & nts::PinMode::INPUT);
    cr_assert_eq(pinout.size(), 2);
}

Test(circuit, remove_then_relink)
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
    circuit.connect(3, "and", 3);
    circuit.disconnect(3, "not", 2);
    assert_truth(circuit, AND_GATE_SPEC);

    circuit.connect(3, "not", 2);
    circuit.disconnect(3, "and", 3);
    assert_truth(circuit, NAND_GATE_SPEC);
}
