//
// Created by Meevere on 11.08.2022.
//

#include "App.h"

App::App()
: is_running(false){
    drawer = std::make_shared<Drawer>(RESOLUTION);
    eventer.add_event_listener(sf::Event::EventType::Closed, [this](){
        this->end();
    });
}

void App::start() {
    is_running = true;
    while (is_running) {
        sf::Event event{};
        while (drawer->pollEvent(event)){
            eventer.evoke(event);
        }
    }
}


void App::end() {
    is_running = false;
}
