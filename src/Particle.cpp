//
// Created by dvd on 28.10.20.
//

#include "Particle.h"
#include "Flock.h"
#include "Utils.h"
#include <random>
#include <time.h>

Particle::Particle(Flock &swarm_, int detection_radius_, float size, sf::Color color) : swarm(swarm_) {
    shape = sf::CircleShape(size, 3);
    shape.setFillColor(color);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    set_position(sf::Vector2f());
    acceleration = sf::Vector2f();

    detection_radius = detection_radius_;
    //std::srand(std::time(0));
}

void Particle::set_position(sf::Vector2f pos) {
    shape.setPosition(pos);
}

sf::Vector2f Particle::get_position() const {
    return shape.getPosition();
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape);
    /*
    utils::vector2::draw(
            target, states, get_position(), acceleration, sf::Color::Red
    );
    utils::vector2::draw(
            target, states, get_position(), velocity * 0.2f, sf::Color::Blue
    );
     */
}

void Particle::apply_force(sf::Vector2f &force) {
    acceleration += force;
}

void Particle::move(const float delta) {
    // Limit acceleration to maximum acceleration
    if (utils::vector2::fst_length(acceleration) > max_acceleration * max_acceleration) {
        utils::vector2::limit(acceleration, max_acceleration);
    }
    velocity += acceleration;
    // Reset acceleration
    acceleration = sf::Vector2f();
    // Adjust rotation of particle according to its direction
    shape.setRotation(utils::vector2::angle(velocity));
    // Adjust velocity to maximum
    if (utils::vector2::fst_length(velocity) > max_velocity * max_velocity) {
        utils::vector2::limit(velocity, max_velocity);
    }
    shape.move(velocity * delta);
}

void Particle::randomize(sf::Window &window) {
    // Random position within the window
    set_position(
            sf::Vector2f(
                    std::rand() % window.getSize().x,
                    std::rand() % window.getSize().y
                    )
            );
    // Random direction and velocity
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float v = std::rand() % (int) max_velocity;
    velocity = sf::Vector2f(std::cos(angle) * v, std::sin(angle) * v);
}

void Particle::update(const Flock &swarm) {

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
            double dist = utils::vector2::fst_dist(p.get_position(), get_position());
            if (dist <= detection_radius * detection_radius) {
                neighbors.push_back(&p);
            }
        }
    }
    return neighbors;
}