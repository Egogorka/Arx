//
// Created by meeve on 03.08.2022.
//

#include "l.h"
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>

std::shared_ptr<std::vector<sf::Texture>> load_textures() {
    std::ifstream f("../assets/textures/textures.json");

    auto out = std::make_shared<std::vector<sf::Texture>>();
    json array_data = json::parse(f);

    out->reserve(array_data.size());
    for(auto& data : array_data){
        std::string path = "../assets/textures/" + data["filename"].get<std::string>();
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
    std::ifstream f("../assets/textures/textures.json");

    auto out = std::make_shared<std::vector<TileSpriteFactory>>();
    json textures_data = json::parse(f);

    // Walk the json to reserve memory for vector
    int size = 0;
    for(auto& texture_data : textures_data) {
        for (auto &tiles_data : texture_data["tiles"]) {
            size += tiles_data.size();
        }
    }
    out->reserve(size);

    auto iter = textures->begin();
    for(auto& texture_data : textures_data){
        for(auto& tiles_data : texture_data["tiles"]) {
            auto pos = Vector2i{tiles_data["pos"][0].get<int>(), tiles_data["pos"][1].get<int>()};
            out->emplace_back(*iter, pos);
        }
    }
    f.close();
    return out;
}

