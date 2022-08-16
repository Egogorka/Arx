//
// Created by Meevere on 13.08.2022.
//

#include "Multisprite.h"

MultispriteFactory::MultispriteFactory(
        sf::Texture &texture, const Vector2i &pos, const Vector2i &size, const Vector2i &gap)
: texture(&texture), pos(pos), size(size), gap(gap) {}

sf::Sprite MultispriteFactory::get(int animation, int frame) {
    sf::Vector2i position{
            pos[0] + (size[0] + gap[0]) * frame,
            pos[1] + (size[1] + gap[1]) * animation
    };
    sf::Sprite out;
    out.setTexture(*texture);
    out.setTextureRect(sf::IntRect{position, toSFMLvector(size)});
    return out;
}
