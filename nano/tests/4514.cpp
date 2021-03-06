/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** 4013
*/

#include "assert_truth.hpp"
#include "nts/components/DecoderComponent.hpp"
#include "nts/NtsCircuit.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

Test(builtin_gates, decoder_gate)
{
    nts::DecoderComponent gate;

    std::vector<int> inputsPins = { 23, 2, 3, 22, 21 };
    std::vector<int> outputsPins = { 11, 10, 9, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15 };
    std::vector<std::vector<std::vector<nts::Tristate>>> truthTable = {
        { { U, U, U, U, U }, { U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U } },
        { { T, U, U, U, U }, { F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F } },
        { { F, F, F, F, F }, { T, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F } },
        { { F, F, F, F, T }, { F, T, F, F, F, F, F, F, F, F, F, F, F, F, F, F } },
        { { F, F, F, T, F }, { F, F, T, F, F, F, F, F, F, F, F, F, F, F, F, F } },
        { { F, F, F, T, T }, { F, F, F, T, F, F, F, F, F, F, F, F, F, F, F, F } },
        { { F, F, T, F, F }, { F, F, F, F, T, F, F, F, F, F, F, F, F, F, F, F } },
        { { F, F, T, F, T }, { F, F, F, F, F, T, F, F, F, F, F, F, F, F, F, F } },
        { { F, F, T, T, F }, { F, F, F, F, F, F, T, F, F, F, F, F, F, F, F, F } },
        { { F, F, T, T, T }, { F, F, F, F, F, F, F, T, F, F, F, F, F, F, F, F } },
        { { F, T, F, F, F }, { F, F, F, F, F, F, F, F, T, F, F, F, F, F, F, F } },
        { { F, T, F, F, T }, { F, F, F, F, F, F, F, F, F, T, F, F, F, F, F, F } },
        { { F, T, F, T, F }, { F, F, F, F, F, F, F, F, F, F, T, F, F, F, F, F } },
        { { F, T, F, T, T }, { F, F, F, F, F, F, F, F, F, F, F, T, F, F, F, F } },
        { { F, T, T, F, F }, { F, F, F, F, F, F, F, F, F, F, F, F, T, F, F, F } },
        { { F, T, T, F, T }, { F, F, F, F, F, F, F, F, F, F, F, F, F, T, F, F } },
        { { F, T, T, T, F }, { F, F, F, F, F, F, F, F, F, F, F, F, F, F, T, F } },
        { { F, T, T, T, T }, { F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, T } }
    };


    for (auto& test : truthTable) {
        auto &inputs = test[0];
        auto &outputs = test[1];
        size_t index = 0;

        for (nts::Tristate &pin : inputs) {
            gate.write(inputsPins[index++], pin);
        }
        stabilize(gate);
        index = 0;
        for (nts::Tristate &pin : outputs) {
            if (gate.read(outputsPins[index++]) != pin) {
                cr_assert_fail();
            }
        }
    }
}