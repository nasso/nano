/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** 4013
*/

#include "nts/NotGate.hpp"
#include "nts/NtsCircuit.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>

const nts::Tristate U(nts::Tristate::UNDEFINED);
const nts::Tristate F(nts::Tristate::FALSE);
const nts::Tristate T(nts::Tristate::TRUE);

class FlipFlop4013 {
public:
    FlipFlop4013(
        nts::Tristate cl = U,
        nts::Tristate d = U,
        nts::Tristate s = U,
        nts::Tristate r = U)
        : gate(loadNts("components/adflipflop.nts", { "components" }))
    {
        gate.write(1, d);
        gate.write(2, cl);
        gate.write(5, !s);
        gate.write(6, !r);

        gate.cycle();
    }

    std::pair<nts::Tristate, nts::Tristate> operator()(
        nts::Tristate cl,
        nts::Tristate d,
        nts::Tristate s,
        nts::Tristate r)
    {
        gate.write(1, d);
        gate.write(2, cl);
        gate.write(5, !s);
        gate.write(6, !r);

        gate.cycle();
        return { gate.read(3), gate.read(4) };
    }

    nts::NtsCircuit gate;
};

Test(flip_flop_4013, async_set)
{
    FlipFlop4013 ff(F, F, F, F);

    cr_assert_eq(ff(F, F, T, F), std::make_pair(T, F));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(T, F));
}

Test(flip_flop_4013, async_reset)
{
    FlipFlop4013 ff(F, F, F, F);

    cr_assert_eq(ff(F, F, F, T), std::make_pair(F, T));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(F, T));
}

Test(flip_flop_4013, async_set_and_reset)
{
    FlipFlop4013 ff(F, F, F, F);

    cr_assert_eq(ff(F, F, T, T), std::make_pair(T, T));
    cr_assert_eq(ff(F, F, T, F), std::make_pair(T, F));
}

Test(flip_flop_4013, sync_usage)
{
    FlipFlop4013 ff(F, F, F, F);

    cr_assert_eq(ff(T, F, F, F), std::make_pair(F, T));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(F, T));
    cr_assert_eq(ff(F, T, F, F), std::make_pair(F, T));
    cr_assert_eq(ff(T, T, F, F), std::make_pair(T, F));
    cr_assert_eq(ff(T, F, F, F), std::make_pair(T, F));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(T, F));
    cr_assert_eq(ff(F, T, F, F), std::make_pair(T, F));
    cr_assert_eq(ff(T, T, F, F), std::make_pair(T, F));
    cr_assert_eq(ff(F, T, F, F), std::make_pair(T, F));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(T, F));
    cr_assert_eq(ff(T, F, F, F), std::make_pair(F, T));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(F, T));
}
