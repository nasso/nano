/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** nts_gates
*/

#include "NTSCircuit.hpp"
#include "assert_truth.hpp"
#include <criterion/criterion.h>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

Test(logic_gates, nor_gate)
{
    nts::NTSCircuit gate("components/nor.nts");

    assert_truth(gate, {
                           .inputs = { 1, 2 },
                           .outputs = { 3 },
                           .truthTable = {
                               { { U, U }, { U } },
                               { { U, F }, { U } },
                               { { U, T }, { F } },
                               { { F, U }, { U } },
                               { { F, F }, { T } },
                               { { F, T }, { F } },
                               { { T, U }, { F } },
                               { { T, F }, { F } },
                               { { T, T }, { F } },
                           },
                       });
}

Test(logic_gates, nand_gate)
{
    nts::NTSCircuit gate("components/nand.nts");

    assert_truth(gate, {
                           .inputs = { 1, 2 },
                           .outputs = { 3 },
                           .truthTable = {
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
                       });
}
