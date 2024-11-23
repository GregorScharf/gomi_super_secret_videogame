#include "../include/ObjectInspector.hpp"
#include <raylib.h>
#include <string>

#define INSPECTOR_HEIGHT 400
#define INSPECTOR_WIDTH_IS_FULL 1

ObjectInspector::ObjectInspector() { this->SelectedObject = nullptr; }

void ObjectInspector::update() {
  //
}

void ObjectInspector::fill(GameObject *obj) { SelectedObject = obj; }

void ObjectInspector::clear() { SelectedObject = nullptr; }

#define FONTSIZE 18

void ObjectInspector::draw(Rectangle *selectionWindow) {
  Rectangle box = {
      selectionWindow->width + 1, (f32)GetScreenHeight() - INSPECTOR_HEIGHT,
      INSPECTOR_WIDTH_IS_FULL * (f32)GetScreenWidth() - selectionWindow->width,
      INSPECTOR_HEIGHT};
  DrawRectanglePro(box, {0}, 0, Color{140, 140, 140, 255});

  if (SelectedObject) {
    DrawText("Position:", box.x + 50, box.y + 10, FONTSIZE, BLACK);
    DrawText(std::to_string(SelectedObject->matrix.x).c_str(), box.x + 200,
             box.y + 10, FONTSIZE, BLACK);
    DrawText(std::to_string(SelectedObject->matrix.y).c_str(), box.x + 300,
             box.y + 10, FONTSIZE, BLACK);

    DrawText("Scale:", box.x + 65, box.y + 40, FONTSIZE, BLACK);
    DrawText(std::to_string(SelectedObject->matrix.width).c_str(), box.x + 200,
             box.y + 40, FONTSIZE, BLACK);
    DrawText(std::to_string(SelectedObject->matrix.height).c_str(), box.x + 300,
             box.y + 40, FONTSIZE, BLACK);

    /*
    DrawText(, , , FONTSIZE, BLACK);
    */
  }
}
