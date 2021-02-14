/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** sr_latch
*/

#include "InputComponent.hpp"
#include "NTSCircuit.hpp"
#include "OutputComponent.hpp"
#include <criterion/criterion.h>
#include <cstddef>

Test(sr_latch, set_then_reset)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/srlatch.nts");
    nts::InputComponent is = nts::Tristate::FALSE;
    nts::InputComponent ir = nts::Tristate::FALSE;
    nts::OutputComponent out;

    auto step = [&]() {
        is.simulate(++tick);
        ir.simulate(++tick);
    };

    is.setLink(1, gate, 1);
    ir.setLink(1, gate, 2);
    gate.setLink(3, out, 1);

    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    is = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    is = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    ir = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    ir = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);
}
