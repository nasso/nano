/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** 4013
*/

#include "InputComponent.hpp"
#include "NTSCircuit.hpp"
#include "NotGate.hpp"
#include <criterion/criterion.h>

const auto U = nts::Tristate::UNDEFINED;
const auto F = nts::Tristate::FALSE;
const auto T = nts::Tristate::TRUE;

class FlipFlop4013 {
public:
    FlipFlop4013(
        nts::Tristate cl = U,
        nts::Tristate d = U,
        nts::Tristate r = U,
        nts::Tristate s = U)
        : gate("components/adflipflop.nts")
        , clock(cl)
        , data(d)
        , reset(r)
        , set(s)
    {
        set.setLink(1, set_, 1);
        reset.setLink(1, reset_, 1);

        gate.setLink(2, clock, 1);
        gate.setLink(6, reset_, 2);
        gate.setLink(1, data, 1);
        gate.setLink(5, set_, 2);

        simulate();
    }

    void simulate()
    {
        m_tick++;
        clock.simulate(m_tick);
        data.simulate(m_tick);
        reset.simulate(m_tick);
        set.simulate(m_tick);
    }

    std::pair<nts::Tristate, nts::Tristate> operator()(
        nts::Tristate cl,
        nts::Tristate d,
        nts::Tristate r,
        nts::Tristate s)
    {
        clock = cl;
        data = d;
        reset = r;
        set = s;

        simulate();
        return { gate.compute(3), gate.compute(4) };
    }

    nts::NTSCircuit gate;
    nts::InputComponent clock;
    nts::InputComponent data;
    nts::InputComponent reset;
    nts::InputComponent set;

private:
    nts::NotGate reset_;
    nts::NotGate set_;
    std::size_t m_tick = 0;
};

Test(flip_flop_4013, async_set)
{
    FlipFlop4013 ff(F, F, F, F);

    cr_assert_eq(ff(F, F, F, T), std::make_pair(T, F));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(T, F));
}

Test(flip_flop_4013, async_reset)
{
    FlipFlop4013 ff(F, F, F, F);

    cr_assert_eq(ff(F, F, T, F), std::make_pair(F, T));
    cr_assert_eq(ff(F, F, F, F), std::make_pair(F, T));
}

Test(flip_flop_4013, async_set_and_reset)
{
    FlipFlop4013 ff(F, F, F, F);

    cr_assert_eq(ff(F, F, T, T), std::make_pair(T, T));
    cr_assert_eq(ff(F, F, F, T), std::make_pair(T, F));
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
