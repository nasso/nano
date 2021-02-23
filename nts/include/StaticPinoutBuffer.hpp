/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** StaticPinoutBuffer
*/

#ifndef STATICPINOUTBUFFER_HPP_
#define STATICPINOUTBUFFER_HPP_

#include "IComponent.hpp"
#include <unordered_map>

namespace nts {

class StaticPinoutBuffer : public IPinoutBuffer {
public:
    using Buffer = std::unordered_map<PinId, Tristate>;

    StaticPinoutBuffer(Buffer);

    Tristate read(PinId) const override;
    void write(PinId, Tristate) override;

private:
    Buffer m_buffer;
};

}

#endif /* !STATICPINOUTBUFFER_HPP_ */
