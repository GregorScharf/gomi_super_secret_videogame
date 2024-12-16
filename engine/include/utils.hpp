#pragma once

#include "types.hpp"
#include <raylib.h>

#define debuglog(x) cout << x << endl;

bool endswith(string s, const char *end);

bool is_int(string &s);
bool is_uint(string &s);
bool is_float(string &s);

Rectangle RecWorldToScreen(Rectangle *rec, Camera2D *camera);
Rectangle RecScreenToWorld(Rectangle *rec, Camera2D *camera);

void DrawRectangleAngle(Rectangle rec, float lineThick, float angle,
                        Color color);

void DrawRectangleAngleEx(Rectangle rec, Vector2 center, float lineThick,
                          float angle, Color color);

bool AngledRecPointCollision(Vector2 p, Rectangle r, Vector2 center, f32 angle);

u64 extractBits(u64 num, u64 pos = 0, u64 k = 1);
