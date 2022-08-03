//
// Created by meeve on 02.08.2022.
//

#ifndef ARX_DRAWER_H
#define ARX_DRAWER_H

#include <SFML/Graphics.hpp>
#include "vector/Vector.h"

#include "Box.h"

class Drawer {
protected:
    Box2 camera;

public:
    Drawer(const Vector2f& size);

};


#endif //ARX_DRAWER_H
