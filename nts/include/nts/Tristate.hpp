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

class Tristate {
public:
    enum Value : std::uint8_t {
        UNDEFINED = std::uint8_t(-1),
        FALSE = 0,
        TRUE = 1,
    };

    constexpr Tristate(Value val = UNDEFINED);

    operator Value() const;
    explicit operator bool() const = delete;

    Tristate operator&&(const Tristate&) const;
    Tristate operator||(const Tristate&) const;
    Tristate operator!() const;

    Tristate& operator|=(const Tristate&);
    Tristate& operator&=(const Tristate&);

private:
    Value m_value;
};

std::ostream& operator<<(std::ostream&, const nts::Tristate&);

}

#endif /* !TRISTATE_HPP_ */
