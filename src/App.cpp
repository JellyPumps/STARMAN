//
// Created by sarthak on 1/30/25.
//

#include "App.hpp"
#include <iostream>
#include "ConfigManager.hpp"
#include "SceneManager.hpp"
#include <stdexcept>
#include <raylib.h>

App::App(const char *title) {
    int display = GetCurrentMonitor();
    width_ = GetMonitorWidth(display);
    height_ = GetMonitorHeight(display);
    title_ = title;

    InitWindow(width_, height_, title_);
    ToggleFullscreen();
    SetTargetFPS(100);
}

App::~App() {
    CloseWindow();
}

void App::run() const {
    SceneManager scene_manager;
    ConfigManager config;

    if (config.get_value("first_run") != "true") {
        scene_manager.current_scene = 1;
    } else {
        scene_manager.current_scene = 0;
        config.set_value("first_run", "false");
    }

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