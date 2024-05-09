//
// Created by faliszewskii on 09.05.24.
//

#ifndef PUMAROBOT_DEBUGUI_H
#define PUMAROBOT_DEBUGUI_H

#include <functional>
#include "imgui.h"

class DebugUI {
    static std::vector<std::function<void()>> controls;

public:
    static void debugUI(const std::function<void()>& newControl) {
        controls.emplace_back(newControl);
    }

    static void render() {
        if(controls.empty()) return;
        ImGui::Begin("Debug Window");
        for(const std::function<void()> &control : controls)
            control();
        ImGui::End();
        controls.clear();
    }
};

#endif //PUMAROBOT_DEBUGUI_H
