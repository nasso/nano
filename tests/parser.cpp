/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** parser
*/

#include "assert_truth.hpp"
#include "nts/NtsCircuit.hpp"
#include <criterion/criterion.h>
#include <sstream>

const auto U = nts::Tristate::UNDEFINED;
const auto F = nts::Tristate::FALSE;
const auto T = nts::Tristate::TRUE;

const GateSpec<2, 1> AND_GATE_SPEC = {
    // inputs
    { 1, 2 },
    // outputs
    { 3 },
    // truth table
    {
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
    // inputs
    { 1, 2 },
    // outputs
    { 3 },
    // truthtable
    {
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

Test(nts_parser, simple_and_gate)
{
    std::istringstream source(
        ".chipsets:\n"
        "input a\n"
        "input b\n"
        "output c\n"
        "and and\n"
        "\n"
        ".links:\n"
        "a:1 and:1\n"
        "b:1 and:2\n"
        "c:1 and:3\n");

    nts::NtsCircuit circuit(source);

    assert_truth(circuit, AND_GATE_SPEC);
}

Test(nts_parser, buffer)
{
    std::istringstream source(
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        "\n"
        ".links:\n"
        "a:1 b:1\n");

    nts::NtsCircuit circuit(source);

    assert_truth<1, 1>(
        circuit,
        {
            { 1 },
            { 2 },
            {
                { { U }, { U } },
                { { F }, { F } },
                { { T }, { T } },
            },
        });
}

Test(nts_parser, clock)
{
    std::istringstream source(
        ".chipsets:\n"
        "clock a\n"
        "output b\n"
        "\n"
        ".links:\n"
        "a:1 b:1\n");

    nts::NtsCircuit circuit(source);

    circuit.simulate();
    cr_assert_eq(circuit.read(2), U);

    circuit.simulate();
    cr_assert_eq(circuit.read(2), U);

    circuit.write(1, T);
    circuit.simulate();
    cr_assert_eq(circuit.read(2), T);

    circuit.simulate();
    cr_assert_eq(circuit.read(2), F);

    circuit.simulate();
    cr_assert_eq(circuit.read(2), T);

    circuit.write(1, T);
    circuit.simulate();
    cr_assert_eq(circuit.read(2), T);

    circuit.simulate();
    cr_assert_eq(circuit.read(2), F);
}
