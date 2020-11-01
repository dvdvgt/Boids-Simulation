//
// Created by dvd on 28.10.20.
//

#ifndef PARTICLESYSTEM_FLOCK_H
#define PARTICLESYSTEM_FLOCK_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "Particle.h"
#include "Rule.h"

class Flock : public sf::Drawable {
private:
    sf::Window &window;
    int num_particles;
    std::vector<std::unique_ptr<Rule>> rules;

    void init_rules();

    void init_particles();

    std::vector<Particle>::iterator add_particle();

public:
    std::vector<Particle> particles;

    Flock(unsigned int count, sf::Window &win);

    int get_num_particles() const;

    void set_num_particles(int num);

    void update(sf::Time delta);

    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
};

#endif //PARTICLESYSTEM_FLOCK_H
