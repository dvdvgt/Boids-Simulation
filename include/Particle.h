//
// Created by dvd on 28.10.20.
//

#ifndef PARTICLESYSTEM_PARTICLE_H
#define PARTICLESYSTEM_PARTICLE_H

#include <SFML/Graphics.hpp>
class Flock;

struct Particle : public sf::Drawable {
    Flock &swarm;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float max_velocity = 120.;
    float max_acceleration = max_velocity * 0.1;
    sf::CircleShape shape;
    int detection_radius;

    void set_position(sf::Vector2f pos);

    sf::Vector2f get_position() const;

    Particle(Flock &swarm_, int detection_radius = 40, float size = 3.f, sf::Color color = sf::Color::Green);

    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

    void apply_force(sf::Vector2f &force);

    virtual void update(const Flock &swarm);

    void move(const float delta);

    void randomize(sf::Window &window);

    void warp(sf::Window &window);

    std::vector<Particle*> find_neighbors() const;
};

#endif //PARTICLESYSTEM_PARTICLE_H
