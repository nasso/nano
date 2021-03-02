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
    RomComponent(std::size_t size);
    RomComponent(std::vector<std::uint8_t> data);

    void tick() override;
    virtual void display(std::ostream& os) const override;

private:
    std::vector<std::uint8_t> m_data;
};

}

#endif /* !ROMCOMPONENT_HPP_ */
