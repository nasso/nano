/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Chip
*/

#ifndef CHIP_HPP_
#define CHIP_HPP_

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <memory>
#include <set>

namespace nts {

class Chip : public AComponent {
public:
    Chip();

    void add(std::unique_ptr<IComponent> component);

protected:
    virtual void _compute(std::size_t tick) override;

private:
    std::set<std::unique_ptr<IComponent>> m_children;
};

}

#endif /* !CHIP_HPP_ */
