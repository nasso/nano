/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** AChip
*/

#ifndef ACHIP_HPP_
#define ACHIP_HPP_

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <vector>

namespace nts {

class AChip : public AComponent {
public:
    AChip();

    nts::Tristate compute(std::size_t pin) override;
    void add(std::unique_ptr<IComponent> component);

private:
    std::vector<std::unique_ptr<IComponent>> m_children;
};

}

#endif /* !ACHIP_HPP_ */
