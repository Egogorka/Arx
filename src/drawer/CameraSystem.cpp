//
// Created by Meevere on 18.09.2022.
//

#include "CameraSystem.h"

#include "src/components/LocationC.h"
#include "src/components/CameraLock.h"

void CameraSystem::update(sf::Time &time) {
    registry->view<LocationC, CameraLock>().each([this, &time](entt::entity entity, LocationC location){
        auto temp = drawer->get_size()/32/drawer->scale; // in tiles
        drawer->offset = location.position - Vector3f{temp[0], temp[1], 0}/2;
    });
}

CameraSystem::CameraSystem(entt::registry *registry, Drawer *drawer) : registry(registry), drawer(drawer) {}
