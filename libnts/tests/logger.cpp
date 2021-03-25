/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** logger
*/

#include "nts/components/LoggerComponent.hpp"
#include "nts_utils.hpp"
#include <criterion/criterion.h>
#include <cstdint>
#include <sstream>
#include <string>

const auto T = nts::Tristate::TRUE;
const auto F = nts::Tristate::FALSE;
const auto U = nts::Tristate::UNDEFINED;

static void write(nts::LoggerComponent& logger, std::uint8_t c)
{
    logger.write(1, c & (1 << 0) ? T : F);
    logger.write(2, c & (1 << 1) ? T : F);
    logger.write(3, c & (1 << 2) ? T : F);
    logger.write(4, c & (1 << 3) ? T : F);
    logger.write(5, c & (1 << 4) ? T : F);
    logger.write(6, c & (1 << 5) ? T : F);
    logger.write(7, c & (1 << 6) ? T : F);
    logger.write(8, c & (1 << 7) ? T : F);

    // cycle the clock
    logger.write(9, F);
    stabilize(logger);
    logger.write(9, T);
    stabilize(logger);
}

static void write(nts::LoggerComponent& logger, const std::string& str)
{
    for (char c : str) {
        write(logger, c);
    }
}

Test(logger, hello_world)
{
    std::ostringstream oss;
    nts::LoggerComponent logger(oss);

    logger.write(10, F);
    write(logger, "hello world!");

    cr_assert_eq(oss.str(), "hello world!");
}

Test(logger, inhibit)
{
    std::ostringstream oss;
    nts::LoggerComponent logger(oss);

    logger.write(10, T);
    write(logger, "hello world!");

    cr_assert_eq(oss.str(), "");
}
