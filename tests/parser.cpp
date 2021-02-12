#include <criterion/criterion.h>

#include "NTSCircuit.hpp"
#include <iostream>

Test(test_parser, parser)
{
    try {
        nts::NTSCircuit m("4081_and.nts");
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
        cr_fail(CR_FAIL_CONTINUES_);
    }
}