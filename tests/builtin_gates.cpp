/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** logic_gates
*/

#include "AndGate.hpp"
#include "ConstComponent.hpp"
#include "NotGate.hpp"
#include "assert_truth.hpp"
#include <criterion/criterion.h>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

Test(builtin_gates, and_gate)
{
    nts::AndGate gate;

    assert_truth(gate, {
                           /*.inputs = */{ 1, 2 },
                           /*.outputs = */{ 3 },
                           /*.truthTable = */{
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
                       });
}

Test(builtin_gates, not_gate)
{
    nts::NotGate gate;

    assert_truth<1, 1>(gate, {
                                 /*.inputs = */{ 1 },
                                 /*.outputs = */{ 2 },
                                 /*.truthTable = */{
                                     { { U }, { U } },
                                     { { F }, { T } },
                                     { { T }, { F } },
                                 },
                             });
}

Test(builtin_gates, constants)
{
    nts::ConstComponent constants[] = { nts::TRUE, nts::FALSE, nts::UNDEFINED };

    cr_assert_eq(constants[0].compute(1), nts::TRUE);
    cr_assert_eq(constants[1].compute(1), nts::FALSE);
    cr_assert_eq(constants[2].compute(1), nts::UNDEFINED);
}
