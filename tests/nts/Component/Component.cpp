#include "AComponent.hpp"
#include <criterion/criterion.h>

class TestComponent : public nts::AComponent {
public:
    TestComponent()
    {
        m_pins = std::vector<nts::Pin>(3);
        m_inputPins = { 0, 1 };
        _init();
    }

protected:
    void _simulate() override;
};

void TestComponent::_simulate()
{
}

Test(testComponent, constructor)
{
    TestComponent c;
}

Test(testComponent, link)
{
    TestComponent a;
    TestComponent b;

    a.setLink(2, b, 0);
    a.setLink(2, b, 1);
}