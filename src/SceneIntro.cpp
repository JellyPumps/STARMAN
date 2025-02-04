//
// Created by sarthak on 2/1/25.
//

#include "SceneIntro.hpp"
#include <raylib.h>

void SceneIntro::update(int &current_scene) {
    if (IsKeyDown(KEY_ENTER)) current_scene = 1;
}

void SceneIntro::render(const int screen_width, const int screen_height) {
    DrawRectangle(0, 0, screen_width, screen_height, BLUE);
    DrawText("INTRO SCREEN", 20, 20, 40, DARKBLUE);
}
