//
// Created by sarthak on 1/30/25.
//

#pragma once

class App {
public:
    explicit App(const char* title);
    ~App();

    void run() const;
private:
    int width_;
    int height_;
    const char *title_;
    static void process_input();
};
