/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Tristate
*/

#ifndef TRISTATE_HPP_
#define TRISTATE_HPP_

#include <cstdint>
#include <iostream>

namespace nts {

enum class Tristate {
    UNDEFINED = -1,
    FALSE = 0,
    TRUE = 1,
};

}

nts::Tristate operator&&(nts::Tristate, nts::Tristate);
nts::Tristate operator||(nts::Tristate, nts::Tristate);
nts::Tristate operator!(nts::Tristate);

std::ostream& operator<<(std::ostream&, const nts::Tristate&);

#endif /* !TRISTATE_HPP_ */
