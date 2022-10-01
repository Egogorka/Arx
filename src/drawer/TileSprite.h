//
// Created by Meevere on 06.08.2022.
//

#ifndef ARX_SRC_DRAWER_TILESPRITE_H
#define ARX_SRC_DRAWER_TILESPRITE_H

#include <SFML/Graphics.hpp>
#include <array>
#include "vector/Vector.h"

enum class Direction {
    LU = 0, RU, RD, LD
};

/**
 * Type of tile, consists of 4 subtile types
 */
struct Type {
    /**
     * bits that correspond to neighboring cells (1 - same type as center one, 0 - other type)
     * they are numbered in this manner:
     * 123
     * 0#4
     * 765
     */
    uint8_t neighbors;

    // arrays with 4 entries that correspond to each subtile
    // from 0 to 3 - type of subtile
    array<int,4> subtypes;
    // from 0 to 3 - amount of anti-clockwise rotation (in 90 degrees)
    array<int,4> rotations;

    static uint8_t rotate(uint8_t type, Direction direction);

    explicit Type(uint8_t neighbors);
};

struct TileSprite;

struct TileSpriteFactory {
protected:
    // texture sheet
    sf::Texture* texture = nullptr;

    // position of tile texture on texture sheet
    Vector2i texture_pos;
    // size of texture is hardcoded to be 32x32px

    sf::Sprite getSubTile(const Type& type, Direction dir);
public:
    TileSpriteFactory();

    TileSpriteFactory(sf::Texture &texture, Vector2i texture_pos);

    TileSprite getTileSprite(const Type& type);
};

struct TileSprite : public sf::Drawable, sf::Transformable {
    std::array<sf::Sprite,4> subtiles;

    explicit TileSprite(const std::array<sf::Sprite,4>& subtiles);
    friend class TileSpriteFactory;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //ARX_SRC_DRAWER_TILESPRITE_H
