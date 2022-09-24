//
// Created by Meevere on 18.09.2022.
//

#ifndef ARX_SRC_SYSTEMS_CAMERASYSTEM_H
#define ARX_SRC_SYSTEMS_CAMERASYSTEM_H

#include "include/entt.hpp"
#include <SFML/Graphics.hpp>

#include "Drawer.h"

class CameraSystem {
    entt::registry *registry;
    Drawer* drawer;
public:
    void update(sf::Time& time);

    CameraSystem(entt::registry *registry, Drawer *drawer);
};


#endif //ARX_SRC_SYSTEMS_CAMERASYSTEM_H
