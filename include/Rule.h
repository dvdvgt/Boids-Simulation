//
// Created by dvd on 29.10.20.
//

#ifndef PARTICLESYSTEM_RULE_H
#define PARTICLESYSTEM_RULE_H

#include "SFML/Graphics.hpp"

class Particle;

class Rule {
protected:
    sf::Vector2f force;
    sf::Color color;
    float weight;
    bool is_enabled;

    Rule(sf::Color color_, float weight_, bool is_enabled_ = true) :
            color(color_),
            weight(weight_),
            is_enabled(is_enabled_) {}

    virtual sf::Vector2f compute_force(const std::vector<Particle *> &neighbors, const Particle &particle) = 0;

public:
    Rule(const Rule &r);

    virtual std::unique_ptr<Rule> clone() = 0;

    void set_weight(float w);

    float get_weight() const;

    void set_enabled(bool state);

    bool get_enabled() const;

    sf::Vector2f compute_weighted_force(const std::vector<Particle *> &neighbors, const Particle &particle);

    void draw(const Particle &particle, sf::RenderTarget &target, sf::RenderStates states) const;

};

class Cohesion : public Rule {
public:
    Cohesion(float weight_ = 1., bool is_enabled_ = true) : Rule(sf::Color::Cyan, weight_, is_enabled_) {}

    Cohesion(const Cohesion &c) : Rule(c) {}

    sf::Vector2f compute_force(const std::vector<Particle *> &neighbors, const Particle &particle) override;

    std::unique_ptr<Rule> clone() override;
};

class Separation : public Rule {
private:
    float min_dist;
public:
    Separation(float min_dist_ = 20., float weight_ = 1., bool is_enabled_ = true) :
            Rule(sf::Color::Red, weight_, is_enabled_), min_dist(min_dist_) {}

    Separation(const Separation &s) : Rule(s), min_dist(s.min_dist) {}

    void set_min_dist(float dist);

    float get_min_dist() const;

    sf::Vector2f compute_force(const std::vector<Particle *> &neighbors, const Particle &particle) override;

    std::unique_ptr<Rule> clone() override;
};

class Alignment : public Rule {
public:
    Alignment(float weight_ = 1., bool is_enabled_ = true) : Rule(sf::Color::Yellow, weight_, is_enabled_) {}

    Alignment(const Alignment &a) : Rule(a) {}

    sf::Vector2f compute_force(const std::vector<Particle *> &neighbors, const Particle &particle) override;

    std::unique_ptr<Rule> clone() override;
};

class WindowBound : public Rule {
private:
    sf::Window &win;
    int dist_threshold;
public:
    WindowBound(sf::Window &win_, int dist_, float weight = 10000000., bool is_enabled = true)
    : Rule(sf::Color::Transparent, weight, is_enabled), win(win_), dist_threshold(dist_) {}

    WindowBound(const WindowBound &w) : Rule(w), win(w.win), dist_threshold(w.dist_threshold) {}

    sf::Vector2f compute_force(const std::vector<Particle *> &neighbors, const Particle &particle) override;

    std::unique_ptr<Rule> clone() override;
};

#endif //PARTICLESYSTEM_RULE_H
