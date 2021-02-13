/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** clock
*/

#include "ClockComponent.hpp"
#include "OutputComponent.hpp"
#include <criterion/criterion.h>
#include <cstddef>

Test(clock, starts_undefined)
{
    nts::ClockComponent clock;
    nts::OutputComponent out;
    clock.setLink(1, out, 1);

    cr_assert_eq(out, nts::Tristate::UNDEFINED);
    clock.simulate(1);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
}

Test(clock, stays_undefined)
{
    nts::ClockComponent clock;
    nts::OutputComponent out;
    clock.setLink(1, out, 1);

    cr_assert_eq(out, nts::Tristate::UNDEFINED);
    clock.simulate(1);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
}

Test(clock, inverts_non_undefined_after_simulation)
{
    nts::ClockComponent clock;
    nts::OutputComponent out;
    clock.setLink(1, out, 1);

    clock = nts::Tristate::FALSE;

    clock.simulate(1);
    cr_assert_eq(out, nts::Tristate::FALSE);

    clock.simulate(2);
    cr_assert_eq(out, nts::Tristate::TRUE);

    clock.simulate(3);
    cr_assert_eq(out, nts::Tristate::FALSE);
}

Test(clock, emits_last_set_value)
{
    nts::ClockComponent clock;
    nts::OutputComponent out;
    clock.setLink(1, out, 1);

    clock = nts::Tristate::FALSE;

    clock.simulate(1);
    cr_assert_eq(out, nts::Tristate::FALSE);

    clock = nts::Tristate::FALSE;

    clock.simulate(2);
    cr_assert_eq(out, nts::Tristate::FALSE);

    clock.simulate(3);
    cr_assert_eq(out, nts::Tristate::TRUE);
}

Test(clock, stays_undefined_when_set)
{
    nts::ClockComponent clock;
    nts::OutputComponent out;
    clock.setLink(1, out, 1);

    clock = nts::Tristate::FALSE;

    clock.simulate(1);
    cr_assert_eq(out, nts::Tristate::FALSE);

    clock = nts::Tristate::UNDEFINED;

    clock.simulate(2);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    clock.simulate(3);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
}
