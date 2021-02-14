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

Test(latch, sr_latch)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/srlatch.nts");
    nts::InputComponent is = nts::Tristate::FALSE;
    nts::InputComponent ir = nts::Tristate::FALSE;
    nts::OutputComponent out;

    auto step = [&]() {
        tick++;
        is.simulate(tick);
        ir.simulate(tick);
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

Test(latch, data_latch)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/dlatch.nts");
    nts::InputComponent idata = nts::Tristate::FALSE;
    nts::InputComponent istore = nts::Tristate::FALSE;
    nts::OutputComponent out;

    auto step = [&]() {
        tick++;
        idata.simulate(tick);
        istore.simulate(tick);
    };

    idata.setLink(1, gate, 1);
    istore.setLink(1, gate, 2);
    gate.setLink(3, out, 1);

    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    idata = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    istore = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    idata = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    istore = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    istore = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);
}
