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

class Drawer {
protected:
    std::shared_ptr<std::vector<sf::Texture>> textures;
    std::shared_ptr<std::vector<TileSpriteFactory>> factories;

    sf::RenderWindow window;

    static Type getTileType(const ndArrayView<Tiles,2>& tiles, Vector2i position);
    void draw(const sf::Drawable& drawable, float zlevel);
public:
    explicit Drawer(const Vector2i& resolution);



    bool pollEvent(sf::Event& event);

    void drawTiles(const ndArrayView<Tiles,2>& tiles);
    void display();
    void clear();
};


#endif //ARX_DRAWER_H
