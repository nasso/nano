/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** NorGate
*/

#ifndef NORGATE_HPP_
#define NORGATE_HPP_

#include "AndGate.hpp"
#include "Circuit.hpp"
#include "NotGate.hpp"

namespace nts {

class NorGate : public Circuit {
public:
    NorGate();

private:
    NotGate m_not[2];
    AndGate m_and;
};

}

#endif /* !NORGATE_HPP_ */
