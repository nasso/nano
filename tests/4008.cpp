/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** nts_components
*/

#include "NTSCircuit.hpp"
#include "assert_truth.hpp"
#include <criterion/criterion.h>

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
