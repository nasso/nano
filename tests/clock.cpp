/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** clock
*/

#include "ClockComponent.hpp"
#include "StaticPinoutBuffer.hpp"
#include <criterion/criterion.h>
#include <cstddef>

Test(clock, stays_undefined)
{
    nts::ClockComponent clock;
    nts::StaticPinoutBuffer buf({ { 1, nts::Tristate::UNDEFINED } });

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::UNDEFINED);
}

Test(clock, toggles_after_simulation)
{
    nts::ClockComponent clock;
    nts::StaticPinoutBuffer buf({ { 1, nts::Tristate::UNDEFINED } });

    clock = nts::Tristate::FALSE;

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::FALSE);

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::TRUE);

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::FALSE);
}

Test(clock, emits_last_set_value)
{
    nts::ClockComponent clock;
    nts::StaticPinoutBuffer buf({ { 1, nts::Tristate::UNDEFINED } });

    clock = nts::Tristate::FALSE;

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::FALSE);

    clock = nts::Tristate::FALSE;

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::FALSE);

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::TRUE);
}

Test(clock, stays_undefined_when_set)
{
    nts::ClockComponent clock;
    nts::StaticPinoutBuffer buf({ { 1, nts::Tristate::UNDEFINED } });

    clock = nts::Tristate::FALSE;

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::FALSE);

    clock = nts::Tristate::UNDEFINED;

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::UNDEFINED);

    clock.simulate(buf);
    cr_assert_eq(buf.read(1), nts::Tristate::UNDEFINED);
}
