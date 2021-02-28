/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** nts_components
*/

#include "assert_truth.hpp"
#include "nts/NtsCircuit.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>
#include <criterion/theories.h>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

Test(components_4008, adder_binary)
{
    auto gate = loadNts("components/adder.nts", { "components" });

    assert_truth<3, 2, 2>(gate, {
                                    /*.inputs = */ { 1, 2, 3 },
                                    /*.outputs = */ { 4, 5 },
                                    /*.truthTable = */ {
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

// maybe FIXME
Test(components_4008, adder_tristate, .disabled = true)
{
    auto gate = loadNts("components/adder.nts", { "components" });

    if (!test_gate<3, 2>(gate,
            {
                /*.inputs = */ { 1, 2, 3 },
                /*.outputs = */ { 4, 5 },
                /*.truthTable = */ {
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
    .disabled = true,
    .timeout = 10)
{
    auto gate = loadNts("components/4008.nts", { "components" });

    gate.write(9, c1);
    gate.write(7, a1);
    gate.write(5, a2);
    gate.write(3, a3);
    gate.write(1, a4);
    gate.write(6, b1);
    gate.write(4, b2);
    gate.write(2, b3);
    gate.write(15, b4);

    gate.simulate();

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
        | ((gate.read(10) == T) << 0)
        | ((gate.read(11) == T) << 1)
        | ((gate.read(12) == T) << 2)
        | ((gate.read(13) == T) << 3)
        | ((gate.read(14) == T) << 4);

    cr_assert_eq(a + b + c, s);
}
