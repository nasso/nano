/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NotGate
*/

#include "nts/NotGate.hpp"
#include <iostream>

namespace nts {

NotGate::NotGate()
{
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
}

void NotGate::simulate()
{
    write(2, !read(1));
}

}
