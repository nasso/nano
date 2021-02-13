#include <criterion/criterion.h>

#include "NTSCircuit.hpp"
#include <iostream>

Test(test_parser, parser)
{
    try {
        nts::NTSCircuit m("components/4081.nts");
    } catch (std::runtime_error& e) {
        cr_assert_fail("%s", e.what());
    }
}
