//
// Created by Meevere on 13.08.2022.
//

#ifndef ARX_SRC_DRAWER_MULTISPRITE_H
#define ARX_SRC_DRAWER_MULTISPRITE_H

#include <SFML/Graphics.hpp>

#include "utility/vector/Vector.h"
#include "utility/vector/sfConvert.h"

struct Animation {
    int length;
    float speed;

    Animation(int length, float speed);
};


struct Multisprite {
    sf::Texture* texture;

    Vector2i pos;
    Vector2i size;
    Vector2i gap;
    std::vector<Animation> animations;

    Multisprite(sf::Texture &texture, const Vector2i &pos, const Vector2i &size, const Vector2i &gap, std::vector<Animation>&& animations);
};

#endif //ARX_SRC_DRAWER_MULTISPRITE_H
