#include "../include/ObjectDragging.hpp"
#include "GameObjects.hpp"
#include "utils.hpp"
#include <raylib.h>

void Dragger::fill(GameObject *new_obj) { Selected = new_obj; }

void Dragger::clear() { Selected = nullptr; }

void Dragger::update() {
  if (Selected) {

    if ((!CheckCollisionPointRec(GetMousePosition(), *ObjectView)) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      clear();
      return;
    }

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

    DrawRectangleAngleEx(r, {r.width / 2, r.height / 2}, 3, Selected->rotation,
                         ORANGE);
  }
}

Dragger::Dragger(Camera2D *cam, Rectangle *_ObjectView) {
  this->ObjectView = _ObjectView;

  Camera = cam;
  Selected = nullptr;
}
