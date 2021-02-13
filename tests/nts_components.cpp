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

Test(components, sum)
{
    nts::NTSCircuit gate("components/sum.nts");

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
