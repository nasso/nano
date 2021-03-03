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

    cr_assert(opt.is_none());
}

Test(option, basic_usage_some)
{
    mtl::Option<std::string> opt("hello");

    cr_assert(opt.is_some());
    cr_assert_eq(*opt, "hello");
}

Test(option, take)
{
    mtl::Option<std::string> opt("hello");

    opt.take();
    cr_assert(opt.is_none());
}

Test(option, emplace)
{
    mtl::Option<std::string> opt;

    cr_assert(opt.emplace("hello").is_none());
    cr_assert(opt.is_some());
    cr_assert_eq(*opt, "hello");
}

Test(option, reuse)
{
    mtl::Option<std::string> opt("hello");

    opt.take();
    cr_assert(opt.emplace("hi").is_none());
    cr_assert_eq(opt, mtl::Option<std::string>("hi"));
}

Test(option, default_construct_value)
{
    mtl::Option<int> opt_none;
    mtl::Option<int> opt_some({});

    cr_assert(opt_none.is_none());
    cr_assert(opt_some.is_some());
}

Test(option, unique_ptr)
{
    auto unique_int = std::make_unique<int>(42);
    mtl::Option<std::unique_ptr<int>> opt(std::move(std::make_unique<int>(3)));

    cr_assert_eq(**opt, 3);
    opt.take();
    cr_assert(opt.is_none());
    opt.emplace(new int(56));
    cr_assert(opt.is_some());
    cr_assert_eq(**opt, 56);
    opt = std::move(unique_int);
    cr_assert_eq(**opt, 42);
    **opt = 59;

    std::unique_ptr<int> got_it_back = opt.unwrap();
    cr_assert_eq(*got_it_back, 59);
}

Test(option, map_simple)
{
    mtl::Option<int> opt(3);

    cr_assert_eq(opt.map([](int v) { return v * 2; }), mtl::Option<int>(6));
}

Test(option, map_as_const_ref)
{
    using uni_int = std::unique_ptr<int>;
    mtl::Option<std::unique_ptr<int>> opt(std::make_unique<int>(3));

    mtl::Option<int> opt2 = opt.map([](uni_int v) { return *v * 2; });

    cr_assert_eq(*opt2, 6);
}

Test(option, unwrap_or)
{
    cr_assert_eq(mtl::Option<int>().unwrap_or_default(), 0);
    cr_assert_eq(mtl::Option<int>(8).unwrap_or_default(), 8);
    cr_assert_eq(mtl::Option<int>().unwrap_or(3), 3);
    cr_assert_eq(mtl::Option<int>(8).unwrap_or(3), 8);
    cr_assert_eq(mtl::Option<int>().unwrap_or_else([]() { return 3; }), 3);
    cr_assert_eq(mtl::Option<int>(8).unwrap_or_else([]() { return 3; }), 8);
}

Test(option, as_ref)
{
    mtl::Option<int> opt(3);
    mtl::Option<int&> ref;

    ref = opt.as_ref();

    cr_assert_eq(opt, ref);
}
