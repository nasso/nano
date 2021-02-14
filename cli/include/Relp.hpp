/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Relp
*/

#ifndef Relp_HPP_
#define Relp_HPP_

#include "MainCircuit.hpp"

class Relp {
public:
    static void run(nts::MainCircuit&);

    static bool m_stopLoop;
};

#endif /* !Relp_HPP_ */
