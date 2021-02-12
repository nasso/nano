/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** sr_latch
*/

#include "InputComponent.hpp"
#include "NorGate.hpp"
#include <criterion/criterion.h>
#include <cstddef>

Test(sr_latch, set_then_reset)
{
    std::size_t tick = 0;
    nts::InputComponent is = nts::Tristate::FALSE;
    nts::InputComponent ir = nts::Tristate::FALSE;
    nts::NorGate b;
    nts::NorGate q;

    auto step = [&]() {
        tick++;
        is.simulate(tick);
        ir.simulate(tick);
    };

    cr_assert_eq(is.compute(1), nts::Tristate::UNDEFINED);
    cr_assert_eq(ir.compute(1), nts::Tristate::UNDEFINED);
    cr_assert_eq(b.compute(3), nts::Tristate::UNDEFINED);
    cr_assert_eq(q.compute(3), nts::Tristate::UNDEFINED);

    is.setLink(1, b, 1);
    ir.setLink(1, q, 2);
    b.setLink(3, q, 1);
    q.setLink(3, b, 2);

    step();
    cr_assert_eq(is.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(ir.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(b.compute(3), nts::Tristate::TRUE);
    cr_assert_eq(q.compute(3), nts::Tristate::FALSE);

    is = nts::Tristate::TRUE;
    step();
    cr_assert_eq(is.compute(1), nts::Tristate::TRUE);
    cr_assert_eq(ir.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(b.compute(3), nts::Tristate::FALSE);
    cr_assert_eq(q.compute(3), nts::Tristate::TRUE);

    is = nts::Tristate::FALSE;
    step();
    cr_assert_eq(is.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(ir.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(b.compute(3), nts::Tristate::FALSE);
    cr_assert_eq(q.compute(3), nts::Tristate::TRUE);

    ir = nts::Tristate::TRUE;
    step();
    cr_assert_eq(is.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(ir.compute(1), nts::Tristate::TRUE);
    cr_assert_eq(b.compute(3), nts::Tristate::TRUE);
    cr_assert_eq(q.compute(3), nts::Tristate::FALSE);

    ir = nts::Tristate::FALSE;
    step();
    cr_assert_eq(is.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(ir.compute(1), nts::Tristate::FALSE);
    cr_assert_eq(b.compute(3), nts::Tristate::TRUE);
    cr_assert_eq(q.compute(3), nts::Tristate::FALSE);
}
