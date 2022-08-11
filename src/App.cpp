//
// Created by Meevere on 11.08.2022.
//

#include "App.h"

App::App()
: is_running(false){
    drawer = std::make_shared<Drawer>(RESOLUTION);
}

void App::start() {
    is_running = true;
    while (is_running) {
        sf::Event event{};
        while (drawer->pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    end();
                    break;
                default:
                    break;
            }
        }
    }
}


void App::end() {
    is_running = false;
}
