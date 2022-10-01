//
// Created by Meevere on 06.08.2022.
//

#include "TileSprite.h"

constexpr uint8_t rotl(uint8_t input, uint8_t moves){
    return (input << moves) | (input >> (8 - moves));
}

constexpr uint8_t rotr(uint8_t input, uint8_t moves){
    return (input >> moves) | (input << (8 - moves));
}

uint8_t LU_mask = 0b00000111;

int subtypes_map(uint8_t neighbors){
    switch (neighbors) {
        case 0b000:
            return 3;
        case 0b001:
            return 1;
        case 0b010:
            return 3;
        case 0b011:
        case 0b100:
            return 1;
        case 0b101:
            return 2;
        case 0b110:
            return 1;
        default:
            return 0;
    }
}

int rotations_map(uint8_t neighbors){
    switch (neighbors) {
        case 0b000:
            return 2;
        case 0b001:
            return 1;
        case 0b010:
            return 2;
        case 0b011:
            return 1;
        case 0b100:
        case 0b101:
        case 0b110:
            return 2;
        default:
            return 0;
    }
}

uint8_t Type::rotate(uint8_t type, Direction direction) {
    return rotr(type, 2 * static_cast<uint8_t>(direction));
}

Type::Type(uint8_t neighbors)
: neighbors(neighbors), rotations(), subtypes() {
    for(int i=0; i<4; i++){
        auto dir = static_cast<Direction>(i);
        uint8_t rot_neighbors = rotate(neighbors, dir) & LU_mask;
        rotations[i]= (rotations_map(rot_neighbors) - i + 4 ) % 4;
        subtypes[i] = subtypes_map(rot_neighbors);
    }
}

TileSpriteFactory::TileSpriteFactory(sf::Texture &texture, Vector2i texture_pos)
:texture(&texture), texture_pos(texture_pos){}

sf::Sprite TileSpriteFactory::getSubTile(const Type &type, Direction dir) {
    sf::Sprite out;
    if(texture == nullptr)
        return out;

    auto i = static_cast<int>(dir);
    auto subtype = type.subtypes[i];
    auto rotation = type.rotations[i];

    out.setTexture(*texture);

    auto pos = texture_pos + Vector2i{16*(subtype % 2), 16*((subtype >> 1) % 2)};
    auto size = Vector2i{16,16};

    out.setTextureRect(sf::IntRect(pos[0], pos[1], size[0], size[0]));
    out.setOrigin(8,8);
    out.setRotation(float((360 - rotation*90) % 360));
    return out;
}

TileSprite TileSpriteFactory::getTileSprite(const Type& type) {
    std::array<sf::Sprite,4> out;
    for(int i=0; i<4; i++){
        auto sub_sprite = getSubTile(type, static_cast<Direction>(i));
        sub_sprite.setPosition(sf::Vector2f{16.0f*float( (i == 1 or i == 2) ? 1 : 0 ), 16.0f*float(i >> 1)} + sf::Vector2f{8,8});
        out[i] = sub_sprite;
    }
    return TileSprite{out};
}

TileSpriteFactory::TileSpriteFactory()
: texture(nullptr), texture_pos() {}

TileSprite::TileSprite(const std::array<sf::Sprite, 4>& subtiles) // NOLINT(modernize-pass-by-value)
: subtiles(subtiles){}

void TileSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for(auto& sprite : subtiles){
        target.draw(sprite, states);
    }
}

