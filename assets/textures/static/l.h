//
// Created by meeve on 03.08.2022.
//

#ifndef ARX_ASSETS_TEXTURES_L_H
#define ARX_ASSETS_TEXTURES_L_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "src/drawer/TileSprite.h"
#include "assets/tiles.h"

/**
 * Loads all textures in /assets/textures that are listed in textures.json
 * There is no particular order in textures themselves. It's just for storage
 * @return
 */
std::shared_ptr<std::vector<sf::Texture>> load_static_textures();


/**
 * Initializes all of TileSpriteFactories for usage in tile display
 * Vector is ordered by enum in tiles.h
 * @param textures all textures
 * @return
 */
std::shared_ptr<std::vector<TileSpriteFactory>> init_factories(const std::shared_ptr<std::vector<sf::Texture>>& textures);

#endif //ARX_ASSETS_TEXTURES_L_H
