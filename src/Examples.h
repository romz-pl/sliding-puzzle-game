#pragma once

#include "State.h"
#include <vector>

class Examples: public std::vector<State>
{
public:
    Examples();

    State Get(size_t id) const;

private:
    static State Ex01();
    static State Ex02();
    static State Ex03();
    static State Ex04();
    static State Ex05();

};
