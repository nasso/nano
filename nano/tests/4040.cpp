/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** 4040
*/

#include "nts/BuiltInComponentFactory.hpp"
#include "nts/ComboComponentFactory.hpp"
#include "nts/NtsCircuit.hpp"
#include "nts/NtsComponentFactory.hpp"
#include "nts/components/CounterComponent.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>
#include <memory>

const std::string NTS_SOURCE = ".chipsets:\n"
                               "clock cl_clock\n"
                               "input in_reset\n"
                               "output out_00\n"
                               "output out_01\n"
                               "output out_02\n"
                               "output out_03\n"
                               "output out_04\n"
                               "output out_05\n"
                               "output out_06\n"
                               "output out_07\n"
                               "output out_08\n"
                               "output out_09\n"
                               "output out_10\n"
                               "output out_11\n"
                               "4040 counter\n"
                               "\n"
                               ".links:\n"
                               "cl_clock:1 counter:10\n"
                               "in_reset:1 counter:11\n"
                               "out_00:1 counter:9\n"
                               "out_01:1 counter:7\n"
                               "out_02:1 counter:6\n"
                               "out_03:1 counter:5\n"
                               "out_04:1 counter:3\n"
                               "out_05:1 counter:2\n"
                               "out_06:1 counter:4\n"
                               "out_07:1 counter:13\n"
                               "out_08:1 counter:12\n"
                               "out_09:1 counter:14\n"
                               "out_10:1 counter:15\n"
                               "out_11:1 counter:1\n";

std::uint16_t readNumber(const nts::NtsCircuit& counter)
{
    return 0
        | ((counter.read(3) == nts::Tristate::TRUE) << 0)
        | ((counter.read(4) == nts::Tristate::TRUE) << 1)
        | ((counter.read(5) == nts::Tristate::TRUE) << 2)
        | ((counter.read(6) == nts::Tristate::TRUE) << 3)
        | ((counter.read(7) == nts::Tristate::TRUE) << 4)
        | ((counter.read(8) == nts::Tristate::TRUE) << 5)
        | ((counter.read(9) == nts::Tristate::TRUE) << 6)
        | ((counter.read(10) == nts::Tristate::TRUE) << 7)
        | ((counter.read(11) == nts::Tristate::TRUE) << 8)
        | ((counter.read(12) == nts::Tristate::TRUE) << 9)
        | ((counter.read(13) == nts::Tristate::TRUE) << 10)
        | ((counter.read(14) == nts::Tristate::TRUE) << 11);
}

Test(counter_4040, initialization)
{
    std::istringstream source(NTS_SOURCE);

    nts::ComboComponentFactory ccf;
    ccf.add(std::make_unique<nts::BuiltInComponentFactory>());
    ccf.add(std::make_unique<nts::NtsComponentFactory>("components"));

    nts::NtsCircuit circuit(source, ccf);

    circuit.cycle();

    circuit.write(1, nts::Tristate::FALSE);
    circuit.write(2, nts::Tristate::TRUE);

    circuit.cycle();
    cr_assert_eq(readNumber(circuit), 0);
    circuit.cycle();
    cr_assert_eq(readNumber(circuit), 0);
    circuit.cycle();
    cr_assert_eq(readNumber(circuit), 0);
}

Test(counter_4040, counting)
{
    std::istringstream source(NTS_SOURCE);

    nts::ComboComponentFactory ccf;
    ccf.add(std::make_unique<nts::BuiltInComponentFactory>());
    ccf.add(std::make_unique<nts::NtsComponentFactory>("components"));

    nts::NtsCircuit circuit(source, ccf);

    circuit.write(1, nts::Tristate::FALSE);
    circuit.write(2, nts::Tristate::TRUE);
    circuit.cycle(); // first cycle: clock is low
    circuit.write(2, nts::Tristate::FALSE);

    for (std::uint16_t n = 0; n < 20; n++) {
        cr_assert_eq(readNumber(circuit), n);
        circuit.cycle(); // rising
        circuit.cycle(); // falling
    }
}
