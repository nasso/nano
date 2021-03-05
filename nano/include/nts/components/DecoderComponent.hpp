/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** DecoderComponent
*/

#ifndef DECODERCOMPONENT_HPP_
#define DECODERCOMPONENT_HPP_

#include "../AComponent.hpp"
#include <memory>
#include <vector>

namespace nts {

class DecoderComponent : public AComponent {
public:
    DecoderComponent();

    void tick() override;
    virtual void display(std::ostream& os) const override;
};

}

#endif /* !DECODERCOMPONENT_HPP_ */
