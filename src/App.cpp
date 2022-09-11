//
// Created by Meevere on 11.08.2022.
//

#include "App.h"

#include "src/components/LocationC.h"
#include "src/components/PlayerC.h"
#include "src/components/CollisionC.h"

App::App()
:
    drawer(RESOLUTION), eventer(), registry(),

    spriteSystem(), tileSystem(),
    #ifdef ARX_DEBUG
    physicsSystem(&registry, &drawer),
    #else
    physicsSystem(&registry),
    #endif
    is_running(false)
{
    segments = load_segments();

    eventer.add_event_listener(sf::Event::EventType::Closed, [this](){
        this->end();
    });

    eventer.add_event_listener(sf::Event::EventType::KeyPressed,
       [this](const sf::Event& event){
           switch (event.key.code) {
               case sf::Keyboard::Comma: // <
                   drawer.parallax_scale /= 1.1;
                   break;
               case sf::Keyboard::Period: // >
                   drawer.parallax_scale *= 1.1;
                   break;
               case sf::Keyboard::Up:
                   drawer.parallax_center += Vector2f{0,.1};
                   break;
               case sf::Keyboard::Down:
                   drawer.parallax_center += Vector2f{0,-.1};
                   break;
               case sf::Keyboard::Left:
                   drawer.parallax_center += Vector2f{-.1,0};
                   break;
               case sf::Keyboard::Right:
                   drawer.parallax_center += Vector2f{.1,0};
                   break;
               case sf::Keyboard::PageUp:
                   drawer.parallax_offset += .1;
                   break;
               case sf::Keyboard::PageDown:
                   drawer.parallax_offset += -.1;
                   break;
               case sf::Keyboard::Enter:
                   std::cout << "Current parallax settings\n";
                   std::cout << "Parallax offset: " << drawer.parallax_offset << '\n';
                   std::cout << "Parallax scale:  " << drawer.parallax_scale << '\n';
                   std::cout << "Parallax center: " << drawer.parallax_center << '\n';
                   break;

               default:
                   break;
           }
       });
}

void App::start() {
    is_running = true;

    auto player = registry.create();

    registry.emplace<LocationC>(player, Vector3f{1.5,1.5,0}, Vector3f{0.01, 0.01, 0});
    registry.emplace<PlayerC>(player);
    registry.emplace<CollisionC>(player, Vector2f{27-8,32-7}, Vector2f{8,7});
    spriteSystem.assign(registry, player, Sprites::Player);

    sf::Clock clock;
    while (is_running) {
        auto time = clock.restart();

        sf::Event event{};
        drawer.clear();

        controlsSystem.update(registry, drawer);
        physicsSystem.update(this->segments->at(0).tiles, time);

        spriteSystem.render(registry, drawer, time);
        drawer.display_sprites([this](int zlevel){
            this->tileSystem.render_partial(this->segments->at(0).tiles, zlevel, drawer);
        }, 3, 0);

        while (drawer.pollEvent(event)){
            eventer.evoke(event);
        }

        drawer.display();
    }
}


void App::end() {
    is_running = false;
}
