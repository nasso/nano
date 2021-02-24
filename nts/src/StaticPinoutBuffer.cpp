/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** StaticPinoutBuffer
*/

#include "StaticPinoutBuffer.hpp"

namespace nts {

StaticPinoutBuffer::StaticPinoutBuffer(Buffer buf)
    : m_buffer(std::move(buf))
{
}

StaticPinoutBuffer::StaticPinoutBuffer(Pinout pinout)
{
    for (auto& pin : pinout) {
        m_buffer[pin.first] = nts::Tristate::UNDEFINED;
    }
}

Tristate StaticPinoutBuffer::read(PinId pin) const
{
    return m_buffer.at(pin);
}

void StaticPinoutBuffer::write(PinId pin, Tristate val)
{
    m_buffer.at(pin) = val;
}

}
