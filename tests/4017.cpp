/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** 4017
*/

#include "ClockComponent.hpp"
#include "InputComponent.hpp"
#include "NTSCircuit.hpp"
#include <criterion/criterion.h>
#include <cstddef>

Test(components_4017, timing_diagram)
{
    nts::ClockComponent cp0 = nts::Tristate::FALSE;
    nts::InputComponent cp1_ = nts::Tristate::FALSE;
    nts::InputComponent mr = nts::Tristate::TRUE;
    nts::OutputComponent outputs[11] = {};
    std::size_t outputPins[11] = { 3, 2, 4, 7, 10, 1, 5, 6, 9, 11, 12 };
    nts::NTSCircuit johnson("components/4017.nts");

    std::size_t tick = 0;
    auto sim = [&]() {
        tick++;
        cp0.simulate(tick);
        cp1_.simulate(tick);
        mr.simulate(tick);

        std::uint16_t out = 0;

        for (std::size_t i = 0; i < 11; i++) {
            out |= (outputs[i] == nts::Tristate::TRUE) << (10 - i);
        }

        return out;
    };

    cp1_.setLink(1, johnson, 13);
    cp0.setLink(1, johnson, 14);
    mr.setLink(1, johnson, 15);

    for (std::size_t i = 0; i < 11; i++) {
        outputs[i].setLink(1, johnson, outputPins[i]);
    }

    cp1_ = nts::Tristate::FALSE;
    cp0 = nts::Tristate::FALSE;
    mr = nts::Tristate::TRUE;
    cr_assert_eq(sim(), 0b10000000001);
    // clock is high here, so next sim isn't a rising edge
    mr = nts::Tristate::FALSE;
    cr_assert_eq(sim(), 0b10000000001);
    // from now on, the clock will rise every other simulation
    cr_assert_eq(sim(), 0b01000000001);
}
