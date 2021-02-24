/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** DynamicPinoutBuffer
*/

#ifndef DYNAMICPINOUTBUFFER_HPP_
#define DYNAMICPINOUTBUFFER_HPP_

#include "IComponent.hpp"
#include <unordered_map>

namespace nts {

class DynamicPinoutBuffer : public IPinoutBuffer {
public:
    using Buffer = std::unordered_map<PinId, Tristate>;

    DynamicPinoutBuffer(Buffer = {});

    Tristate read(PinId) const override;
    void write(PinId, Tristate) override;

    void clear();

private:
    Buffer m_buffer;
};

}

#endif /* !DYNAMICPINOUTBUFFER_HPP_ */
