/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** 4017
*/

#include "nts/Circuit.hpp"
#include "nts/NtsCircuit.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>
#include <cstddef>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

Test(components_4017, timing_diagram)
{
    const nts::PinId PIN_CP1 = 13;
    const nts::PinId PIN_CP0 = 14;
    const nts::PinId PIN_MR = 15;
    const nts::PinId PIN_OUTS[11] = { 3, 2, 4, 7, 10, 1, 5, 6, 9, 11, 12 };

    nts::Tristate nextClockValue;
    nts::PinId clockPin;

    auto gate = loadNts("components/4017.nts", { "components" });

    auto sim = [&]() {
        gate.write(clockPin, nextClockValue);
        gate.cycle();
        nextClockValue = !nextClockValue;

        std::uint16_t out = 0;

        for (std::size_t i = 0; i < 11; i++) {
            out |= (gate.read(PIN_OUTS[i]) == nts::Tristate::TRUE) << (10 - i);
        }

        return out;
    };

    nextClockValue = T;
    clockPin = PIN_CP0;
    gate.write(PIN_CP1, F);
    gate.write(PIN_MR, T);
    cr_assert_eq(sim(), 0b10000000001);
    // clock is high here, so next sim isn't a rising edge
    gate.write(PIN_MR, F);
    cr_assert_eq(sim(), 0b10000000001);
    // from now on, the clock will rise every other simulation
    cr_assert_eq(sim(), 0b01000000001);
    cr_assert_eq(sim(), 0b01000000001);
    cr_assert_eq(sim(), 0b00100000001);
    cr_assert_eq(sim(), 0b00100000001);
    cr_assert_eq(sim(), 0b00010000001);
    cr_assert_eq(sim(), 0b00010000001);
    cr_assert_eq(sim(), 0b00001000001);
    cr_assert_eq(sim(), 0b00001000001);
    cr_assert_eq(sim(), 0b00000100000);
    cr_assert_eq(sim(), 0b00000100000);
    cr_assert_eq(sim(), 0b00000010000);
    cr_assert_eq(sim(), 0b00000010000);
    cr_assert_eq(sim(), 0b00000001000);
    cr_assert_eq(sim(), 0b00000001000);
    cr_assert_eq(sim(), 0b00000000100);
    cr_assert_eq(sim(), 0b00000000100);
    cr_assert_eq(sim(), 0b00000000010);
    cr_assert_eq(sim(), 0b00000000010);
    cr_assert_eq(sim(), 0b10000000001);

    // now testing the second clock
    clockPin = PIN_CP1;
    // make it start as high
    nextClockValue = T;

    // same thing should happen
    cr_assert_eq(sim(), 0b10000000001);
    cr_assert_eq(sim(), 0b01000000001);
    cr_assert_eq(sim(), 0b01000000001);
    cr_assert_eq(sim(), 0b00100000001);
    cr_assert_eq(sim(), 0b00100000001);
    cr_assert_eq(sim(), 0b00010000001);
    cr_assert_eq(sim(), 0b00010000001);
    cr_assert_eq(sim(), 0b00001000001);
    cr_assert_eq(sim(), 0b00001000001);
    cr_assert_eq(sim(), 0b00000100000);
    cr_assert_eq(sim(), 0b00000100000);
    cr_assert_eq(sim(), 0b00000010000);
    cr_assert_eq(sim(), 0b00000010000);
    cr_assert_eq(sim(), 0b00000001000);
    cr_assert_eq(sim(), 0b00000001000);
    cr_assert_eq(sim(), 0b00000000100);
    cr_assert_eq(sim(), 0b00000000100);
    cr_assert_eq(sim(), 0b00000000010);
    cr_assert_eq(sim(), 0b00000000010);
    cr_assert_eq(sim(), 0b10000000001);
    cr_assert_eq(sim(), 0b10000000001);
    cr_assert_eq(sim(), 0b01000000001);
    cr_assert_eq(sim(), 0b01000000001);
    cr_assert_eq(sim(), 0b00100000001);
    cr_assert_eq(sim(), 0b00100000001);

    // try to master reset everything
    gate.write(PIN_MR, T);
    cr_assert_eq(sim(), 0b10000000001);
    cr_assert_eq(sim(), 0b10000000001);
}
