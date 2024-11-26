#pragma once
#include "GameObjects.hpp"
#include "types.hpp"
#include <raylib.h>

class Dragger {
  GameObject *Selected;
  Vector2 last_frame_pos;
  Camera2D *Camera;

public:
  Dragger(Camera2D *cam);
  void update();
  void draw();
  void fill(GameObject *new_obj);
  void clear();
};
