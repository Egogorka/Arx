//
// Created by Meevere on 13.08.2022.
//

#ifndef ARX_UTILITY_VECTOR_SFCONVERT_H
#define ARX_UTILITY_VECTOR_SFCONVERT_H

#include <SFML/System/Vector2.hpp>
#include "Vector.h"

template<typename T>
static sf::Vector2<T> toSFMLvector(Vector<T,2> vector){
    return sf::Vector2<T>{vector[0], vector[1]};
}

template<typename T>
static Vector<T,2> fromSFMLvector(sf::Vector2<T> vector){
    return Vector<T,2>{vector[0], vector[1]};
}

#endif //ARX_UTILITY_VECTOR_SFCONVERT_H
