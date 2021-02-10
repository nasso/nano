/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Pin
*/

#ifndef PIN_HPP_
#define PIN_HPP_

#include "IComponent.hpp"
#include "Subject.hpp"
#include <memory>
#include <vector>

namespace nts {

class Pin : rtk::Subject<Tristate> {
public:
    Pin();
    ~Pin();

    void connect(std::weak_ptr<Pin> pin);

private:
    std::weak_ptr<Pin> m_parent;
    std::vector<std::weak_ptr<Pin>> m_children;
};

}

#endif /* !PIN_HPP_ */
