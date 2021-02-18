/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IPinComponent
*/

#ifndef IPINCOMPONENT_HPP_
#define IPINCOMPONENT_HPP_

#include "IComponent.hpp"

namespace nts {

class IPinComponent : virtual public IComponent {
public:
    enum class Kind {
        INPUT,
        OUTPUT,
    };

    virtual Kind kind() const = 0;
};

}

#endif /* !IPINCOMPONENT_HPP_ */
