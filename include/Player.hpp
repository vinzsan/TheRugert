#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SharedMetadata.hpp"
#include "raylib.h"

namespace Player3DCamHandler
{
    static void MotionHandler(Camera3D &camere,float speed)
    {
        float velocity = GetFrameTime();
        Vector3 forward = Vector3Normalize(Vector3Subtract(camere.target,camere.position));
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward,camere.up));

        if (IsKeyDown(KeyboardKey::KEY_W))
        {
            camere.position = Vector3Add(camere.position,Vector3Scale(forward,velocity));
            camere.target = Vector3Add(camere.target,Vector3Scale(forward,velocity));
        }
        if (IsKeyDown(KeyboardKey::KEY_S))
        {
            camere.position = Vector3Subtract(camere.position,Vector3Scale(forward,velocity));
            camere.target = Vector3Subtract(camere.target,Vector3Scale(forward,velocity));
        }

        if (IsKeyDown(KeyboardKey::KEY_A))
        {
            camere.position = Vector3Subtract(camere.position,Vector3Scale(right,velocity));
            camere.target = Vector3Subtract(camere.target,Vector3Scale(right,velocity));
        }
        if (IsKeyDown(KeyboardKey::KEY_D))
        {
            camere.position = Vector3Add(camere.position,Vector3Scale(right,velocity));
            camere.target = Vector3Add(camere.position,Vector3Scale(right,velocity));
        }
    }
}

#endif