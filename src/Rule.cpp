//
// Created by dvd on 29.10.20.
//

#include "Rule.h"
#include "Particle.h"
#include "Utils.h"

//
// Rule base class
//

Rule::Rule(const Rule &r) {
    force = r.force;
    color = r.color;
    weight = r.weight;
    is_enabled = r.is_enabled;
}

void Rule::set_weight(float w) {
    weight = w;
}

float Rule::get_weight() const {
    return weight;
}

void Rule::set_enabled(bool state) {
    is_enabled = state;
}

bool Rule::get_enabled() const {
    return is_enabled;
}

sf::Vector2f Rule::compute_weighted_force(const std::vector<Particle*> &neighbors, const Particle &particle) {
    if (is_enabled) {
        force = weight * compute_force(neighbors, particle);
    } else {
        force = sf::Vector2f();
    }
    return force;
}

void Rule::draw(const Particle &particle, sf::RenderTarget &target, sf::RenderStates states) const {
    utils::vector2::draw(target, states, particle.get_position(), force * 3.5f, color);
}

//
// Cohesion
//

sf::Vector2f Cohesion::compute_force(const std::vector<Particle*> &neighbors, const Particle &particle) {
    sf::Vector2f cohesion_force;

    if (!neighbors.empty()) {
        sf::Vector2f center;
        for (const auto &neighbor : neighbors) {
            center += neighbor->get_position();
        }
        center /= (float) neighbors.size();
        center -= particle.get_position();
        utils::vector2::normalize(center);
        cohesion_force = center;
    }
    return cohesion_force;
}

std::unique_ptr<Rule> Cohesion::clone() {
    return std::make_unique<Cohesion>(*this);
}

//
// Separation
//

void Separation::set_min_dist(float dist) {
    min_dist = dist;
}

float Separation::get_min_dist() const {
    return min_dist;
}

sf::Vector2f Separation::compute_force(const std::vector<Particle*> &neighbors, const Particle &particle) {
    sf::Vector2f separation_force;

    if (!neighbors.empty()) {
        sf::Vector2f position = particle.get_position();
        int count_close_neighbors = 0;

        for (const auto &neighbor : neighbors) {
            sf::Vector2f neighbor_pos = neighbor->get_position();

            float dist = utils::vector2::dist(position, neighbor_pos);

            if (dist < min_dist) {
                sf::Vector2f rejection_vec = position - neighbor_pos;
                utils::vector2::normalize(rejection_vec);
                separation_force += rejection_vec / dist;
                ++count_close_neighbors;
            }
        }
        if (count_close_neighbors) {
            separation_force /= (float) count_close_neighbors;
        }
    }
    utils::vector2::normalize(separation_force);
    return separation_force;
}


std::unique_ptr<Rule> Separation::clone() {
    return std::make_unique<Separation>(*this);
}

//
// Alignment
//

sf::Vector2f Alignment::compute_force(const std::vector<Particle*> &neighbors, const Particle &particle) {
    sf::Vector2f avg_velocity;

    if (!neighbors.empty()) {
        for (const auto &neighbor : neighbors) {
            avg_velocity += neighbor->velocity;
        }
        avg_velocity /= (float) neighbors.size();
    }
    utils::vector2::normalize(avg_velocity);
    return avg_velocity;
}

std::unique_ptr<Rule> Alignment::clone() {
    return std::make_unique<Alignment>(*this);
}

//
// WindowBound (window border repels particle)
//

sf::Vector2f WindowBound::compute_force(const std::vector<Particle *> &neighbors, const Particle &particle) {
    sf::Vector2f repelling_force;
    sf::Vector2f position = particle.get_position();

    unsigned int win_width = win.getSize().x;
    unsigned int win_height = win.getSize().y;

    const float epsilon = 1E-4;

    if (position.x < dist_threshold) {
        repelling_force.x += dist_threshold / position.x;
    } else if (position.x > win_width - dist_threshold) {
        int delta = position.x - win_width;
        repelling_force.x += dist_threshold / (delta + epsilon);
    } else if (position.y < dist_threshold) {
        repelling_force.y += dist_threshold / position.y;
    } else if (position.y > win_height - dist_threshold) {
        int delta = position.y - win_height;
        repelling_force.y += dist_threshold / (delta + epsilon);
    }

    utils::vector2::normalize(repelling_force);
    return repelling_force;
}

std::unique_ptr<Rule> WindowBound::clone() {
    return std::make_unique<WindowBound>(*this);
}