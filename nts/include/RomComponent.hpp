/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** RomComponent
*/

#ifndef ROMCOMPONENT_HPP_
#define ROMCOMPONENT_HPP_

#include "AComponent.hpp"
#include <memory>
#include <vector>

namespace nts {
class RomComponent : public AComponent {
public:
    RomComponent(std::vector<char> buff);
    ~RomComponent() = default;

protected:
    void _compute(PinSetter set) override;

private:
    bool _compute_addr(size_t& addr, size_t pin);

    std::vector<char> m_buff;
};
}

#endif /* !ROMCOMPONENT_HPP_ */
