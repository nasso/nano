#include "Pin.hpp"

nts::Pin::Pin()
    : rtk::BehaviorSubject<Tristate>(UNDEFINED)
{
}