#include "imgui.h"
#include "imgui-SFML.h"
#include "Profiler.hpp"
#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "GameRules.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Conway's Game of Life");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    if (!ImGui::SFML::Init(window))
        return -1;

    Profiler profiler;
    sf::Clock deltaClock;

    //grid setup
    int gridWidth = 30;
    int gridHeight = 30;
    Grid grid(window.getSize().x, window.getSize().y);
    grid.gridWidth = gridWidth;
    grid.gridHeigth = gridHeight;

    grid.gridSetup();

    GameRules gameRules(grid);

    bool isRunning = false;
    float updateDelay = 0.2f;
    sf::Clock updateClock;


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Time deltaTime = deltaClock.restart();
        ImGui::SFML::Update(window, deltaTime);

        {
            //imgui show profiler
            ImGui::Begin("Controls");
            if (ImGui::Button("Clear Profiler History")) {
                profiler.clear();
            }
            ImGui::End();
        }

        profiler.renderImGui();

        {
            PROFILE(profiler, "update");
                gameRules.update();
                updateClock.restart();
        }

        {
            PROFILE(profiler, "Rendering");
            window.clear(sf::Color::Black);

            gameRules.render(window);
            ImGui::SFML::Render(window);

            window.display();
        }
    }

    ImGui::SFML::Shutdown();
    return 0;
}
