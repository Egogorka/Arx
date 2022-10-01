//
// Created by meeve on 03.08.2022.
//

#include "l.h"
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>

std::shared_ptr<std::vector<sf::Texture>> load_static_textures() {
    std::ifstream f("../assets/textures/static/texture.json");

    auto out = std::make_shared<std::vector<sf::Texture>>();
    json array_data = json::parse(f);

    out->reserve(array_data.size());
    for(auto& data : array_data){
        std::string path = "../assets/textures/static/" + data["filename"].get<std::string>();
        out->emplace_back();
        auto texture = out->rbegin();
        if(!texture->loadFromFile(path)) {
            std::cout << "Could not load texture with filename: " << data["filename"] << '\n';
            break;
        }
    }
    f.close();
    return out;
}

std::shared_ptr<std::vector<TileSpriteFactory>> init_factories(const std::shared_ptr<std::vector<sf::Texture>>& textures) {
    // Poor design - need to open textures.json twice
    std::ifstream f("../assets/textures/static/texture.json");

    auto out = std::make_shared<std::vector<TileSpriteFactory>>();
    json data = json::parse(f);

    // Walk the json to reserve memory for vector
    int size = 0;
    for(auto& file_data : data) {
        for (auto &tile_data : file_data["tiles"]) {
            size += tile_data.size();
        }
    }
    out->resize(size);

    auto iter = textures->begin();
    for(auto& file_data : data){
        for(auto& tiles_data : file_data["tiles"]) {
            auto pos  = Vector2i{tiles_data["pos"][0].get<int>(), tiles_data["pos"][1].get<int>()};
            auto tile = tiles_data["name"].get<Tiles>();
            out->at(static_cast<int>(tile)) = TileSpriteFactory(*iter, pos);
        }
        iter++;
    }
    f.close();
    return out;
}

