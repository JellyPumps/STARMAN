//
// Created by sarthak on 1/30/25.
//

#pragma once

#include "raylib.h"
#include "memory"
#include "Scene.hpp"

class SceneManager {
public:
    SceneManager();
    void update();
    void render(const int screen_width, const int screen_height) const;
    int current_scene = 0;
private:
    std::unique_ptr<Scene> scenes[10];
};
