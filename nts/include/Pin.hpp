/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Pin
*/

#ifndef PIN_HPP_
#define PIN_HPP_

#include "BehaviorSubject.hpp"
#include "IComponent.hpp"
#include <memory>
#include <vector>

namespace nts {

class Pin : public rtk::BehaviorSubject<Tristate> {
public:
    Pin();
    ~Pin() = default;

    void gt(std::weak_ptr<Pin> pin);

private:
    std::weak_ptr<Pin> m_parent;
    std::vector<std::weak_ptr<Pin>> m_children;
};

}

#endif /* !PIN_HPP_ */
