/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NorGate
*/

#include "NorGate.hpp"
#include "AndGate.hpp"
#include "NotGate.hpp"
#include <iostream>

namespace nts {

NorGate::NorGate()
{
    input(1).setLink(1, m_not[0], 1);
    input(2).setLink(1, m_not[1], 1);
    output(3).setLink(1, m_and, 3);

    m_and.setLink(1, m_not[0], 2);
    m_and.setLink(2, m_not[1], 2);
}

}
