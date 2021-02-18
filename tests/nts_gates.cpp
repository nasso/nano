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

Test(logic_gates, nand)
{
    nts::NTSCircuit gate("components/nand.nts");

    assert_truth(gate, {
                           /*.inputs = */{ 1, 2 },
                           /*.outputs = */{ 3 },
                           /*.truthTable = */{
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

Test(logic_gates, nor)
{
    nts::NTSCircuit gate("components/nor.nts");

    assert_truth(gate, {
                           /*.inputs = */{ 1, 2 },
                           /*.outputs = */{ 3 },
                           /*.truthTable = */{
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

Test(logic_gates, or)
{
    nts::NTSCircuit gate("components/or.nts");

    assert_truth(gate, {
                           /*.inputs = */{ 1, 2 },
                           /*.outputs = */{ 3 },
                           /*.truthTable = */{
                               { { U, U }, { U } },
                               { { U, F }, { U } },
                               { { U, T }, { T } },
                               { { F, U }, { U } },
                               { { F, F }, { F } },
                               { { F, T }, { T } },
                               { { T, U }, { T } },
                               { { T, F }, { T } },
                               { { T, T }, { T } },
                           },
                       });
}

Test(logic_gates, xor)
{
    nts::NTSCircuit gate("components/xor.nts");

    assert_truth(gate, {
                           /*.inputs = */{ 1, 2 },
                           /*.outputs = */{ 3 },
                           /*.truthTable = */{
                               { { U, U }, { U } },
                               { { U, F }, { U } },
                               { { U, T }, { U } },
                               { { F, U }, { U } },
                               { { F, F }, { F } },
                               { { F, T }, { T } },
                               { { T, U }, { U } },
                               { { T, F }, { T } },
                               { { T, T }, { F } },
                           },
                       });
}

Test(logic_gates, xnor)
{
    nts::NTSCircuit gate("components/xnor.nts");

    assert_truth(gate, {
                           /*.inputs = */{ 1, 2 },
                           /*.outputs = */{ 3 },
                           /*.truthTable = */{
                               { { U, U }, { U } },
                               { { U, F }, { U } },
                               { { U, T }, { U } },
                               { { F, U }, { U } },
                               { { F, F }, { T } },
                               { { F, T }, { F } },
                               { { T, U }, { U } },
                               { { T, F }, { F } },
                               { { T, T }, { T } },
                           },
                       });
}

Test(logic_gates, multiplexer)
{
    nts::NTSCircuit gate("components/mux.nts");

    assert_truth<3>(gate, {
                              /*.inputs = */{ 1, 2, 3 },
                              /*.outputs = */{ 4 },
                              /*.truthTable = */{
                                  { { U, U, U }, { U } },
                                  { { U, U, F }, { U } },
                                  { { U, U, T }, { U } },
                                  { { U, F, U }, { U } },
                                  { { U, F, F }, { U } },
                                  { { U, F, T }, { F } },
                                  { { U, T, U }, { U } },
                                  { { U, T, F }, { U } },
                                  { { U, T, T }, { T } },
                                  { { F, U, U }, { U } },
                                  { { F, U, F }, { F } },
                                  { { F, U, T }, { U } },
                                  { { F, F, U }, { F } },
                                  { { F, F, F }, { F } },
                                  { { F, F, T }, { F } },
                                  { { F, T, U }, { U } },
                                  { { F, T, F }, { F } },
                                  { { F, T, T }, { T } },
                                  { { T, U, U }, { U } },
                                  { { T, U, F }, { T } },
                                  { { T, U, T }, { U } },
                                  { { T, F, U }, { U } },
                                  { { T, F, F }, { T } },
                                  { { T, F, T }, { F } },
                                  { { T, T, U }, { T } },
                                  { { T, T, F }, { T } },
                                  { { T, T, T }, { T } },
                              },
                          });
}

Test(logic_gates, and3)
{
    nts::NTSCircuit gate("components/and3.nts");

    assert_truth<3>(gate, {
                              /*.inputs = */{ 1, 2, 3 },
                              /*.outputs = */{ 4 },
                              /*.truthTable = */{
                                  { { U, U, U }, { U } },
                                  { { U, U, F }, { F } },
                                  { { U, U, T }, { U } },
                                  { { U, F, U }, { F } },
                                  { { U, F, F }, { F } },
                                  { { U, F, T }, { F } },
                                  { { U, T, U }, { U } },
                                  { { U, T, F }, { F } },
                                  { { U, T, T }, { U } },
                                  { { F, U, U }, { F } },
                                  { { F, U, F }, { F } },
                                  { { F, U, T }, { F } },
                                  { { F, F, U }, { F } },
                                  { { F, F, F }, { F } },
                                  { { F, F, T }, { F } },
                                  { { F, T, U }, { F } },
                                  { { F, T, F }, { F } },
                                  { { F, T, T }, { F } },
                                  { { T, U, U }, { U } },
                                  { { T, U, F }, { F } },
                                  { { T, U, T }, { U } },
                                  { { T, F, U }, { F } },
                                  { { T, F, F }, { F } },
                                  { { T, F, T }, { F } },
                                  { { T, T, U }, { U } },
                                  { { T, T, F }, { F } },
                                  { { T, T, T }, { T } },
                              },
                          });
}
