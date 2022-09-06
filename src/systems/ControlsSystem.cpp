//
// Created by Meevere on 04.09.2022.
//

#include "ControlsSystem.h"

#include "src/components/LocationC.h"
#include "src/components/PlayerC.h"

void ControlsSystem::update(entt::registry &registry, Drawer& drawer) {
    registry.view<PlayerC, LocationC>().each([&](auto entity, LocationC& location){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            location.velocity.y() += -.01;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            location.velocity.y() += .01;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            location.velocity.x() += -.01;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            location.velocity.x() += .01;
        }
    });
}
