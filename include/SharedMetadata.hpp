#ifndef SHARED_METADATA_HPP
#define SHARED_METADATA_HPP

#include "raylib.h"

enum class YougurtSwitchSceneContextKey
{
    MAIN_WINDOW,
    MENU_WINDOW,
    END_WINDOW,
};

struct Yougurt3DState
{
    bool windowPause = false;
};

struct YougurtSharedMetadata
{
    bool windowLifetimes = true;
    bool mousHiddenFlags = true;

    float mouseValue = 0.0;
    float mouseWheel = 0.0;
    YougurtSwitchSceneContextKey keySwitchWindow;
    Yougurt3DState mode3dstate;
};

#endif