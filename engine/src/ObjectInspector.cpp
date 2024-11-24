#include "../include/ObjectInspector.hpp"
#include <raylib.h>
#include <string>

#define INSPECTOR_HEIGHT 400
#define INSPECTOR_WIDTH_IS_FULL 1

ObjectInspector::ObjectInspector(Rectangle *selectionWindow) {
  this->SelectedObject = nullptr;
  this->PositionInput.set_matrix(
      {selectionWindow->width + 200,
       (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 10, 256, 28});
  this->ScaleInput.set_matrix({selectionWindow->width + 200,
                               (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 50,
                               256, 28});
  this->RotationInput.set_matrix(
      {selectionWindow->width + 200,
       (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 90, 256, 28});
}

void ObjectInspector::update() {
  Vector2 mouse = GetMousePosition();
  ScaleInput.update(mouse);
  RotationInput.update(mouse);
  PositionInput.update(mouse);
}

void ObjectInspector::fill(GameObject *obj) { SelectedObject = obj; }

void ObjectInspector::clear() { SelectedObject = nullptr; }

#define FONTSIZE 18

void ObjectInspector::draw(Rectangle *selectionWindow) {
  Rectangle box = {
      selectionWindow->width, (f32)GetScreenHeight() - INSPECTOR_HEIGHT,
      INSPECTOR_WIDTH_IS_FULL * (f32)GetScreenWidth() - selectionWindow->width,
      INSPECTOR_HEIGHT};
  DrawRectanglePro(box, {0}, 0, Color{140, 140, 140, 255});
  DrawRectangleLinesEx(box, 2, BLACK);

  // gonna need a way to make this more interactable but im still thinking
  // of a smarter way to do that
  if (SelectedObject) {
    DrawText("Position:", box.x + 50, box.y + 10, FONTSIZE, BLACK);
    PositionInput.setText(std::to_string(SelectedObject->matrix.x) +
                          std::to_string(SelectedObject->matrix.y));
    PositionInput.draw();

    DrawText("Scale:", box.x + 50, box.y + 50, FONTSIZE, BLACK);
    ScaleInput.setText(std::to_string(SelectedObject->matrix.width) +
                       std::to_string(SelectedObject->matrix.height));
    ScaleInput.draw();
    DrawText("Rotation: ", box.x + 50, box.y + 90, FONTSIZE, BLACK);
    RotationInput.setText(std::to_string(SelectedObject->rotation));
    RotationInput.draw();

    DrawText("", box.x + 50, box.y + 100, FONTSIZE, BLACK);

    /*
    DrawText(, , , FONTSIZE, BLACK);
    */
  }
}
