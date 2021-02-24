/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** DynamicPinoutBuffer
*/

#include "DynamicPinoutBuffer.hpp"

namespace nts {

DynamicPinoutBuffer::DynamicPinoutBuffer(Buffer buf)
    : m_buffer(std::move(buf))
{
}

Tristate DynamicPinoutBuffer::read(PinId pin) const
{
    if (m_buffer.find(pin) != m_buffer.end()) {
        return m_buffer.at(pin);
    }

    return {};
}

void DynamicPinoutBuffer::write(PinId pin, Tristate val)
{
    m_buffer[pin] = val;
}

void DynamicPinoutBuffer::clear()
{
    m_buffer.clear();
}

}
