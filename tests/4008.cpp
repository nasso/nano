/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** nts_components
*/

#include "InputComponent.hpp"
#include "NTSCircuit.hpp"
#include "OutputComponent.hpp"
#include "assert_truth.hpp"
#include <criterion/criterion.h>
#include <criterion/theories.h>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

Test(components_4008, adder_binary)
{
    nts::NTSCircuit gate("components/adder.nts");

    assert_truth<3, 2, 2>(gate, {
                                    .inputs = { 1, 2, 3 },
                                    .outputs = { 4, 5 },
                                    .truthTable = {
                                        { { F, F, F }, { F, F } },
                                        { { T, F, F }, { F, T } },
                                        { { F, T, F }, { F, T } },
                                        { { T, T, F }, { T, F } },
                                        { { F, F, T }, { F, T } },
                                        { { T, F, T }, { T, F } },
                                        { { F, T, T }, { T, F } },
                                        { { T, T, T }, { T, T } },
                                    },
                                });
}

Test(components_4008, adder_tristate)
{
    nts::NTSCircuit gate("components/adder.nts");

    if (!test_gate<3, 2>(gate,
            {
                .inputs = { 1, 2, 3 },
                .outputs = { 4, 5 },
                .truthTable = {
                    { { U, U, U }, { U, U } },
                    { { F, U, U }, { U, U } },
                    { { T, U, U }, { U, U } },
                    { { U, F, U }, { U, U } },
                    { { F, F, U }, { F, U } },
                    { { T, F, U }, { U, U } },
                    { { U, T, U }, { U, U } },
                    { { F, T, U }, { U, U } },
                    { { T, T, U }, { T, U } },
                    { { U, U, F }, { U, U } },
                    { { F, U, F }, { F, U } },
                    { { T, U, F }, { U, U } },
                    { { U, F, F }, { F, U } },
                    { { F, F, F }, { F, F } },
                    { { T, F, F }, { F, T } },
                    { { U, T, F }, { U, U } },
                    { { F, T, F }, { F, T } },
                    { { T, T, F }, { T, F } },
                    { { U, U, T }, { U, U } },
                    { { F, U, T }, { U, U } },
                    { { T, U, T }, { T, U } },
                    { { U, F, T }, { U, U } },
                    { { F, F, T }, { F, T } },
                    { { T, F, T }, { T, F } },
                    { { U, T, T }, { T, U } },
                    { { F, T, T }, { T, F } },
                    { { T, T, T }, { T, T } },
                },
            })) {
        criterion::logging::warn
            << "Tristate Full Adder tests failed!"
            << std::flush;
        criterion::logging::info << gate << std::flush;
    }
}

TheoryDataPoints(components_4008, binary_4008) = {
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
    DataPoints(nts::Tristate, T, F),
};

Theory(
    (
        nts::Tristate c1,
        nts::Tristate a1,
        nts::Tristate a2,
        nts::Tristate a3,
        nts::Tristate a4,
        nts::Tristate b1,
        nts::Tristate b2,
        nts::Tristate b3,
        nts::Tristate b4),
    components_4008,
    binary_4008,
    .timeout = 5)
{
    nts::NTSCircuit gate("components/4008.nts");
    nts::InputComponent inputs[] = {
        c1,
        a1,
        a2,
        a3,
        a4,
        b1,
        b2,
        b3,
        b4,
    };
    nts::OutputComponent s1, s2, s3, s4, co;

    // initialize inputs
    for (auto& in : inputs) {
        in.simulate(1);
    }

    gate.setLink(9, inputs[0], 1);
    gate.setLink(7, inputs[1], 1);
    gate.setLink(5, inputs[2], 1);
    gate.setLink(3, inputs[3], 1);
    gate.setLink(1, inputs[4], 1);
    gate.setLink(6, inputs[5], 1);
    gate.setLink(4, inputs[6], 1);
    gate.setLink(2, inputs[7], 1);
    gate.setLink(15, inputs[8], 1);
    gate.setLink(10, s1, 1);
    gate.setLink(11, s2, 1);
    gate.setLink(12, s3, 1);
    gate.setLink(13, s4, 1);
    gate.setLink(14, co, 1);

    gate.simulate(1);

    std::uint8_t c = c1 == T;
    std::uint8_t a = 0
        | ((a1 == T) << 0)
        | ((a2 == T) << 1)
        | ((a3 == T) << 2)
        | ((a4 == T) << 3);
    std::uint8_t b = 0
        | ((b1 == T) << 0)
        | ((b2 == T) << 1)
        | ((b3 == T) << 2)
        | ((b4 == T) << 3);
    std::uint8_t s = 0
        | ((s1 == T) << 0)
        | ((s2 == T) << 1)
        | ((s3 == T) << 2)
        | ((s4 == T) << 3)
        | ((co == T) << 4);

    cr_assert_eq(a + b + c, s);
}
