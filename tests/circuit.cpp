/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** circuit
*/

#include "Circuit.hpp"
#include "AndGate.hpp"
#include "NotGate.hpp"
#include "StaticPinoutBuffer.hpp"
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
    cr_assert(pinout.at(1) & nts::PinUsage::INPUT);
    cr_assert(pinout.at(2) & nts::PinUsage::INPUT);
    cr_assert(pinout.at(3) & nts::PinUsage::OUTPUT);
    cr_assert_eq(pinout.size(), 3);
}

Test(circuit, single_component_simulate)
{
    nts::Circuit<std::string> circuit;
    std::unique_ptr<nts::AndGate> and_gate(new nts::AndGate);

    circuit.insert("and", std::move(and_gate));
    circuit.connect(1, "and", 1);
    circuit.connect(2, "and", 2);
    circuit.connect(3, "and", 3);

    nts::StaticPinoutBuffer pbuf({
        { 1, nts::Tristate::FALSE },
        { 2, nts::Tristate::TRUE },
        { 3, nts::Tristate::UNDEFINED },
    });
    circuit.simulate(pbuf);
    cr_assert_eq(pbuf.read(3), nts::Tristate::FALSE);
    pbuf.write(1, nts::Tristate::TRUE);
    circuit.simulate(pbuf);
    cr_assert_eq(pbuf.read(3), nts::Tristate::TRUE);
}
