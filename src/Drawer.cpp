//
// Created by meeve on 02.08.2022.
//

#include "Drawer.h"

Drawer::Drawer(const Vector2i &resolution) {
    window.create(sf::VideoMode(resolution.x(), resolution.y()), "Arx", sf::Style::Default);
    window.setFramerateLimit(60);


}
