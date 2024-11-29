#include "../include/ObjectDragging.hpp"
#include "GameObjects.hpp"
#include "utils.hpp"
#include <raylib.h>

void Dragger::fill(GameObject *new_obj) { Selected = new_obj; }

void Dragger::clear() { Selected = nullptr; }

void Dragger::update() {
  if (Selected) {
  f32 inverse_zoom = 1 / Camera->zoom;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

      Selected->matrix.x += GetMouseDelta().x * inverse_zoom;
      Selected->matrix.y += GetMouseDelta().y * inverse_zoom;
    }

    f32 *p = &Selected->matrix.x;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      p += 2;
    }

    if (IsKeyPressedRepeat(KEY_W) || IsKeyPressedRepeat(KEY_UP)) {
      *(p + 1) -= inverse_zoom;
    }
    if (IsKeyPressedRepeat(KEY_A) || IsKeyPressedRepeat(KEY_LEFT)) {
      *p -= inverse_zoom;
    }
    if (IsKeyPressedRepeat(KEY_S) || IsKeyPressedRepeat(KEY_DOWN)) {
      *(p + 1) += inverse_zoom;
    }
    if (IsKeyPressedRepeat(KEY_D) || IsKeyPressedRepeat(KEY_RIGHT)) {
      *p += inverse_zoom;
    }
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
      *(p + 1) -= inverse_zoom;
    }
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
      *p -= inverse_zoom;
    }
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
      *(p + 1) += inverse_zoom;
    }
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
      *p += inverse_zoom;
    }
  }
}

void Dragger::draw() {
  if (Selected) {
    Rectangle r = RecWorldToScreen(&Selected->matrix, Camera);
    r.x -= r.width / 2;
    r.y -= r.height / 2;
    DrawRectangleLinesEx(r, 3, Color{255, 180, 100, 255});
  }
}

Dragger::Dragger(Camera2D *cam) {
  Camera = cam;
  Selected = nullptr;
}