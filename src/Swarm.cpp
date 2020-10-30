//
// Created by dvd on 28.10.20.
//

#include "Swarm.h"

Swarm::Swarm(unsigned int count, sf::Window &win) : num_particles(count), window(win){
    init_particles();
    init_rules();
}

void Swarm::init_rules() {
    rules.emplace_back(std::make_unique<Cohesion>(4.25f));
    rules.emplace_back(std::make_unique<Separation>(25., 4.75f));
    rules.emplace_back(std::make_unique<Alignment>(3.f));
}

void Swarm::init_particles() {
    for (int i = 0; i < num_particles; ++i) {
        particles.emplace_back(*this);
    }
    for (auto &particle : particles) {
        particle.randomize(window);
    }
    //set_particle_rules();
}

void Swarm::set_particle_rules() {
    for (auto &particle : particles) {
        for (auto &rule : rules) {
            //particle.rules.push_back(rule->clone());
        }
    }
}
/*
void Swarm::set_num_particles(int num) {
    int diff = num_particles - num;
    // Add particles
    if (diff < 0) {
        diff = -diff;
        for (int i = 0; i < diff; ++i) {
            particles.emplace_back(*this);
            ++num_particles;
        }
    } else if (diff > 0) { // Remove particles
        for (int i = 0; i < diff; ++i) {
            particles.pop_back();
            --num_particles;
        }
    }
}
*/
void Swarm::update(sf::Time delta) {
    for (auto &particle : particles) {
        std::vector<Particle*> neighborhood = particle.find_neighbors();
        for (auto &rule : particle.rules) {
            sf::Vector2f weighted_force = rule->compute_weighted_force(neighborhood, particle);
            particle.acceleration = sf::Vector2f();
            particle.apply_force(weighted_force);
        }
        particle.move(delta.asSeconds());
        particle.warp(window);
    }
}

void Swarm::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &particle : particles) {
        target.draw(particle.shape);
    }
}