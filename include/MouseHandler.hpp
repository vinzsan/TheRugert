#ifndef MOUSE_HANDLER_HPP
#define MOUSE_HANDLER_HPP

#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "BaseWindow.hpp"
#include "SharedMetadata.hpp"

namespace YougurtCursor
{
    static inline void MouseHandler(YougurtSharedMetadata &shared)
    {
        if (shared.mousHiddenFlags)
        {
            DisableCursor();
        } else
        {
            EnableCursor();
        }
    }
}

namespace YougurtMouseDirection3D
{
    static inline float yaw = 0.0f;
    static inline float pitch = 0.0f;

    static void UpdateDirection(Vector2 mouse_delta,Camera3D &cam)
    {
        yaw -= mouse_delta.x * 0.1f;
        pitch -= mouse_delta.y * 0.1f;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        Vector3 direction{};

        direction.x = std::cosf(DEG2RAD * pitch) * std::sinf(DEG2RAD * yaw);
        direction.y = std::sinf(DEG2RAD * pitch);
        direction.z = std::cosf(DEG2RAD * pitch) * std::cosf(DEG2RAD * yaw);

        cam.target = Vector3Add(cam.position,direction);
    }

    static void UpdateMouse(float mouse_wheel,Camera3D &cam,float &default_fovy)
    {
        if (mouse_wheel != 0)
        {
            cam.fovy -= mouse_wheel * 5.0f;

            if (cam.fovy > default_fovy) cam.fovy = default_fovy;
            if (cam.fovy < 1.0f) cam.fovy = 1.0f;
        }
    }
}

#endif