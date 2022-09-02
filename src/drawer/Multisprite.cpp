//
// Created by Meevere on 01.09.2022.
//

#include "Multisprite.h"

Multisprite::Multisprite(sf::Texture &texture, const Vector2i &pos, const Vector2i &size, const Vector2i &gap,
                         std::vector<Animation>&& animations)
 : texture(&texture), pos(pos), size(size), gap(gap), animations(std::move(animations)){}

Animation::Animation(int length, float speed) : length(length), speed(speed) {}
