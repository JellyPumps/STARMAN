//
// Created by sarthak on 1/30/25.
//

#include "SceneManager.hpp"
#include "SceneMenu.hpp"

SceneManager::SceneManager() {
    // Stub, fill with scenes
    // scenes[x] = std::make_unique<SCENENAME>();
    scenes[0] = std::make_unique<SceneMenu>();
}

void SceneManager::update() {
    scenes[current_scene]->update(current_scene);
}

void SceneManager::render(const int screen_width, const int screen_height) const {
    scenes[current_scene]->render(screen_width, screen_height);
}
