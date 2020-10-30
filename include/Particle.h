//
// Created by dvd on 28.10.20.
//

#ifndef PARTICLESYSTEM_PARTICLE_H
#define PARTICLESYSTEM_PARTICLE_H

#include <SFML/Graphics.hpp>
#include "Rule.h"
class Swarm;

struct Particle : public sf::Drawable {
    Swarm &swarm;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float max_velocity = 100.;
    float max_acceleration = 15.;
    sf::CircleShape shape;
    int detection_radius;
    std::vector<std::unique_ptr<Rule>> rules;

    void set_position(sf::Vector2f pos);

    sf::Vector2f get_position() const;

    Particle(Swarm &swarm_, int detection_radius = 40, float size = 4.f, sf::Color color = sf::Color::Green);

    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

    void apply_force(sf::Vector2f &force);

    virtual void update(const Swarm &swarm);

    void move(const float delta);

    void randomize(sf::Window &window);

    void warp(sf::Window &window);

    std::vector<Particle*> find_neighbors() const;

    void set_rules(const std::vector<std::unique_ptr<Rule>> &r);
};

#endif //PARTICLESYSTEM_PARTICLE_H
