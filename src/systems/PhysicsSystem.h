//
// Created by Meevere on 04.09.2022.
//

#ifndef ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H
#define ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H

#include "include/entt.hpp"

#include "utility/ndarray/ndArrayView.h"
#include "assets/tiles.h"

#include <SFML/Graphics.hpp>

/**
 * Handles moving and collisions
 */
class PhysicsSystem {
public:
    void update(entt::registry& registry, const ndArrayView<Tiles, 2> &tiles, sf::Time& time);
};


#endif //ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H
