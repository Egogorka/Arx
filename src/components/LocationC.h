//
// Created by meeve on 25.08.2022.
//

#ifndef TILES_H_SRC_COMPONENTS_LOCATIONC_H
#define TILES_H_SRC_COMPONENTS_LOCATIONC_H

#include "utility/vector/Vector.h"

/**
 * In units of tile and originated from top left corner
 */
struct LocationC {
    Vector3f position;
    Vector3f velocity;

    inline explicit LocationC(const Vector3f& position): position(), velocity() {};
};

#endif //TILES_H_SRC_COMPONENTS_LOCATIONC_H
