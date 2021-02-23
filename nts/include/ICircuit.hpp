/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ICircuit
*/

#ifndef ICIRCUIT_HPP_
#define ICIRCUIT_HPP_

#include "IPinout.hpp"
#include "IComponent.hpp"
#include <memory>

namespace nts {

template <typename K>
class ICircuit : public IComponent {
public:
    // Components
    virtual void insert(const K&, std::unique_ptr<IComponent>) = 0;
    virtual IComponent &operator[](const K&) = 0;
    virtual const IComponent &operator[](const K&) const = 0;

    // Links
    virtual void connect(const K&, PinId, const K&, PinId) = 0;
    virtual void connect(PinId, const K&, PinId) = 0;
};

}

#endif /* !ICIRCUIT_HPP_ */
