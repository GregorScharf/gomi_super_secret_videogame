#include "../include/utils.hpp"
#include "types.hpp"
#include <cmath>
#include <cstring>
#include <raylib.h>

bool endswith(string s, const char *end) {
  if (strlen(end) > s.size()) {
    return false;
  }
  string thisend = s.substr(s.size() - strlen(end), s.size() + 1);
  string str = end;
  return strcmp(thisend.c_str(), str.c_str()) == 0;
}

Rectangle RecWorldToScreen(Rectangle *rec, Camera2D *camera) {
  Vector2 tmp = GetWorldToScreen2D({rec->x, rec->y}, *camera);
  return {tmp.x, tmp.y, rec->width * camera->zoom, rec->height * camera->zoom};
}
Rectangle RecScreenToWorld(Rectangle *rec, Camera2D *camera) {
  Vector2 tmp = GetScreenToWorld2D({rec->x, rec->y}, *camera);
  return {tmp.x, tmp.y, rec->width * camera->zoom, rec->height * camera->zoom};
}

bool is_int(string &s) {
  bool minus = false;
  for (char c : s) {
    if (c < 48 || c > 57) {
      if (c != '-' || minus) {
        return false;
      } else {
        minus = true;
      }
    }
  }
  return true;
}

bool is_uint(string &s) {
  for (char c : s) {
    if (c < 48 || c > 57) {
      return false;
    }
  }
  return true;
}

bool is_float(string &s) {
  bool dot = false;

  if (s.size() == 0) {
    return false;
  }

  for (char c : s) {
    if (c < 48 || c > 57) {
      if (c != '.' || dot) {
        return false;
      } else {
        dot = true;
      }
    }
  }
  return true;
}

f32 cosd(f32 x) { return cos(x) * RAD_TO_DEC; }
f32 sind(f32 x) { return sin(x) * RAD_TO_DEC; }

void DrawRectangleAngleEx(Rectangle rec, Vector2 center, float lineThick,
                          float angle, Color color) {
  Vector2 vertecies[4];

  angle = angle * (M_PI / 180);

  center.x += rec.x;
  center.y += rec.y;

  vertecies[0].x = rec.x - center.x;
  vertecies[0].y = rec.y - center.y;

  vertecies[1].x = rec.x + rec.width - center.x;
  vertecies[1].y = rec.y - center.y;

  vertecies[2].x = rec.x + rec.width - center.x;
  vertecies[2].y = rec.y + rec.height - center.y;

  vertecies[3].x = rec.x - center.x;
  vertecies[3].y = rec.y + rec.height - center.y;

  for (i32 i = 0; i < 4; i++) {
    u64 x = vertecies[i].x;
    u64 y = vertecies[i].y;
    vertecies[i].x = (x * cos(angle)) - (y * sin(angle));
    vertecies[i].y = (x * sin(angle)) + (y * cos(angle));
    vertecies[i].x += center.x;
    vertecies[i].y += center.y;
  }

  DrawLineEx(vertecies[0], vertecies[1], lineThick, color);
  DrawLineEx(vertecies[1], vertecies[2], lineThick, color);
  DrawLineEx(vertecies[2], vertecies[3], lineThick, color);
  DrawLineEx(vertecies[3], vertecies[0], lineThick, color);
}

bool AngledRecPointCollision(Vector2 p, Rectangle r, Vector2 center,
                             f32 angle) {
  if (angle == 0) {
    return CheckCollisionPointRec(p, r);
  }
  Vector2 vertices[4];

  angle = angle * (M_PI / 180);

  center.x += r.x;
  center.y += r.y;

  vertices[0].x = r.x - center.x;
  vertices[0].y = r.y - center.y;

  vertices[1].x = r.x + r.width - center.x;
  vertices[1].y = r.y - center.y;

  vertices[2].x = r.x + r.width - center.x;
  vertices[2].y = r.y + r.height - center.y;

  vertices[3].x = r.x - center.x;
  vertices[3].y = r.y + r.height - center.y;

  for (i32 i = 0; i < 4; i++) {
    f32 x = vertices[i].x;
    f32 y = vertices[i].y;
    vertices[i].x = (x * cos(angle)) - (y * sin(angle));
    vertices[i].y = (x * sin(angle)) + (y * cos(angle));
    vertices[i].x += center.x;
    vertices[i].y += center.y;
  }

  bool collision = false;

  i32 next = 0;
  for (i32 current = 0; current < 4; current++) {

    next = current + 1;
    if (next == 4)
      next = 0;

    Vector2 vc = vertices[current]; // c for "current"
    Vector2 vn = vertices[next];    // n for "next"

    if (((vc.y >= p.y && vn.y < p.y) || (vc.y < p.y && vn.y >= p.y)) &&
        (p.x < (vn.x - vc.x) * (p.y - vc.y) / (vn.y - vc.y) + vc.x)) {
      collision = !collision;
    }
  }
  return collision;
}

// we can save like 7 cpu cycles per frame with this
u64 extractBits(u64 num, u64 pos, u64 k) {

  u64 shifted = num >> pos;
  u64 mask = (1 << k) - 1;

  return shifted & mask;
}
