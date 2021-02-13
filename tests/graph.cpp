/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** graph
*/

#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include <criterion/criterion.h>

Test(graph, single_input)
{
    nts::InputComponent in;

    cr_assert_eq(in.compute(1), nts::Tristate::UNDEFINED);

    in = nts::Tristate::TRUE;
    cr_assert_eq(in.compute(1), nts::Tristate::UNDEFINED);
    in.simulate(1);
    in = nts::Tristate::FALSE;
    cr_assert_eq(in.compute(1), nts::Tristate::TRUE);
    in.simulate(1);
    cr_assert_eq(in.compute(1), nts::Tristate::TRUE);
    in.simulate(2);
    cr_assert_eq(in.compute(1), nts::Tristate::FALSE);
}

Test(graph, input_into_node)
{
    nts::InputComponent in = nts::Tristate::TRUE;
    nts::OutputComponent out;

    in.setLink(1, out, 1);
    in.simulate(1);

    cr_assert_eq(out, nts::Tristate::TRUE);
}

Test(graph, unset_single_link)
{
    nts::InputComponent in = nts::Tristate::TRUE;
    nts::OutputComponent out;

    in.setLink(1, out, 1);
    in.unsetLink(1, out, 1);
    in.simulate(1);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    in.setLink(1, out, 1);
    in.simulate(1);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
    in.simulate(2);
    cr_assert_eq(out, nts::Tristate::TRUE);
    in = nts::Tristate::FALSE;
    out.unsetLink(1, in, 1);
    in.simulate(3);
    cr_assert_eq(out, nts::Tristate::TRUE);
    out.simulate(2);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
    out.simulate(3);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
}
