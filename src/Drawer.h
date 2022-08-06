//
// Created by meeve on 02.08.2022.
//

#ifndef ARX_DRAWER_H
#define ARX_DRAWER_H

#include <SFML/Graphics.hpp>
#include "vector/Vector.h"
#include <vector>

#include "Box.h"

class Drawer {
protected:
    sf::View camera;
    std::vector<sf::Texture> textures;

    sf::Window window;
public:
    Drawer(const Vector2i& resolution);


};


#endif //ARX_DRAWER_H
