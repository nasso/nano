/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** logic_gates
*/

#include "assert_truth.hpp"
#include "nts/AndGate.hpp"
#include "nts/ConstComponent.hpp"
#include "nts/NotGate.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

Test(builtin_gates, and_gate)
{
    nts::AndGate gate;

    assert_truth(gate, {
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
                       });
}

Test(builtin_gates, not_gate)
{
    nts::NotGate gate;

    assert_truth<1, 1>(
        gate,
        {
            /*.inputs = */ { 1 },
            /*.outputs = */ { 2 },
            /*.truthTable = */ {
                { { U }, { U } },
                { { F }, { T } },
                { { T }, { F } },
            },
        });
}

Test(builtin_gates, constants)
{
    nts::ConstComponent constants[] = {
        nts::Tristate::TRUE,
        nts::Tristate::FALSE,
        nts::Tristate::UNDEFINED,
    };

    stabilize(constants[0]);
    cr_assert_eq(constants[0].read(1), nts::Tristate::TRUE);
    stabilize(constants[1]);
    cr_assert_eq(constants[1].read(1), nts::Tristate::FALSE);
    stabilize(constants[2]);
    cr_assert_eq(constants[2].read(1), nts::Tristate::UNDEFINED);
}
