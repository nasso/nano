/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** nts_gates
*/

#include "InputComponent.hpp"
#include "NTSCircuit.hpp"
#include <criterion/criterion.h>

Test(logic_gates, nor_gate)
{
    std::size_t tick = 0;
    nts::InputComponent a;
    nts::InputComponent b;
    nts::OutputComponent out;
    nts::NTSCircuit gate("components/nor.nts");

    a.setLink(1, gate, 1);
    b.setLink(1, gate, 2);
    gate.setLink(3, out, 1);

    auto sim = [&](nts::Tristate va, nts::Tristate vb) {
        a = va;
        b = vb;
        a.simulate(++tick);
        b.simulate(++tick);
    };

    sim(nts::Tristate::UNDEFINED, nts::Tristate::UNDEFINED);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
    sim(nts::Tristate::UNDEFINED, nts::Tristate::FALSE);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
    sim(nts::Tristate::UNDEFINED, nts::Tristate::TRUE);
    cr_assert_eq(out, nts::Tristate::FALSE);
    sim(nts::Tristate::FALSE, nts::Tristate::UNDEFINED);
    cr_assert_eq(out, nts::Tristate::UNDEFINED);
    sim(nts::Tristate::FALSE, nts::Tristate::FALSE);
    cr_assert_eq(out, nts::Tristate::TRUE);
    sim(nts::Tristate::FALSE, nts::Tristate::TRUE);
    cr_assert_eq(out, nts::Tristate::FALSE);
    sim(nts::Tristate::TRUE, nts::Tristate::UNDEFINED);
    cr_assert_eq(out, nts::Tristate::FALSE);
    sim(nts::Tristate::TRUE, nts::Tristate::FALSE);
    cr_assert_eq(out, nts::Tristate::FALSE);
    sim(nts::Tristate::TRUE, nts::Tristate::TRUE);
    cr_assert_eq(out, nts::Tristate::FALSE);
}
