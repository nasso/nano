/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** NorGate
*/

#ifndef NORGATE_HPP_
#define NORGATE_HPP_

#include "AComponent.hpp"

namespace nts {

class NorGate : public AComponent {
protected:
    void _compute(std::size_t tick) override;
};

}

#endif /* !NORGATE_HPP_ */
