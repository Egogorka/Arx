//
// Created by Meevere on 13.08.2022.
//

#include "l.h"
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>

std::shared_ptr<std::vector<sf::Texture>> load_dynamic_textures() {
    std::ifstream f("../assets/textures/dynamic/texture.json");

    auto out = std::make_shared<std::vector<sf::Texture>>();
    json array_data = json::parse(f);

    out->reserve(array_data.size());
    std::cout << "Loading textures: ...\n";
    for(auto& data : array_data){
        std::string path = "../assets/textures/dynamic/" + data["filename"].get<std::string>();
        out->emplace_back();
        auto texture = out->rbegin();
        std::cout << "/assets/textures/dynamic/" << data["filename"] << '\n';
        if(!texture->loadFromFile(path)) {
            std::cout << "Could not load texture with filename: " << data["filename"].get<std::string>() << '\n';
            break;
        }
    }
    f.close();
    return out;
}

std::shared_ptr<std::vector<MultispriteFactory>> init_msprite_factories(const std::shared_ptr<std::vector<sf::Texture>>& textures) {
    // Poor design - need to open textures.json twice
    std::ifstream f("../assets/textures/dynamic/texture.json");

    // Each MultispriteFactory corresponds to one entry in json[i].textures[j] - so there are more factories than textures
    auto out = std::make_shared<std::vector<MultispriteFactory>>();
    json json_files = json::parse(f);

    // Walk the json to reserve memory for vector
    int length = 0;
    for(auto& json_file : json_files) {
        length += json_file["textures"].size();
    }
    out->reserve(length);

    auto iter = textures->begin();
    for(auto& json_file : json_files){
        for(auto& json_texture : json_file["textures"]) {
            auto pos = Vector2i{json_texture["pos"][0].get<int>(), json_texture["pos"][1].get<int>()};
            auto size = Vector2i{json_texture["size"][0].get<int>(), json_texture["size"][1].get<int>()};
            auto gap = Vector2i{json_texture["gap"][0].get<int>(), json_texture["gap"][1].get<int>()};
            out->emplace_back(*iter, pos, size, gap);
        }
        iter++;
    }
    f.close();
    return out;
}

