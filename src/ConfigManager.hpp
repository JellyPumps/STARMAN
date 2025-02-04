//
// Created by sarthak on 2/1/25.
//

#pragma once

#include <string>
#include <map>

class ConfigManager {
public:
    ConfigManager();
    bool is_first_run() const;
    void set_default_config();

    std::string get_value(const std::string &key);
    void set_value(const std::string &key, const std::string &value);
private:
    std::string config_file_path_;
    std::map<std::string, std::string> config_data_;

    static std::string get_config_dir();

    static void create_dir(const std::string& path);

    void load_config();
    void save_config() const;
};
