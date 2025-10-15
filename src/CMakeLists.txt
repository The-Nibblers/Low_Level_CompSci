add_executable(low-level_setup
 main.cpp
        Grid.cpp
        Grid.h
        GameRules.cpp
        GameRules.h
)

target_link_libraries(low-level_setup
 PUBLIC
  ImGui-SFML::ImGui-SFML
)

# Do we need this?
# include(Install.cmake)