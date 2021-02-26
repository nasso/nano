/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** assert_truth
*/

#ifndef ASSERT_TRUTH_HPP_
#define ASSERT_TRUTH_HPP_

#include "nts/IComponent.hpp"
#include <cmath>
#include <criterion/criterion.h>
#include <cstddef>
#include <unordered_map>

static constexpr std::size_t spow(std::size_t x, int n, std::size_t acc = 1)
{
    return n < 1
        ? acc
        : spow(x * x, n / 2, (n % 2) ? acc * x : acc);
}

template <
    std::size_t I,
    std::size_t O,
    std::size_t B = 3,
    typename V = nts::Tristate>
struct GateSpec {
    std::size_t inputs[I];
    std::size_t outputs[O];
    struct {
        V inputs[I];
        V outputs[O];
    } truthTable[spow(B, I)];
};

template <
    std::size_t I = 2,
    std::size_t O = 1,
    std::size_t B = 3,
    typename V = nts::Tristate>
static bool test_gate(nts::IComponent& gate, GateSpec<I, O, B, V> spec)
{
    std::unordered_map<std::size_t, nts::Tristate> pinout;

    for (std::size_t i = 0; i < I; i++) {
        pinout[spec.inputs[i]] = nts::Tristate::UNDEFINED;
    }

    for (std::size_t i = 0; i < O; i++) {
        pinout[spec.outputs[i]] = nts::Tristate::UNDEFINED;
    }

    for (auto& case_ : spec.truthTable) {
        for (std::size_t i = 0; i < I; i++) {
            gate.write(spec.inputs[i], case_.inputs[i]);
        }

        gate.simulate();

        for (std::size_t i = 0; i < O; i++) {
            if (gate.read(spec.outputs[i]) != case_.outputs[i]) {
                return false;
            }
        }
    }

    return true;
}

template <
    std::size_t I = 2,
    std::size_t O = 1,
    std::size_t B = 3,
    typename V = nts::Tristate>
static void assert_truth(nts::IComponent& gate, GateSpec<I, O, B, V> spec)
{
    if (!test_gate(gate, spec)) {
        criterion::logging::warn << gate << std::flush;
        cr_assert_fail();
    }
}

template <
    std::size_t I = 2,
    std::size_t O = 1,
    std::size_t B = 3,
    typename V = nts::Tristate>
static void expect_truth(nts::IComponent& gate, GateSpec<I, O, B, V> spec)
{
    if (!test_gate(gate, spec)) {
        criterion::logging::info << gate << std::flush;
        cr_expect_fail();
    }
}

#endif /* !ASSERT_TRUTH_HPP_ */
