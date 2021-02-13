/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** assert_truth
*/

#ifndef ASSERT_TRUTH_HPP_
#define ASSERT_TRUTH_HPP_

#include "IComponent.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include <cmath>
#include <criterion/criterion.h>
#include <cstddef>

template <std::size_t I, std::size_t O>
struct GateSpec {
    std::size_t inputs[I];
    std::size_t outputs[O];
    struct {
        nts::Tristate inputs[I];
        nts::Tristate outputs[O];
    } truthTable[(std::size_t)std::pow(3, I)];
};

template <std::size_t I = 2, std::size_t O = 1>
static void assert_truth(nts::IComponent& gate, GateSpec<I, O> spec)
{
    std::size_t tick = 0;
    nts::InputComponent inputs[I] = {};
    nts::OutputComponent outputs[O] = {};

    for (std::size_t i = 0; i < I; i++) {
        inputs[i].setLink(1, gate, spec.inputs[i]);
    }

    for (std::size_t i = 0; i < O; i++) {
        outputs[i].setLink(1, gate, spec.outputs[i]);
    }

    for (auto& case_ : spec.truthTable) {
        for (std::size_t i = 0; i < I; i++) {
            inputs[i] = case_.inputs[i];
            inputs[i].simulate(++tick);
        }

        for (std::size_t i = 0; i < O; i++) {
            cr_assert_eq(outputs[i], case_.outputs[i]);
        }
    }
}

#endif /* !ASSERT_TRUTH_HPP_ */
