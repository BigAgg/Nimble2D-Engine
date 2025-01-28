/*
*	MIT License
*
*	Copyright (c) 2025 BigAgg
*
*	Permission is hereby granted, free of charge, to any person obtaining a
copy *	of this software and associated documentation files (the "Software"), to
deal *	in the Software without restriction, including without limitation the
rights *	to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell *	copies of the Software, and to permit persons to whom the
Software is *	furnished to do so, subject to the following conditions:

*	The above copyright notice and this permission notice shall be included
in all *	copies or substantial portions of the Software.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE *	SOFTWARE.
*/

#pragma once

#include "entitycomponentsystem/ecs.h"
#include "raylib.h"

#define MIN_WIDTH 1080
#define MIN_HEIGHT 720

namespace globals {
inline bool running;
inline bool wasResized = false;

inline Camera2D gameCam;
inline Camera2D menuCam;

inline int width, height, fps;
inline bool fullscreen, borderless, vsync, maximized, paused;

inline SceneHandler sceneHandler;
} // namespace globals
