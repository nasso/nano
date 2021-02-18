/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IOutputComponent
*/

#ifndef IOUTPUTCOMPONENT_HPP_
#define IOUTPUTCOMPONENT_HPP_

#include "IPinComponent.hpp"

namespace nts {

class IOutputComponent : virtual public IPinComponent {
public:
    virtual operator nts::Tristate() const = 0;

    Kind kind() const final override
    {
        return Kind::OUTPUT;
    }
};

}

#endif /* !IOUTPUTCOMPONENT_HPP_ */
