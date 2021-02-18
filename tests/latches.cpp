/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** latch tests
*/

#include "InputComponent.hpp"
#include "NTSCircuit.hpp"
#include "OutputComponent.hpp"
#include <criterion/criterion.h>
#include <cstddef>

const auto U = nts::Tristate::UNDEFINED;
const auto F = nts::Tristate::FALSE;
const auto T = nts::Tristate::TRUE;

Test(latches, srlatch)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/srlatch.nts");
    nts::InputComponent is = nts::Tristate::FALSE;
    nts::InputComponent ir = nts::Tristate::FALSE;
    nts::OutputComponent out;

    auto step = [&]() {
        tick++;
        is.simulate(tick);
        ir.simulate(tick);
    };

    is.setLink(1, gate, 1);
    ir.setLink(1, gate, 2);
    gate.setLink(3, out, 1);

    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    is = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    is = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    ir = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    ir = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);
}

Test(latches, dlatch)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/dlatch.nts");
    nts::InputComponent idata = nts::Tristate::FALSE;
    nts::InputComponent istore = nts::Tristate::FALSE;
    nts::OutputComponent out;

    auto step = [&]() {
        tick++;
        idata.simulate(tick);
        istore.simulate(tick);
    };

    idata.setLink(1, gate, 1);
    istore.setLink(1, gate, 2);
    gate.setLink(3, out, 1);

    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    idata = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    istore = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    idata = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    istore = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    istore = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    istore = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);
}

Test(latches, dflipflop)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/dflipflop.nts");
    nts::InputComponent idata;
    nts::InputComponent iclock;
    nts::OutputComponent out;

    auto step = [&]() {
        tick++;
        idata.simulate(tick);
        iclock.simulate(tick);
    };

    idata.setLink(1, gate, 1);
    iclock.setLink(1, gate, 2);
    gate.setLink(3, out, 1);

    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    idata = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    // the clock started undefined to setting it to true for the first time
    // should correspond to a rising edge
    iclock = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    iclock = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::UNDEFINED);

    iclock = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    iclock = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    idata = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::FALSE);

    iclock = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    iclock = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    iclock = nts::Tristate::TRUE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    iclock = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);

    idata = nts::Tristate::FALSE;
    step();
    cr_assert_eq(out, nts::Tristate::TRUE);
}

Test(latches, adflipflop_set)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/adflipflop.nts");
    nts::InputComponent idata;
    nts::InputComponent iclock;
    nts::InputComponent ipreset;
    nts::InputComponent iclear;
    nts::OutputComponent out[2];

    auto step = [&]() {
        tick++;
        idata.simulate(tick);
        iclock.simulate(tick);
        ipreset.simulate(tick);
        iclear.simulate(tick);
    };

    idata.setLink(1, gate, 1);
    iclock.setLink(1, gate, 2);
    out[0].setLink(1, gate, 3);
    out[1].setLink(1, gate, 4);
    ipreset.setLink(1, gate, 5);
    iclear.setLink(1, gate, 6);

    step();
    cr_assert_eq(out[0], U);
    cr_assert_eq(out[1], U);

    ipreset = T;
    step();
    cr_assert_eq(out[0], U);
    cr_assert_eq(out[1], U);

    ipreset = F;
    step();
    cr_assert_eq(out[0], T);
    cr_assert_eq(out[1], U);

    // it is impossible to initialize the gate with data and clock to Hi-Z
    ipreset = T;
    step();
    cr_assert_eq(out[0], U);
    cr_assert_eq(out[1], U);
}

Test(latches, adflipflop_reset)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/adflipflop.nts");
    nts::InputComponent idata;
    nts::InputComponent iclock;
    nts::InputComponent ipreset;
    nts::InputComponent iclear;
    nts::OutputComponent out[2];

    auto step = [&]() {
        tick++;
        idata.simulate(tick);
        iclock.simulate(tick);
        ipreset.simulate(tick);
        iclear.simulate(tick);
    };

    idata.setLink(1, gate, 1);
    iclock.setLink(1, gate, 2);
    out[0].setLink(1, gate, 3);
    out[1].setLink(1, gate, 4);
    ipreset.setLink(1, gate, 5);
    iclear.setLink(1, gate, 6);

    step();
    cr_assert_eq(out[0], U);
    cr_assert_eq(out[1], U);

    iclear = T;
    step();
    cr_assert_eq(out[0], U);
    cr_assert_eq(out[1], U);

    iclear = F;
    step();
    cr_assert_eq(out[0], U);
    cr_assert_eq(out[1], T);

    // it is impossible to initialize the gate with data and clock to Hi-Z
    iclear = T;
    step();
    cr_assert_eq(out[0], U);
    cr_assert_eq(out[1], U);
}

Test(latches, reg1, .disabled = true)
{
    std::size_t tick = 0;
    nts::NTSCircuit gate("components/reg1.nts");
    nts::InputComponent idata;
    nts::InputComponent istore;
    nts::InputComponent iclock;
    nts::OutputComponent out;

    auto step = [&](nts::Tristate data, nts::Tristate store, nts::Tristate cl) {
        idata = data;
        istore = store;
        iclock = cl;

        tick++;
        idata.simulate(tick);
        istore.simulate(tick);
        iclock.simulate(tick);
    };

    idata.setLink(1, gate, 1);
    istore.setLink(1, gate, 2);
    iclock.setLink(1, gate, 3);
    gate.setLink(4, out, 1);

    step(U, U, U);
    cr_assert_eq(out, U);

    // cycle the clock with undefined values
    step(U, U, F);
    cr_assert_eq(out, U);
    step(U, U, T);
    cr_assert_eq(out, U);
    step(U, U, F);
    cr_assert_eq(out, U);

    // cycle the clock with (T, F)
    step(T, F, F);
    cr_assert_eq(out, U);
    step(T, F, T);
    cr_assert_eq(out, U);
    step(T, F, F);
    cr_assert_eq(out, U);

    // cycle the clock with (T, T)
    step(T, T, F);
    cr_assert_eq(out, U);
    step(T, T, T);
    cr_assert_eq(out, T);
    step(T, T, F);
    cr_assert_eq(out, T);

    // cycle the clock with (F, T)
    step(F, T, F);
    cr_assert_eq(out, T);
    step(F, T, T);
    cr_assert_eq(out, F);
    step(F, T, F);
    cr_assert_eq(out, F);

    // keep the clock low and cycle the store!
    step(T, F, F);
    cr_assert_eq(out, F);
    step(T, T, F);
    cr_assert_eq(out, F);
    step(T, F, F);
    cr_assert_eq(out, F);
}
