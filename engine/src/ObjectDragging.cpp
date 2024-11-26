#include "../include/ObjectDragging.hpp"
#include "GameObjects.hpp"
#include "utils.hpp"
#include <raylib.h>

void Dragger::fill(GameObject *new_obj) { Selected = new_obj; }

void Dragger::clear() { Selected = nullptr; }

void Dragger::update() {
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && Selected) {
    clear();
  }
  if (Selected) {
    last_frame_pos = GetMousePosition();
  }
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && Selected) {

    Selected->matrix.x += GetMouseDelta().x * (1 / Camera->zoom);
    Selected->matrix.y += GetMouseDelta().y * (1 / Camera->zoom);

    cout << Camera->zoom << endl;
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
