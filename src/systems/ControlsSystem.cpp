//
// Created by Meevere on 04.09.2022.
//

#include "ControlsSystem.h"

#include "src/components/LocationC.h"
#include "src/components/PlayerC.h"

void ControlsSystem::update(entt::registry &registry, Drawer& drawer) {
    registry.view<PlayerC, LocationC>().each([&](auto entity, LocationC& location){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            location.position.y() += -.1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            location.position.y() += .1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            location.position.x() += -.1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            location.position.x() += .1;
        }
    });
}
