//
// Created by Meevere on 17.12.2021.
//

#include "Vector.h"

Vector2f get_vector_i2f(Vector2i vec){
    return {(float)vec.x(), (float)vec.y()};
}

Vector3f get_vector_i2f(Vector3i vec){
    return {(float)vec.z(), (float)vec.x(), (float)vec.y()};
}

Vector2i get_vector_f2i(Vector2f vec){
    return {(int)vec.x(), (int)vec.y()};
}

Vector3i get_vector_f2i(Vector3i vec){
    return {(int)vec.z(), (int)vec.x(), (int)vec.y()};
}

