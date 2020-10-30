#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Swarm.h"
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 512), "Particles");

    // create the particle system
    Swarm swarm(300, window);

    // create a clock to track the elapsed time
    sf::Clock clock;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // make the particle system emitter follow the mouse
        //sf::Vector2i mouse = sf::Mouse::getPosition(window);
        //particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        swarm.update(elapsed);

        // draw it
        window.clear();
        window.draw(swarm);
        window.display();
        //window.setFramerateLimit(60);
    }

    return 0;
}
