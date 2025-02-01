//
// Created by sarthak on 1/30/25.
//

#pragma once

class Scene {
public:
    virtual ~Scene() = default;
    virtual void update(int &current_scene) = 0;
    virtual void render(const int screen_width, const int screen_height) = 0;
};