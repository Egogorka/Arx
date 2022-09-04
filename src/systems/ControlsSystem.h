//
// Created by Meevere on 04.09.2022.
//

#ifndef ARX_SRC_SYSTEMS_CONTROLSSYSTEM_H
#define ARX_SRC_SYSTEMS_CONTROLSSYSTEM_H

#include "include/entt.hpp"

#include "src/Drawer.h"

class ControlsSystem {
public:
    void update(entt::registry& registry, Drawer& drawer);
};


#endif //ARX_SRC_SYSTEMS_CONTROLSSYSTEM_H
