//
// Created by sarthak on 2/1/25.
//

#include "ConfigManager.hpp"

#include <fstream>
#include <iostream>

// Platform specific includes

#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>

// Platform specific include
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#endif

ConfigManager::ConfigManager() {
    config_file_path_ = get_config_dir() + "config.cfg";

    if (is_first_run()) {
        set_default_config();
    } else {
        load_config();
    }
}


std::string ConfigManager::get_config_dir() {
    std::string config_dir;

    #ifdef _WIN32
        // AppData / Local
        char path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
            config_dir = std::string(path) + "\\STARMAN\";
        }
    #elif defined(__linux__) || defined(__APPLE__)
        const char *homedir = getenv("HOME");
        if (homedir == nullptr) {
            struct passwd *pw = getpwuid(getuid());
            homedir = pw->pw_dir;
        }
        config_dir = std::string(homedir) + "/.config/STARMAN/";
    #endif

    create_dir(config_dir);
    return config_dir;
}

void ConfigManager::create_dir(const std::string &path) {
    #ifdef _WIN32
        CreateDirectoryA(path.c_str(), NULL);
    #else
        mkdir(path.c_str(), 0755);
    #endif
}

void ConfigManager::load_config() {
    std::ifstream config_file(config_file_path_);
    if (!config_file.is_open()) {
        std::cerr << "Failed to open config file " << config_file_path_ << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(config_file, line)) {
        size_t delim_pos = line.find("=");
        if (delim_pos != std::string::npos) {
            std::string key = line.substr(0, delim_pos);
            std::string value = line.substr(delim_pos + 1);
            config_data_[key] = value;
        }
    }
    config_file.close();
}

void ConfigManager::save_config() const {
    std::ofstream config_file(config_file_path_);
    if (!config_file.is_open()) {
        std::cerr << "Failed to open config file " << config_file_path_ << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const auto &pair : config_data_) {
        config_file << pair.first << "=" << pair.second << std::endl;
    }
    config_file.close();
}

bool ConfigManager::is_first_run() const {
    std::ifstream config_file(config_file_path_);
    return !config_file.good();
}

void ConfigManager::set_default_config() {
    config_data_["resolution"] = "1920x1080";
    config_data_["fullscreen"] = "0";
    config_data_["volume"] = "60";
    config_data_["brightness"] = "50";
    config_data_["first_run"] = "true";
    save_config();
}

std::string ConfigManager::get_value(const std::string &key) {
    if (config_data_.find(key) != config_data_.end()) {
        return config_data_[key];
    }

    return "";
}

void ConfigManager::set_value(const std::string &key, const std::string &value) {
    config_data_[key] = value;
    save_config();
}