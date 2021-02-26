/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** RomComponent
*/

#include "RomComponent.hpp"

namespace nts {
RomComponent::RomComponent(std::vector<char> buff)
    : m_buff(buff)
{
    std::vector<size_t> inputs_pin = { 8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19 };
    std::vector<size_t> outputs_pin = { 9, 10, 11, 13, 14, 15, 16, 17 };

    for (auto pin : inputs_pin)
        input(pin);
    for (auto pin : outputs_pin)
        output(pin);
}

bool RomComponent::_compute_addr(size_t& addr, size_t pin)
{
    Tristate val = compute(pin);
    if (val == UNDEFINED)
        return true;
    addr = (addr << 1) + val;
    return false;
}

void RomComponent::_compute(PinSetter set)
{
    size_t addr = 0;
    char res = 0;
    std::vector<size_t> inputs_pin = { 8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19 };
    std::vector<size_t> outputs_pin = { 9, 10, 11, 13, 14, 15, 16, 17 };

    for (auto pin : inputs_pin) {
        if (_compute_addr(addr, pin))
            return;
    }
    if (addr >= m_buff.size()) {
        for (auto pin : outputs_pin)
            set(pin, UNDEFINED);
    }
    res = m_buff[addr];
    for (auto pin : outputs_pin) {
        set(pin, res & 1 ? TRUE : FALSE);
        res = res >> 1;
    }
}
}
