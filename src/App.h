//
// Created by Meevere on 11.08.2022.
//

#ifndef ARX_SRC_APP_H
#define ARX_SRC_APP_H

#include <memory>
#include "Drawer.h"
#include "utility/Eventer.h"

#define RESOLUTION Vector2i{1000, 800}

class App {
    std::shared_ptr<Drawer> drawer;
    Eventer<sf::Event,sf::Event::Count> eventer;

    bool is_running;

public:
    App();

    void start();
    void end();
};


#endif //ARX_SRC_APP_H
