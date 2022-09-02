//
// Created by meeve on 22.08.2022.
//

#ifndef ARX_SRC_DRAWER_MULTISPRITEC_H
#define ARX_SRC_DRAWER_MULTISPRITEC_H

#include <SFML/Graphics.hpp>

#include "utility/vector/Vector.h"
#include "utility/vector/sfConvert.h"

#include "src/drawer/Multisprite.h"

struct MultispriteC {
    Multisprite* multisprite;

    int animation = 0;
    float current = 0;
    float multiplier;
};


#endif //ARX_SRC_DRAWER_MULTISPRITEC_H
