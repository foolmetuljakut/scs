#include "UnitParamsFactory.hpp"

namespace src::unit {

UnitParams UnitParamsFactory::prussia1866() {
    return UnitParams {
        0, 0, // ids
        1000, 1000, 0, // troops
        25, 25, // morale
        0.1152f, 0, 0, // normal (6/min as 1/h * 0.32 hit chance), explosive, artillery
        600, // eff range
    };
}

UnitParams UnitParamsFactory::austria1866() {
    return UnitParams {
        1, 0, // ids
        1000, 1000, 0, // troops
        25, 25, // morale
        0.0432f, 0, 0, // normal (2/min as 1/h * 0.36 hit chance), explosive, artillery
        107, // eff range
    };
}

};