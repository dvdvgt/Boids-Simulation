//
// Created by dvd on 26.10.20.
//

#ifndef BOIDSSIM_Vec2_H
#define BOIDSSIM_Vec2_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <ostream>

namespace utils {
    const double PI = 3.141592653589793238463;

    namespace vector2 {

        double scalar(const sf::Vector2f &v1, const sf::Vector2f &v2);

        void normalize(sf::Vector2f &v);

        double length(const sf::Vector2f &v);

        double fst_length(const sf::Vector2f &v);

        double dist(const sf::Vector2f &v1, const sf::Vector2f &v2);

        double fst_dist(const sf::Vector2f &v1, const sf::Vector2f &v2);

        void rotate(sf::Vector2f &v, double angle);

        void limit(sf::Vector2f &v, double s);

        double angle(const sf::Vector2f &v1, const sf::Vector2f &v2);

        double angle(const sf::Vector2f &v);

        void
        draw(sf::RenderTarget &target, sf::RenderStates states, const sf::Vector2f start, const sf::Vector2f vector,
             const sf::Color color);
    }
}
#endif //BOIDSSIM_Vec2_H
