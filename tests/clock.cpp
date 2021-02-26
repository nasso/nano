/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** clock
*/

#include "nts/ClockComponent.hpp"
#include <criterion/criterion.h>
#include <cstddef>

Test(clock, stays_undefined)
{
    nts::ClockComponent clock;

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::UNDEFINED);

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::UNDEFINED);

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::UNDEFINED);
}

Test(clock, toggles_after_simulation)
{
    nts::ClockComponent clock = nts::Tristate::FALSE;

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::FALSE);

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::TRUE);

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::FALSE);
}

Test(clock, emits_last_set_value)
{
    nts::ClockComponent clock = nts::Tristate::TRUE;

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::TRUE);

    clock = nts::Tristate::FALSE;

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::FALSE);

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::TRUE);
}

Test(clock, stays_undefined_after_set)
{
    nts::ClockComponent clock = nts::Tristate::FALSE;

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::FALSE);

    clock = nts::Tristate::UNDEFINED;

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::UNDEFINED);

    clock.simulate();
    cr_assert_eq(clock.read(1), nts::Tristate::UNDEFINED);
}
