//
// Created by Meevere on 13.08.2022.
//

#ifndef ARX_SRC_DRAWER_MULTISPRITE_H
#define ARX_SRC_DRAWER_MULTISPRITE_H

#include <SFML/Graphics.hpp>

#include "utility/vector/Vector.h"
#include "utility/vector/sfConvert.h"

class MultispriteFactory {

    sf::Texture* texture;

    // Multisprite info
    Vector2i pos;
    Vector2i size;
    Vector2i gap;

public:
    MultispriteFactory(sf::Texture &texture, const Vector2i &pos, const Vector2i &size, const Vector2i &gap);

    sf::Sprite get(int animation, int frame);
};


#endif //ARX_SRC_DRAWER_MULTISPRITE_H
