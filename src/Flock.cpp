//
// Created by dvd on 28.10.20.
//

#include "Flock.h"
#include "Particle.h"

Flock::Flock(unsigned int count, sf::Window &win) : num_particles(count), window(win){
    init_particles();
    init_rules();
}

void Flock::init_rules() {
    rules.emplace_back(std::make_unique<Cohesion>(2.75f));
    rules.emplace_back(std::make_unique<Separation>(25., 3.5f));
    rules.emplace_back(std::make_unique<Alignment>(2.25f));
    rules.emplace_back(std::make_unique<WindowBound>(window, 20));
}

void Flock::init_particles() {
    for (int i = 0; i < num_particles; ++i) {
        auto iter = add_particle();
        iter->randomize(window);
    }
}

std::vector<Particle>::iterator Flock::add_particle() {
    particles.emplace_back(*this, 40);
    return --particles.end();
}

int Flock::get_num_particles() const {
    return num_particles;
}

void Flock::set_num_particles(int num) {
    int diff = num_particles - num;
    // Add particles
    if (diff < 0) {
        diff = -diff;
        for (int i = 0; i < diff; ++i, ++num_particles) {
            auto iter = add_particle();
            iter->randomize(window);
        }
    } else if (diff > 0) { // Remove particles
        for (int i = 0; i < diff; ++i, --num_particles) {
            particles.pop_back();
        }
    }
}

void Flock::update(sf::Time delta) {
    for (auto &particle : particles) {
        std::vector<Particle*> neighborhood = particle.find_neighbors();
        for (auto &rule : rules) {
            sf::Vector2f weighted_force = rule->compute_weighted_force(neighborhood, particle);
            particle.apply_force(weighted_force);
        }
        particle.move(delta.asSeconds());
        particle.warp(window);
    }
}

void Flock::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &particle : particles) {
        target.draw(particle);
    }
}