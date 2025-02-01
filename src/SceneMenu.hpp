//
// Created by sarthak on 1/30/25.
//

#pragma once

#include "Scene.hpp"

class SceneMenu : public Scene {
public:
    void update(int &current_scene) override;
    void render(const int screen_width, const int screen_height) override;
};
