#include "Examples.h"

Examples::Examples()
{
    push_back(Ex01());
    push_back(Ex02());
    push_back(Ex03());
    push_back(Ex04());
    push_back(Ex05());
}

State Examples::Get(size_t id) const
{
    return at(id);
}

State Examples::Ex01()
{
    const std::array< char, State::TILENO > tab{
     2,  8,  3,  5,  9,
     1,  6,  7,  4,  0,
    11, 12, 13, 14, 10,
    16, 17, 18, 19, 15,
    21, 22, 23, 24, 20,
    };

    return State{ tab };
}


State Examples::Ex02()
{
    const std::array< char, State::TILENO > tab{
     1,  7,  2,  8,  4,
     6,  9, 13,  3,  5,
    11, 17, 12, 14, 10,
    16, 18, 23, 22, 15,
    21, 24, 19, 20,  0,
    };

    return State{ tab };
}


State Examples::Ex03()
{
    const std::array< char, State::TILENO > tab{
     1,  4,  3,  5, 10,
     6,  7,  8,  2,  9,
    23, 11, 13, 14, 15,
    12,  0, 18, 24, 19,
    17, 16, 21, 22, 20,
    };

    return State{ tab };
}


State Examples::Ex04()
{
    const std::array< char, State::TILENO > tab{
     0,  6,  2,  9,  4,
    17,  1,  3, 10, 14,
    22,  8,  7, 12,  5,
    21, 11, 18, 13, 24,
    16, 23, 15, 20, 19,
    };

    return State{ tab };
}


State Examples::Ex05()
{
    const std::array< char, State::TILENO > tab{
     2,  3,  7,  9,  4,
    11,  1, 14,  5, 10,
    12, 17, 15, 19,  8,
    22,  6, 13,  0, 23,
    16, 21, 18, 24, 20,
    };

    return State{ tab };
}
