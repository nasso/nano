/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** option
*/

#include "mtl/Option.hpp"
#include <criterion/criterion.h>
#include <functional>
#include <string>
#include <unordered_set>

class Unique {
public:
    Unique()
        : m_val(0)
    {
    }

    explicit Unique(int val)
        : m_val(val)
    {
    }

    Unique(const Unique&) = delete;

    Unique(Unique&& other)
        : m_val(other.m_val)
    {
    }

    ~Unique()
    {
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
};

Test(option, default_constructor_is_none)
{
    mtl::Option<Unique> opt;

    cr_assert(!opt);
}

Test(option, some_constructor)
{
    mtl::Option<Unique> opt = mtl::some<Unique>(4);

    cr_assert(opt);
    cr_assert_eq(opt.unwrap(), 4);
    cr_assert(!opt);
}

Test(option, some_default_constructor)
{
    auto opt = mtl::some<Unique>();

    cr_assert(opt);
    cr_assert_eq(opt.unwrap(), 0);
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

Test(option, unwrap_none)
{
    cr_assert_any_throw(mtl::none<int>().unwrap());
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

Test(option, as_mut)
{
    mtl::Option<int> opt = mtl::some<int>(3);
    mtl::Option<int&> mut = opt.as_mut();

    cr_assert(mut);
    mut.unwrap() = 5;
    cr_assert_eq(opt.unwrap(), 5);
}

Test(option, as_ref_none)
{
    mtl::Option<const int&> ref = mtl::none<int>().as_ref();

    cr_assert(!ref);
}

Test(option, as_mut_none)
{
    mtl::Option<int&> mut = mtl::none<int>().as_mut();

    cr_assert(!mut);
}

Test(option, as_ref_from_const)
{
    const mtl::Option<int> opt = mtl::some<int>(3);
    mtl::Option<const int&> ref = opt.as_ref();

    cr_assert_eq(ref.unwrap(), 3);
}

Test(option, map_as_ref)
{
    const mtl::Option<Unique> mbOrig = mtl::some<Unique>(3);
    mtl::Option<const Unique&> mbRef = mbOrig.as_ref();
    mtl::Option<Unique> mbDoubled = mbRef.map([](const Unique& u) {
        return Unique(u.get() * 2);
    });

    cr_assert(mbOrig);
    cr_assert(!mbRef);
    cr_assert(mbDoubled);
    cr_assert_eq(mbDoubled, mtl::some<Unique>(6));
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

Test(option, hash_owned)
{
    mtl::Option<int> owned;
    mtl::Option<int&> mut;
    mtl::Option<const int&> ref;

    std::hash<mtl::Option<int>>()(owned);
    std::hash<mtl::Option<int&>>()(mut);
    std::hash<mtl::Option<const int&>>()(ref);
}

Test(option, hash_set)
{
    std::unordered_set<mtl::Option<std::string>> set;

    set.emplace();
    set.emplace();
    set.emplace("hi");
    set.emplace("hello");
    cr_assert_neq(set.find(mtl::none<std::string>()), set.end());
    cr_assert_neq(set.find(mtl::some<std::string>("hi")), set.end());
    cr_assert_neq(set.find(mtl::some<std::string>("hello")), set.end());
    cr_assert_eq(set.find(mtl::some<std::string>("blabla")), set.end());
}
