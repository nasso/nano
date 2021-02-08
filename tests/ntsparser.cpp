/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ntsparser
*/

#include "test_add.hpp"
#include <criterion/criterion.h>

Test(test, it_works)
{
    cr_assert_eq(add(2, 2), 4);
}
