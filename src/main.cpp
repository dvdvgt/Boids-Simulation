#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Flock.h"
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "Boids Simulation");

    // create the particle system
    Flock swarm(750, window);

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
            } else if (event.key.code == sf::Keyboard::PageUp) {
                swarm.set_num_particles(swarm.get_num_particles() + 1);
            } else if (event.key.code == sf::Keyboard::PageDown) {
                swarm.set_num_particles(swarm.get_num_particles() - 1);
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
