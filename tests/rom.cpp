/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** rom
*/

#include "nts/RomComponent.hpp"
#include <criterion/criterion.h>
#include <cstdint>
#include <vector>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

void fetch(nts::RomComponent& rom, std::uint16_t addr)
{
    rom.write(8, addr & (1 << 0) ? T : F);
    rom.write(7, addr & (1 << 1) ? T : F);
    rom.write(6, addr & (1 << 2) ? T : F);
    rom.write(5, addr & (1 << 3) ? T : F);
    rom.write(4, addr & (1 << 4) ? T : F);
    rom.write(3, addr & (1 << 5) ? T : F);
    rom.write(2, addr & (1 << 6) ? T : F);
    rom.write(1, addr & (1 << 7) ? T : F);
    rom.write(23, addr & (1 << 8) ? T : F);
    rom.write(22, addr & (1 << 9) ? T : F);
    rom.write(19, addr & (1 << 10) ? T : F);

    rom.tick();
}

bool readHiZ(nts::RomComponent& rom, std::uint16_t addr)
{
    fetch(rom, addr);

    return true
        && (rom.read(9) == U)
        && (rom.read(10) == U)
        && (rom.read(11) == U)
        && (rom.read(13) == U)
        && (rom.read(14) == U)
        && (rom.read(15) == U)
        && (rom.read(16) == U)
        && (rom.read(17) == U);
}

std::uint8_t read(nts::RomComponent& rom, std::uint16_t addr)
{
    fetch(rom, addr);

    std::uint8_t val = 0
        | ((rom.read(9) == T) << 0)
        | ((rom.read(10) == T) << 1)
        | ((rom.read(11) == T) << 2)
        | ((rom.read(13) == T) << 3)
        | ((rom.read(14) == T) << 4)
        | ((rom.read(15) == T) << 5)
        | ((rom.read(16) == T) << 6)
        | ((rom.read(17) == T) << 7);

    return val;
}

Test(rom, hello_world)
{
    std::string text = "hello world!";
    std::vector<std::uint8_t> data(text.begin(), text.end());
    data.resize(2048);

    nts::RomComponent rom(data);

    rom.write(18, F);
    rom.write(20, F);
    cr_assert_eq(read(rom, 0), 'h');
    cr_assert_eq(read(rom, 1), 'e');
    cr_assert_eq(read(rom, 2), 'l');
    cr_assert_eq(read(rom, 3), 'l');
    cr_assert_eq(read(rom, 4), 'o');
    cr_assert_eq(read(rom, 5), ' ');
    cr_assert_eq(read(rom, 6), 'w');
    cr_assert_eq(read(rom, 7), 'o');
    cr_assert_eq(read(rom, 8), 'r');
    cr_assert_eq(read(rom, 9), 'l');
    cr_assert_eq(read(rom, 10), 'd');
    cr_assert_eq(read(rom, 11), '!');
}

Test(rom, out_of_bounds_is_zero)
{
    std::vector<std::uint8_t> data(2048);
    nts::RomComponent rom(data);

    rom.write(18, F);
    rom.write(20, F);
    cr_assert_eq(read(rom, 0), 0);
    cr_assert_eq(read(rom, 1), 0);
    cr_assert_eq(read(rom, 13), 0);
    cr_assert_eq(read(rom, 14), 0);
    cr_assert_eq(read(rom, 1392), 0);
}

Test(rom, output_tristate)
{
    std::string text = "hello world!";
    std::vector<std::uint8_t> data(text.begin(), text.end());
    data.resize(2048);
    nts::RomComponent rom(data);

    rom.write(20, F);
    rom.write(18, F);
    cr_assert_eq(read(rom, 0), 'h');

    rom.write(20, T);
    cr_assert(readHiZ(rom, 0));
    cr_assert(readHiZ(rom, 1));
    cr_assert(readHiZ(rom, 13));
    cr_assert(readHiZ(rom, 14));
    cr_assert(readHiZ(rom, 1392));

    rom.write(18, T);
    rom.write(20, F);
    cr_assert(readHiZ(rom, 0));
    cr_assert(readHiZ(rom, 1));
    cr_assert(readHiZ(rom, 13));
    cr_assert(readHiZ(rom, 14));
    cr_assert(readHiZ(rom, 1392));

    rom.write(18, T);
    rom.write(20, T);
    cr_assert(readHiZ(rom, 0));
    cr_assert(readHiZ(rom, 1));
    cr_assert(readHiZ(rom, 13));
    cr_assert(readHiZ(rom, 14));
    cr_assert(readHiZ(rom, 1392));
}
