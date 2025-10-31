#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "Profiler.hpp"
#include "Particles.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Particle System Test");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    if (!ImGui::SFML::Init(window)) {
        return -1;
    }

    ParticleSystem ps(&window);
    Profiler profiler;
    sf::Clock deltaClock;

    sf::Vector2f spawnPos(400.f, 400.f);

    while (window.isOpen()) {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event); // note: pass window + dereferenced event
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Time deltaTime = deltaClock.restart();
        float dt = deltaTime.asSeconds();
        ImGui::SFML::Update(window, deltaTime);

        ImGui::Begin("Particle Controls");
        if (ImGui::Button("Spawn 50 Particles")) {
            ps.spawnParticles(50, spawnPos);
        }
        ImGui::Text("Particle Count: %zu", ps.getParticleCount());
        ImGui::End();

        profiler.renderImGui();

        // ---- Update Particles ----
        {
            PROFILE(profiler, "update");
            ps.update(dt);
        }

        // ---- Render ----
        {
            PROFILE(profiler, "render");
            window.clear(sf::Color::Black);
            ps.render();
            ImGui::SFML::Render(window);
            window.display();
        }
    }

    ImGui::SFML::Shutdown();
    return 0;
}
