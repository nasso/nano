/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** option
*/

#include "mtl/Option.hpp"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <string>

#ifdef _WIN32
#define LF "\r\n"
#else
#define LF "\n"
#endif

class Unique {
public:
    Unique()
        : m_val(0)
    {
        std::cout << "Unique()" << std::endl;
    }

    explicit Unique(int val)
        : m_val(val)
    {
        std::cout << "Unique(" << val << ")" << std::endl;
    }

    Unique(const Unique&) = delete;

    Unique(Unique&& other)
        : m_val(other.m_val)
    {
        other.m_moved = true;
    }

    ~Unique()
    {
        if (!m_moved) {
            std::cout << "~Unique(" << m_val << ")" << std::endl;
        }
    }

    bool operator==(const Unique& rhs) const
    {
        return m_val == rhs.m_val;
    }

    bool operator==(int rhs) const
    {
        return m_val == rhs;
    }

    int get() const
    {
        return m_val;
    }

private:
    int m_val = 0;
    bool m_moved = false;
};

TestSuite(option, .init = cr_redirect_stdout);

Test(option, default_constructor_is_none)
{
    mtl::Option<Unique> opt;

    cr_assert(!opt);
    std::cout << std::endl;
    cr_assert_stdout_eq_str(LF);
}

Test(option, some_constructor)
{
    mtl::Option<Unique> opt = mtl::some<Unique>(4);

    cr_assert(opt);
    cr_assert_eq(opt.unwrap(), 4);
    cr_assert(!opt);
    cr_assert_stdout_eq_str(
        "Unique(4)" LF
        "~Unique(4)" LF);
}

Test(option, some_default_constructor)
{
    auto opt = mtl::some<Unique>();

    cr_assert(opt);
    cr_assert_eq(opt.unwrap(), 0);
    cr_assert_stdout_eq_str(
        "Unique()" LF
        "~Unique(0)" LF);
}

Test(option, replace_some)
{
    mtl::Option<std::string> opt;

    cr_assert(opt.replace("hello").is_none());
    cr_assert(opt);
    cr_assert_eq(opt.unwrap(), "hello");
}

Test(option, replace_none)
{
    auto opt = mtl::some<std::string>("hello");

    cr_assert(opt);
    cr_assert_eq(opt.unwrap(), "hello");
    cr_assert(opt.replace("hi").is_none());
    cr_assert(opt);
    cr_assert_eq(opt.unwrap(), "hi");
}

Test(option, map_simple)
{
    auto opt = mtl::some<int>(3);
    auto dbl = opt.map([](int v) { return v * 2; });

    cr_assert(dbl);
    cr_assert_eq(dbl.unwrap(), 6);
}

Test(option, unwrap_or)
{
    cr_assert_eq(mtl::none<int>().unwrap_or_default(), 0);
    cr_assert_eq(mtl::some<int>(8).unwrap_or_default(), 8);
    cr_assert_eq(mtl::none<int>().unwrap_or(3), 3);
    cr_assert_eq(mtl::some<int>(8).unwrap_or(3), 8);
    cr_assert_eq(mtl::none<int>().unwrap_or_else([]() { return 3; }), 3);
    cr_assert_eq(mtl::some<int>(8).unwrap_or_else([]() { return 3; }), 8);
}

Test(option, as_ref)
{
    mtl::Option<int> opt = mtl::some<int>(3);
    mtl::Option<const int&> ref = opt.as_ref();

    cr_assert_eq(ref.unwrap(), 3);
}

Test(option, map_as_ref)
{
    mtl::Option<Unique> mbOrig = mtl::some<Unique>(3);
    mtl::Option<const Unique&> mbRef = mbOrig.as_ref();
    mtl::Option<Unique> mbDoubled = mbRef.map([](const Unique& u) {
        return Unique(u.get() * 2);
    });

    cr_assert(mbOrig);
    cr_assert(!mbRef);
    cr_assert(mbDoubled);
    cr_assert_eq(mbDoubled.unwrap().get(), mbOrig.unwrap().get() * 2);
}

Test(option, unique_ptr)
{
    mtl::Option<std::unique_ptr<int>> opt(std::make_unique<int>(3));

    cr_assert(opt);
    cr_assert_eq(*opt.unwrap(), 3);
    opt.replace(new int(56));
    opt.replace(new int(139));
    cr_assert(opt);
    cr_assert_eq(*opt.unwrap(), 139);
    opt.replace(std::move(std::make_unique<int>(42)));
}
