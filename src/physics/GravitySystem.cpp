//
// Created by Meevere on 11.09.2022.
//

#include "GravitySystem.h"

void GravitySystem::update(sf::Time& time) {
    registry->view<LocationC, GravityC>().each([this, &time](entt::entity entity, LocationC& location){
        location.velocity += GravityC::g * time.asMilliseconds() / 16;
    });
}

GravitySystem::GravitySystem(entt::registry *registry) : registry(registry) {}
