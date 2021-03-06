/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** latch tests
*/

#include "nts/NtsCircuit.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>
#include <cstddef>

const auto U = nts::Tristate::UNDEFINED;
const auto F = nts::Tristate::FALSE;
const auto T = nts::Tristate::TRUE;

Test(latches, srlatch)
{
    auto gate = loadNts("components/srlatch.nts", { "components" });

    gate.write(1, F);
    gate.write(2, F);

    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(1, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(1, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);
}

Test(latches, dlatch)
{
    auto gate = loadNts("components/dlatch.nts", { "components" });

    gate.write(1, F);
    gate.write(2, F);

    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(1, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(1, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(1, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(1, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(1, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);
}

Test(latches, dflipflop)
{
    auto gate = loadNts("components/dflipflop.nts", { "components" });

    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(1, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(1, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    // the clock started undefined so setting it to true for the first time
    // should not correspond to a rising edge
    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);

    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(1, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), F);

    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(2, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(1, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(2, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);

    gate.write(1, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);
}

Test(latches, adflipflop_set)
{
    auto gate = loadNts("components/adflipflop.nts", { "components" });

    gate.cycle();
    cr_assert_eq(gate.read(3), U);
    cr_assert_eq(gate.read(4), U);

    gate.write(5, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);
    cr_assert_eq(gate.read(4), U);

    gate.write(5, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), T);
    cr_assert_eq(gate.read(4), U);

    // it is impossible to initialize the gate with data and clock to Hi-Z
    gate.write(5, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);
    cr_assert_eq(gate.read(4), U);
}

Test(latches, adflipflop_reset)
{
    auto gate = loadNts("components/adflipflop.nts", { "components" });

    gate.cycle();
    cr_assert_eq(gate.read(3), U);
    cr_assert_eq(gate.read(4), U);

    gate.write(6, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);
    cr_assert_eq(gate.read(4), U);

    gate.write(6, F);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);
    cr_assert_eq(gate.read(4), T);

    // it is impossible to initialize the gate with data and clock to Hi-Z
    gate.write(6, T);
    gate.cycle();
    cr_assert_eq(gate.read(3), U);
    cr_assert_eq(gate.read(4), U);
}

// FIXME
Test(latches, reg1, .disabled = true)
{
    auto gate = loadNts("components/reg1.nts", { "components" });

    auto step = [&](nts::Tristate data, nts::Tristate store, nts::Tristate cl) {
        gate.write(1, data);
        gate.write(2, store);
        gate.write(3, cl);
        gate.cycle();
    };

    step(U, U, U);
    cr_assert_eq(gate.read(4), U);

    // cycle the clock with undefined values
    step(U, U, F);
    cr_assert_eq(gate.read(4), U);
    step(U, U, T);
    cr_assert_eq(gate.read(4), U);
    step(U, U, F);
    cr_assert_eq(gate.read(4), U);

    // cycle the clock with (T, F)
    step(T, F, F);
    cr_assert_eq(gate.read(4), U);
    step(T, F, T);
    cr_assert_eq(gate.read(4), U);
    step(T, F, F);
    cr_assert_eq(gate.read(4), U);

    // cycle the clock with (T, T)
    step(T, T, F);
    cr_assert_eq(gate.read(4), U);
    step(T, T, T);
    cr_assert_eq(gate.read(4), T);
    step(T, T, F);
    cr_assert_eq(gate.read(4), T);

    // cycle the clock with (F, T)
    step(F, T, F);
    cr_assert_eq(gate.read(4), T);
    step(F, T, T);
    cr_assert_eq(gate.read(4), F);
    step(F, T, F);
    cr_assert_eq(gate.read(4), F);

    // keep the clock low and cycle the store!
    step(T, F, F);
    cr_assert_eq(gate.read(4), F);
    step(T, T, F);
    cr_assert_eq(gate.read(4), F);
    step(T, F, F);
    cr_assert_eq(gate.read(4), F);
}
