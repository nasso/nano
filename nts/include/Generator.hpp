/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Generator
*/

#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include "AComponent.hpp"

namespace nts {

template <typename T>
class Generator<T> : public AComponent {
public:
    ~Generator();
};

}

#endif /* !GENERATOR_HPP_ */
