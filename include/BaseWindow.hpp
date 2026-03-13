#ifndef BASE_WINDOW_HPP
#define BASE_WINDOW_HPP

#include <iostream>

#include "MouseHandler.hpp"
#include "SharedMetadata.hpp"
#include "Player.hpp"

#include "../include/raylib.h"

constexpr size_t SwitchSceneToIndex(YougurtSwitchSceneContextKey key)
{
    return static_cast<size_t>(key);
}

class YougurtBaseWindowScene
{
protected:
    YougurtSharedMetadata &shared;
public:
    YougurtBaseWindowScene(YougurtSharedMetadata &shared_ref) noexcept : shared(shared_ref)
    {

    }
    virtual ~YougurtBaseWindowScene() noexcept = default;

    virtual void DrawWindowScene() = 0;
    virtual void EventPoll() = 0;
    virtual void UpdateState() = 0;
    virtual void reset() = 0;
};

class MainWindow : public YougurtBaseWindowScene
{
protected:
    Camera3D camera{};
    float default_fovy = 45.0f;
    Vector3 box = {5.0,5.0,5.0};
    Color box_color = RED;
    Vector2 floor{50.0,50.0};

    int width,height = 0;
public:
    MainWindow(YougurtSharedMetadata &shared_ref) noexcept : YougurtBaseWindowScene(shared_ref)
    {
        camera.position = {10.0f,10.0f,10.0f};
        camera.fovy = default_fovy;
        camera.projection = CAMERA_PERSPECTIVE;
        camera.target = {0.0,50.0,0.0};
        camera.up = {0.0,1.0,0.0};

        DisableCursor();
    }

    ~MainWindow() noexcept override = default;

    void DrawWindowScene() override
    {
        ClearBackground(GRAY);
        DrawText("Hello from Window scene",10,10,20,BLACK);
        if (!shared.mode3dstate.windowPause)
        {
            BeginMode3D(camera);
            DrawPlane((Vector3) {0.0,-1.0f,0.0},floor,DARKBROWN);
            DrawGrid(50,0.5f);
            DrawCube((Vector3){0.0f,5.0f,0.0f},5,5,5,this->box_color);

            EndMode3D();
        }
        DrawText("+",width / 2,height / 2,20,BLACK);
    }
    void EventPoll() override
    {
        if (IsKeyPressed(KeyboardKey::KEY_ONE))
        {
            shared.mousHiddenFlags = false;
            shared.mode3dstate.windowPause = false;
            shared.keySwitchWindow = YougurtSwitchSceneContextKey::MENU_WINDOW;
        }
        if (IsKeyPressed(KeyboardKey::KEY_TWO) && shared.mousHiddenFlags)
        {
            shared.mousHiddenFlags = false;
        }

        if (IsKeyPressed(KeyboardKey::KEY_THREE) && !shared.mousHiddenFlags)
        {
            shared.mousHiddenFlags = true;
        }

        if (IsKeyDown(KeyboardKey::KEY_Z))
        {
            if (camera.fovy > 1.0f)
                camera.fovy -= 0.5f;
        }
        if (IsKeyPressed(KeyboardKey::KEY_R))
        {
            camera.fovy = default_fovy;
        }

        if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
        {
            Ray ray = GetMouseRay((Vector2){this->width / 2.0f,this->height / 2.0f},camera);

            RayCollision hit = GetRayCollisionBox(ray,(BoundingBox){
                { -2.5f,2.5f,-2.5f},
                {2.5f,7.5f,2.5f}
            });

            if (hit.hit && hit.distance <= (float)5.0f)
            {
                this->box_color = WHITE;
            }
        }

        width = GetScreenWidth();
        height = GetScreenHeight();
    }
    void UpdateState() override
    {
        YougurtMouseDirection3D::UpdateMouse(GetMouseWheelMove(),camera,default_fovy);
        YougurtMouseDirection3D::UpdateDirection(GetMouseDelta(),camera);
        Player3DCamHandler::MotionHandler(camera,20.0f);
    }
    void reset() override
    {

    }
};


class MenuWindow : public YougurtBaseWindowScene
{
protected:
public:
    MenuWindow(YougurtSharedMetadata &shared_ref) noexcept : YougurtBaseWindowScene(shared_ref)
    {

    }
    ~MenuWindow() noexcept override = default;

    void DrawWindowScene() override
    {
        ClearBackground(GREEN);
        DrawText("Hello from menu",100,100,20,BLACK);
    }
    void EventPoll() override
    {
        if (IsKeyPressed(KeyboardKey::KEY_ONE))
        {
            shared.mousHiddenFlags = true;
            shared.keySwitchWindow = YougurtSwitchSceneContextKey::MAIN_WINDOW;
        }
    }
    void UpdateState() override
    {
        if (shared.mousHiddenFlags)
        {
            shared.mousHiddenFlags = false;
        }
    }
    void reset() override
    {

    }
};

#endif
