#pragma once

#include <random>
#include <SFML/Graphics.hpp>

class ParticleSystem {
private:
    sf::RenderWindow* window;
    std::mt19937 rng;
    std::vector<sf::Vector2f> positions;
    std::vector<sf::Vector2f> velocities;
    std::vector<sf::Color> colors;
    std::vector<float> lifetimes;
    std::vector<float> maxLifetimes;
    std::vector<sf::CircleShape> shapes;
    std::vector<sf::Vector2f> accelerations;
    std::vector<uint8_t> alive;
    size_t count;
    const sf::Vector2f gravity = {0.f, 98.1f};
    const float radius = 2.0f;

public:
    ParticleSystem(sf::RenderWindow* win)
        : window(win), rng(std::random_device{}()), count(0) {
        const size_t reserveSize = 5000;
        positions.reserve(reserveSize);
        velocities.reserve(reserveSize);
        colors.reserve(reserveSize);
        lifetimes.reserve(reserveSize);
        maxLifetimes.reserve(reserveSize);
        shapes.reserve(reserveSize);
        accelerations.reserve(reserveSize);
        alive.reserve(reserveSize);
    }

    inline void spawnParticles(int n, const sf::Vector2f& origin) {
        std::uniform_real_distribution<float> angleDist(0.f, 6.28318f);
        std::uniform_real_distribution<float> speedDist(50.f, 200.f);
        std::uniform_int_distribution<int> colorDist(0, 255);
        std::uniform_real_distribution<float> lifeDist(1.0f, 5.0f);
        positions.resize(count + n);
        velocities.resize(count + n);
        colors.resize(count + n);
        lifetimes.resize(count + n);
        maxLifetimes.resize(count + n);
        shapes.resize(count + n);
        accelerations.resize(count + n);
        alive.resize(count + n);
        for (int i = 0; i < n; ++i) {
            size_t idx = count + i;
            float angle = angleDist(rng);
            float speed = speedDist(rng);
            velocities[idx] = {std::cos(angle) * speed, std::sin(angle) * speed};
            positions[idx] = origin;
            colors[idx] = sf::Color(colorDist(rng), colorDist(rng), colorDist(rng), 255);
            float life = lifeDist(rng);
            lifetimes[idx] = life;
            maxLifetimes[idx] = life;
            shapes[idx] = sf::CircleShape(radius);
            shapes[idx].setFillColor(colors[idx]);
            shapes[idx].setPosition(origin);
            accelerations[idx] = gravity;
            alive[idx] = 1;
        }
        count += n;
    }

    inline void update(float dt) {
        const float maxX = 800.f, maxY = 800.f;
        for (size_t i = 0; i < count; ++i) {
            if (!alive[i]) continue;
            sf::Vector2f& v = velocities[i];
            sf::Vector2f& p = positions[i];
            v += accelerations[i] * dt;
            p += v * dt;
            float& life = lifetimes[i];
            life -= dt;
            if (life <= 0.f) {
                alive[i] = 0;
                continue;
            }
            float alpha = life / maxLifetimes[i];
            colors[i].a = static_cast<uint8_t>(alpha * 255.f);
            if (p.x < 0.f) { p.x = 0.f; v.x *= -0.8f; }
            else if (p.x > maxX) { p.x = maxX; v.x *= -0.8f; }
            if (p.y < 0.f) { p.y = 0.f; v.y *= -0.8f; }
            else if (p.y > maxY) { p.y = maxY; v.y *= -0.8f; }
        }
    }

    inline void render() {
        for (size_t i = 0; i < count; ++i)
            if (alive[i]) {
                shapes[i].setPosition(positions[i]);
                shapes[i].setFillColor(colors[i]);
                window->draw(shapes[i]);
            }
    }

    inline size_t getParticleCount() const {
        return count;
    }
};
