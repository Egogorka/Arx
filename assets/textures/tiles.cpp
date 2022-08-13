//
// Created by Meevere on 07.08.2022.
//

#include "tiles.h"

std::map<std::string, Tiles> tilesMap{ // NOLINT(cert-err58-cpp)
        {"None", Tiles::None},
        {"Brick", Tiles::Brick},
        {"Pollution", Tiles::Pollution}
};