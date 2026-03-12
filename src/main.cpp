#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>

#include "../include/BaseWindow.hpp"
#include "../include/MouseHandler.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"

constexpr int YOUGURT_WINDOW_WIDTH = 800;
constexpr int YOUGURT_WINDOW_HEIGHT = 600;
constexpr int YOUGURT_DEFAULT_FPS = 60;

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT
        | FLAG_WINDOW_RESIZABLE);

    InitWindow(YOUGURT_WINDOW_WIDTH,
               YOUGURT_WINDOW_HEIGHT,
               "Yougurt");

    SetTargetFPS(YOUGURT_DEFAULT_FPS);

    YougurtSharedMetadata sharedMetadata{};
    sharedMetadata.keySwitchWindow = YougurtSwitchSceneContextKey::MAIN_WINDOW;
    sharedMetadata.mousHiddenFlags = true;

    std::unique_ptr<YougurtBaseWindowScene> main_window = std::make_unique<MainWindow>(sharedMetadata);
    std::unique_ptr<YougurtBaseWindowScene> menu_window = std::make_unique<MenuWindow>(sharedMetadata);

    std::vector<std::unique_ptr<YougurtBaseWindowScene>> currentWindow;
    currentWindow.push_back(std::move(main_window));
    currentWindow.push_back(std::move(menu_window));

    while (!WindowShouldClose() && sharedMetadata.windowLifetimes)
    {
        /* Universal key */
        if (IsKeyPressed(KeyboardKey::KEY_Q))
        {
            sharedMetadata.windowLifetimes = false;
        }
        currentWindow[SwitchSceneToIndex(sharedMetadata.keySwitchWindow)]->EventPoll();

        BeginDrawing();
        if (sharedMetadata.keySwitchWindow == YougurtSwitchSceneContextKey::END_WINDOW)
        {
            sharedMetadata.keySwitchWindow = YougurtSwitchSceneContextKey::MAIN_WINDOW;
        }

        currentWindow[static_cast<size_t>(sharedMetadata.keySwitchWindow)]->UpdateState();

        currentWindow[static_cast<size_t>(sharedMetadata.keySwitchWindow)]->DrawWindowScene();
        YougurtCursor::MouseHandler(sharedMetadata);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}