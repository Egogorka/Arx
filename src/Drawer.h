//
// Created by meeve on 02.08.2022.
//

#ifndef ARX_DRAWER_H
#define ARX_DRAWER_H

#include <SFML/Graphics.hpp>
#include "vector/Vector.h"
#include <vector>
#include <memory>


#include "utility/ndarray/ndArrayView.h"
#include "assets/textures/tiles.h"
#include "src/drawer/TileSprite.h"

#include "src/drawer/Multisprite.h"

class Drawer {
protected:
    std::shared_ptr<std::vector<sf::Texture>> static_textures;
    std::shared_ptr<std::vector<TileSpriteFactory>> factories;

    std::shared_ptr<std::vector<sf::Texture>> msprite_textures;
    std::shared_ptr<std::vector<MultispriteFactory>> msprite_factories;

    sf::RenderWindow window;

    static Type getTileType(const ndArrayView<Tiles,2>& tiles, Vector2i position);
    void draw(const sf::Drawable& drawable, const Vector2f& pos, float zlevel, sf::Transform transform = sf::Transform::Identity);
public:
    explicit Drawer(const Vector2i& resolution);

    Vector2f parallax_center{0.5f,0.0f};
    float parallax_offset = 5.0f;
    float parallax_scale = 0.15f;
    float scale = 2;

    bool pollEvent(sf::Event& event);

    void drawMSprite(int index, const Vector3f& pos, int animation, int frame);

    void drawTiles(const ndArrayView<Tiles,2>& tiles);
    void drawTiles(const ndArrayView<Tiles,2>& tiles, float zlevel);
    void display();
    void clear();

};


#endif //ARX_DRAWER_H
