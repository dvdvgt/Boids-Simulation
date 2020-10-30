//
// Created by dvd on 26.10.20.
//

#include "Utils.h"
#include <cmath>
#include "SFML/Window.hpp"

namespace utils {

    namespace vector2 {

        double scalar(const sf::Vector2f &v1, const sf::Vector2f &v2) {
            return 0;
        }

        void normalize(sf::Vector2f &v) {
            double len = length(v);
            double scalar = (len != 0) ? 1. / len : 0.;

            v.x *= scalar;
            v.y *= scalar;
        }

        double length(const sf::Vector2f &v) {
            return std::sqrt(
                    (v.x * v.x) + (v.y * v.y)
            );
        }

        double fst_length(const sf::Vector2f &v) {
            return (v.x * v.x) + (v.y * v.y);
        }

        double dist(const sf::Vector2f &v1, const sf::Vector2f &v2) {
            double dist = std::sqrt(
                    (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y)
            );
            return dist;
        }

        double fst_dist(const sf::Vector2f &v1, const sf::Vector2f &v2) {
            return (v2.x - v1.x) + (v2.y - v1.y);
        }

        void rotate(sf::Vector2f &v, double angle) {
            const double cos = std::cos(angle);
            const double sin = std::sin(angle);

            v.x = (v.x * cos) + (v.y * -sin);
            v.y = (v.x * sin) + (v.y * cos);
        }

        void limit(sf::Vector2f &v, double s) {
            double len = length(v);

            if (len > s) {
                double tmp = s / len;
                v.x *= tmp;
                v.y *= tmp;
            }
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states, const sf::Vector2f start, const sf::Vector2f vector,
             const sf::Color color) {
            sf::VertexArray line = sf::VertexArray(sf::Lines, 2);

            line[0] = start;
			line[1] = start + vector;

			line[0].color = color;
			line[1].color = color;

			target.draw(line, states);
        }
    }
}