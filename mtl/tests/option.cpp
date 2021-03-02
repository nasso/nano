/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** option
*/

#include "mtl/Option.hpp"
#include <criterion/criterion.h>
#include <string>

Test(option, basic_usage_none)
{
    mtl::Option<std::string> opt;

    cr_assert_not(opt.some());
}

Test(option, basic_usage_some)
{
    mtl::Option<std::string> opt("hello");

    cr_assert(opt.some());
    cr_assert_eq(*opt, "hello");
}

Test(option, clear)
{
    mtl::Option<std::string> opt("hello");

    opt.clear();
    cr_assert_not(opt.some());
}

Test(option, emplace)
{
    mtl::Option<std::string> opt;

    opt.emplace("hello");
    cr_assert(opt.some());
    cr_assert_eq(*opt, "hello");
}

Test(option, assign_operator)
{
    mtl::Option<std::string> opt;

    opt = "hello";
    cr_assert(opt.some());
    cr_assert_eq(*opt, "hello");
}

Test(option, reuse)
{
    mtl::Option<std::string> opt("hello");

    opt.clear();
    opt = "hi";
    cr_assert(opt.some());
    cr_assert_eq(*opt, "hi");
}

Test(option, default_construct_value)
{
    mtl::Option<int> opt_none;
    mtl::Option<int> opt_some({});

    cr_assert_not(opt_none.some());
    cr_assert(opt_some.some());
}

Test(option, unique_ptr)
{
    auto unique_int = std::make_unique<int>(42);
    mtl::Option<std::unique_ptr<int>> opt(new int(3));

    cr_assert_eq(**opt, 3);
    opt.clear();
    cr_assert_not(opt.some());
    opt = new int(56);
    cr_assert(opt.some());
    cr_assert_eq(**opt, 56);
    opt = std::move(unique_int);
    cr_assert_eq(**opt, 42);
    **opt = 59;

    std::unique_ptr<int> got_it_back = opt.take();
    cr_assert_eq(*got_it_back, 59);
}
