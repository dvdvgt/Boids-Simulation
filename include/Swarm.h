//
// Created by dvd on 28.10.20.
//

#ifndef PARTICLESYSTEM_SWARM_H
#define PARTICLESYSTEM_SWARM_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "Particle.h"

class Swarm : public sf::Drawable {
private:
    sf::Window &window;
    int num_particles;
    std::vector<std::unique_ptr<Rule>> rules;

    void init_rules();

    void set_particle_rules();

    void init_particles();

public:
    std::vector<Particle> particles;

    Swarm(unsigned int count, sf::Window &win);

    void set_num_particles(int num);

    void update(sf::Time delta);

    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
};

#endif //PARTICLESYSTEM_SWARM_H
