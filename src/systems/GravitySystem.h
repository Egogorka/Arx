//
// Created by Meevere on 11.09.2022.
//

#ifndef ARX_SRC_SYSTEMS_GRAVITYSYSTEM_H
#define ARX_SRC_SYSTEMS_GRAVITYSYSTEM_H

#include "main.h"
#include "include/entt.hpp"

#include "src/components/LocationC.h"
#include "src/components/GravityC.h"

#include <SFML/Graphics.hpp>

class GravitySystem {
    entt::registry *registry;

public:
    void update(sf::Time& time);

    explicit GravitySystem(entt::registry *registry);
};

#endif //ARX_SRC_SYSTEMS_GRAVITYSYSTEM_H
