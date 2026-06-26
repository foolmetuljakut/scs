#pragma once
#include "../std.hpp"
#include "../unit/CamoType.hpp"

namespace src::combat {

    struct Terrain {
        int _cover_provision; // for how many there is cover available
        int _max_distance;
        src::unit::CamoType _terrain_type; // the kind of color scheme the terrain is colored in
        
        static const float _cover_factor; // how well are they covered
        static const float _camo_factor; // how well you remain hidden with a matching color pattern in your environment
    };

};