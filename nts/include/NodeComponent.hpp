/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NodeComponent
*/

#ifndef NODECOMPONENT_HPP_
#define NODECOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {

/**
 * @brief A component forwarding its single input to its single output.
 */
class NodeComponent : public AComponent {
public:
    NodeComponent();

protected:
    void _compute(PinSetter set) override;
};

}

#endif /* !NODECOMPONENT_HPP_ */
