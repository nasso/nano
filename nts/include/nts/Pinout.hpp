/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Pinout
*/

#ifndef PINOUT_HPP_
#define PINOUT_HPP_

#include <cstddef>
#include <unordered_map>

namespace nts {

enum class PinMode : int {
    NONE = 0,
    INPUT = 1 << 1,
    OUTPUT = 1 << 2,
};

using PinId = std::size_t;
using Pinout = std::unordered_map<PinId, PinMode>;

}

nts::PinMode operator&(nts::PinMode, nts::PinMode);
nts::PinMode operator|(nts::PinMode, nts::PinMode);
nts::PinMode operator^(nts::PinMode, nts::PinMode);
nts::PinMode operator~(nts::PinMode);
bool operator!(nts::PinMode);
bool operator!=(nts::PinMode, nts::PinMode);
bool operator==(nts::PinMode, nts::PinMode);

#endif /* !PINOUT_HPP_ */
