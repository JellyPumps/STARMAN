//
// Created by sarthak on 2/1/25.
//

#pragma once

#include <string>
#include <filesystem>
#include <fstream>

class ConfigManager {
public:
    ConfigManager();
    bool is_first_launch();
    void set_first_launch_flag();
    std::filesystem::path get_config_path();
private:
    std::filesystem::path config_path_;
};
