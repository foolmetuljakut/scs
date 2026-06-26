#pragma once
#include "../std.hpp"

namespace src::combat {

    struct Terrain {
        int _cover_provision; // for how many there is cover available
        static const float _cover_factor; // how well are they covered
    };

};