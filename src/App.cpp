//
// Created by sarthak on 1/30/25.
//

#include "App.hpp"

#include <stdexcept>

App::App(const int width, const int height, const char *title) {
    width_ = width;
    height_ = height;
    title_ = title;

    InitWindow(width_, height_, title_);
    SetTargetFPS(100);

    int display = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
}

App::~App() {
    CloseWindow();
}

void App::run() const {
    SceneManager scene_manager;
    while (!WindowShouldClose()) {
        scene_manager.update();
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        scene_manager.render(width_, height_);
        EndDrawing();
    }
}

void App::process_input() {
    // Stub
}