//
// Created by Meevere on 13.08.2022.
//

#ifndef ARX_ASSETS_TEXTURES_DYNAMIC_L_H
#define ARX_ASSETS_TEXTURES_DYNAMIC_L_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "src/drawer/Multisprite.h"

/**
 * Loads all textures in /assets/textures that are listed in textures.json
 * Outer vector is indexed by types that are defined in tiles.h,
 * Inner vector correspond to multiple textures of same tile (to make it randomizable)
 * (atm no inner vector for easier implementation)
 * @return
 */
std::shared_ptr<std::vector<sf::Texture>> load_dynamic_textures();


/**
 * Initializes all MultispriteFactories that would be used in animations handling
 * @param textures - textures of multisprites
 * @return
 */
std::shared_ptr<std::vector<MultispriteFactory>> init_msprite_factories(const std::shared_ptr<std::vector<sf::Texture>>& textures);

#endif //ARX_ASSETS_TEXTURES_DYNAMIC_L_H
