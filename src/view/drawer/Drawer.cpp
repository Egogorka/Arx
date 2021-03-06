//
// Created by Meevere on 21.11.2021.
//

#include "Drawer.h"
#include "src/view/Color.h"

Drawer::Drawer(Vector2f resolution): resolution(resolution){
    window.create(sf::VideoMode(resolution[0], resolution[1]), "Test", sf::Style::Default);
    window.setFramerateLimit(60);
}

void Drawer::draw_circle(float radius, const Vector2i &position, const Color& color) {
    sf::CircleShape shape(radius);
    shape.setPosition(get_sf_vector(position));
    shape.setFillColor(color.getSFMLColor());
    window.draw(shape);
}

void Drawer::draw_circle(float radius, const Vector2i &position) {
    draw_circle(radius, position, Color::Green);
}

void Drawer::draw_line(const Vector2i &a, const Vector2i &b, const Color &color) {
    sf::VertexArray line{sf::Lines, 2};
//    sf::VertexArray line[] = {
//            sf::Vertex{sf::Vector2f{(float)a[0], (float)a[1]}},
//            sf::Vertex{sf::Vector2f{(float)b[0], (float)b[1]}}
//    };
    line[0].position = get_sf_vector(a);
    line[1].position = get_sf_vector(b);

    line[0].color = color.getSFMLColor();
    line[1].color = color.getSFMLColor();
    window.draw(line);
}

void Drawer::clear() {
    window.clear();
}

void Drawer::display() {
    window.display();
}

std::queue<DrawerEvent> Drawer::handle_events() {
    std::queue<DrawerEvent> events;
    sf::Event event{};
    while (window.pollEvent(event)){
        Event temp;
        switch (event.type) {
            case sf::Event::Closed:
                temp = Event{DrawerEvent::EventType::Exit, Event::Exit{}};
                break;
            case sf::Event::MouseButtonPressed:
                temp = Event{Event::EventType::MousePressed, Event::MouseClick{
                        event.mouseButton.button,
                        Vector2i{event.mouseButton.x, event.mouseButton.y}
                }};
                break;
            case sf::Event::MouseButtonReleased:
                temp = Event{Event::EventType::MouseReleased, Event::MouseClick{
                        event.mouseButton.button,
                        Vector2i{event.mouseButton.x, event.mouseButton.y}
                }};
                break;
            case sf::Event::MouseMoved:
                temp = Event{Event::EventType::MouseMove, Event::MouseMove{
                    Vector2i{event.mouseMove.x, event.mouseMove.y}
                }};
                break;
            case sf::Event::MouseWheelScrolled:
                temp = Event{Event::EventType::MouseScroll, Event::MouseScroll{event.mouseWheelScroll}};
            default:
                break;
        }
        if( temp.type != Event::EventType::Invalid ) {
            evoke(temp);
            events.push(temp);
        }
    }
    return events;
}

Vector2f Drawer::getSize() {
    return Vector2f{(float)window.getSize().x, (float)window.getSize().y};
}

sf::Vector2f Drawer::get_sf_vector(const Vector2i &vec) {
    return { (float)vec.x(), (float)vec.y() };
}

sf::Vector2f Drawer::get_sf_vector(const Vector2f &vec) {
    return { vec.x(), vec.y() };
}
