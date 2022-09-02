//
// Created by meeve on 24.08.2022.
//

#ifndef TILES_H_SRC_SYSTEMS_SPRITESYSTEM_H
#define TILES_H_SRC_SYSTEMS_SPRITESYSTEM_H

#include <memory>
#include <vector>

#include "src/drawer/Multisprite.h"
#include "components/MultispriteC.h"

#include "assets/textures/dynamic/dynamic.h"

#include "include/entt.hpp"
#include "src/Drawer.h"

class SpriteSystem {
    std::shared_ptr<std::vector<sf::Texture>> msprite_textures;
    std::shared_ptr<std::vector<Multisprite>> msprites;

    sf::Sprite getSprite(MultispriteC& sprite);
public:
    SpriteSystem();
    void assign(entt::registry& registry, entt::entity& entity, Sprites sprite);

    void render(entt::registry& registry, Drawer& drawer, sf::Time& time);
};


#endif //TILES_H_SRC_SYSTEMS_SPRITESYSTEM_H
