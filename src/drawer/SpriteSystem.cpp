//
// Created by meeve on 24.08.2022.
//

#include "SpriteSystem.h"
#include "src/components/LocationC.h"

#include "assets/textures/dynamic/l.h"

void SpriteSystem::render(entt::registry& registry, Drawer &drawer, sf::Time& time) {
   auto view = registry.view<MultispriteC, LocationC>();
   drawer.reserve_queue(view.size_hint());
   view.each([&](auto entity, MultispriteC& sprite, LocationC& location){
        // Update the sprite
        sprite.current += time.asMilliseconds() / 16 * (sprite.multisprite->animations[sprite.animation].speed * sprite.multiplier); // amount of steps
        while(sprite.current >= sprite.multisprite->animations[sprite.animation].length) sprite.current -= sprite.multisprite->animations[sprite.animation].length;

        // Render it
        drawer.queue(getSprite(sprite), location.position);
   });
}

sf::Sprite SpriteSystem::getSprite(MultispriteC &sprite) {
    sf::Vector2i position{
            sprite.multisprite->pos[0] + (sprite.multisprite->size[0] + sprite.multisprite->gap[0]) * int(sprite.current),
            sprite.multisprite->pos[1] + (sprite.multisprite->size[1] + sprite.multisprite->gap[1]) * sprite.animation
    };
    sf::Sprite out;
    out.setTexture(*sprite.multisprite->texture);
    out.setTextureRect(sf::IntRect{position, toSFMLvector(sprite.multisprite->size)});
    return out;
}

SpriteSystem::SpriteSystem() :
msprite_textures(load_dynamic_textures()), msprites(init_msprites(msprite_textures)) {}

void SpriteSystem::assign(entt::registry &registry, entt::entity &entity, Sprites sprite) {
    registry.emplace<MultispriteC>(
            entity,
            &msprites->at(static_cast<int>(sprite)),
            0, 0.f, 1.f
    );
}
