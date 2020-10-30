//
// Created by dvd on 28.10.20.
//

#include "Particle.h"
#include "Swarm.h"
#include "Utils.h"
#include <random>

Particle::Particle(Swarm &swarm_, int detection_radius_, float size, sf::Color color) : swarm(swarm_) {
    shape = sf::CircleShape(size, 3);
    shape.setFillColor(color);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(200, 200);
    acceleration = sf::Vector2f();

    detection_radius = detection_radius_;
}

void Particle::set_position(sf::Vector2f pos) {
    shape.setPosition(pos);
}

sf::Vector2f Particle::get_position() const {
    return shape.getPosition();
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape);
}

void Particle::apply_force(sf::Vector2f &force) {
    if (utils::vector2::length(force) > max_acceleration) {
        utils::vector2::limit(force, max_acceleration);
    }
    acceleration += force;
}

void Particle::move(const float delta) {
    if (utils::vector2::length(acceleration) > max_acceleration) {
        utils::vector2::limit(acceleration, max_acceleration);
    }
    velocity += acceleration;
    if (utils::vector2::length(velocity) > max_velocity) {
        utils::vector2::limit(velocity, max_velocity);
    }
    acceleration = sf::Vector2f();
    shape.move(velocity * delta);
}

void Particle::randomize(sf::Window &window) {
    float angle = (std::rand() % 360) * 3.14f / 180.f;

    set_position(
            sf::Vector2f(
                    std::rand() % window.getSize().x,
                    std::rand() % window.getSize().y
                    )
            );
    velocity = sf::Vector2f(std::cos(angle) * max_velocity, std::sin(angle) * max_velocity);
}

void Particle::update(const Swarm &swarm) {

}

void Particle::warp(sf::Window &window) {
    sf::Vector2f pos = get_position();
    sf::Vector2u win_size = window.getSize();

    if (pos.x < 0) {
        pos.x += win_size.x;
    }
    else if (pos.x > win_size.x) {
        pos.x -= win_size.x;
    }

    if (pos.y < 0) {
        pos.y += win_size.y;
    } else if (pos.y > win_size.y) {
        pos.y -= win_size.y;
    }

    if (pos != get_position()) {
        set_position(pos);
    }
}

std::vector<Particle*> Particle::find_neighbors() const {
    std::vector<Particle*> neighbors;

    for (auto &p : swarm.particles) {
        if (&p != this) {
            double dist = utils::vector2::dist(p.get_position(), get_position());
            if (dist <= detection_radius) {
                neighbors.push_back(&p);
            }
        }
    }
    return neighbors;
}