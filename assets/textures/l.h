//
// Created by meeve on 03.08.2022.
//

#ifndef ARX_ASSETS_TEXTURES_L_H
#define ARX_ASSETS_TEXTURES_L_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "src/drawer/TileSprite.h"
#include "tiles.h"

/**
 * Loads all textures in /assets/textures that are listed in textures.json
 * Outer vector is indexed by types that are defined in tiles.h,
 * Inner vector correspond to multiple textures of same tile (to make it randomizable)
 * (atm no inner vector for easier implementation)
 * @return
 */
std::shared_ptr<std::vector<sf::Texture>> load_textures();


/**
 * Initializes all of TileSpriteFactories for usage in tile display
 * Vector is indexed by types that are defined in tiles.h
 * @param textures all textures
 * @return
 */
std::shared_ptr<std::vector<TileSpriteFactory>> init_factories(const std::shared_ptr<std::vector<sf::Texture>>& textures);

#endif //ARX_ASSETS_TEXTURES_L_H
