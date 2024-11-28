#include "../include/ObjectInspector.hpp"
#include "fonts.hpp"
#include <raylib.h>
#include <string>
ObjectInspector::ObjectInspector(
    Rectangle *selectionWindow,
    shared_ptr<GameObjectContainer> GameObjectsRef) {
  this->GameObjects = GameObjectsRef;
  this->SelectedObject = nullptr;
  this->PositionInputx.set_matrix(
      {selectionWindow->width + 200,
       (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 10, 128, 28});
  this->PositionInputy.set_matrix(
      {selectionWindow->width + 328,
       (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 10, 128, 28});
  this->ScaleInputx.set_matrix({selectionWindow->width + 200,
                                (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 50,
                                128, 28});
  this->ScaleInputy.set_matrix({selectionWindow->width + 328,
                                (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 50,
                                128, 28});
  this->RotationInput.set_matrix(
      {selectionWindow->width + 200,
       (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 90, 128, 28});
  RotationInput.input_type = FLOAT;
  ScaleInputx.input_type = FLOAT;
  ScaleInputy.input_type = FLOAT;
  PositionInputx.input_type = FLOAT;
  PositionInputy.input_type = FLOAT;
  ShaderInput.input_type = STRING;

  shaderBox = {selectionWindow->width + 500,
               (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 10, 100, 80};
  clearShaders = {selectionWindow->width + 625,
                  (f32)GetScreenHeight() - INSPECTOR_HEIGHT + 10, 100, 80};
}

void ObjectInspector::update() {
  Vector2 mouse = GetMousePosition();
  ScaleInputx.update(mouse);
  ScaleInputy.update(mouse);
  RotationInput.update(mouse);
  PositionInputx.update(mouse);
  PositionInputy.update(mouse);
  ShaderInput.update(mouse);

  if (SelectedObject) {
    if (ScaleInputx.can_callback()) {
      SelectedObject->matrix.width = std::stof(ScaleInputx.callback());
    }
    if (ScaleInputy.can_callback()) {
      SelectedObject->matrix.height = std::stof(ScaleInputy.callback());
    }
    if (RotationInput.can_callback()) {
      SelectedObject->rotation = std::stof(RotationInput.callback());
    }
    if (PositionInputx.can_callback()) {
      SelectedObject->matrix.x = std::stof(PositionInputx.callback());
    }
    if (PositionInputy.can_callback()) {
      SelectedObject->matrix.y = std::stof(PositionInputy.callback());
    }

    if (CheckCollisionPointRec(mouse, clearShaders) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      SelectedObject->clearShader();
    }

    if (IsKeyPressed(KEY_DELETE)) {
      GameObjects->erase(SelectedObject->ObjectListKey);

      // add the other list removal here when it crashes

      delete SelectedObject;
      clear();
    }
  }
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
    DrawTextEx(Fonts::Carlito, "Position:", {box.x + 50, box.y + 10}, 18, 1,
               BLACK);

    if (!PositionInputx.IsSelected) {
      PositionInputx.setText(std::to_string(SelectedObject->matrix.x));
    }
    PositionInputx.draw();
    if (!PositionInputy.IsSelected) {
      PositionInputy.setText(std::to_string(SelectedObject->matrix.y));
    }
    PositionInputy.draw();

    DrawTextEx(Fonts::Carlito, "Scale: ", {box.x + 50, box.y + 50}, 18, 1,
               BLACK);

    if (!ScaleInputx.IsSelected) {
      ScaleInputx.setText(std::to_string(SelectedObject->matrix.width));
    }
    ScaleInputx.draw();

    if (!ScaleInputy.IsSelected) {
      ScaleInputy.setText(std::to_string(SelectedObject->matrix.height));
    }
    ScaleInputy.draw();
    DrawTextEx(Fonts::Carlito, "Rotation", {box.x + 50, box.y + 90}, 18, 1,
               BLACK);

    if (!RotationInput.IsSelected) {
      RotationInput.setText(std::to_string(SelectedObject->rotation));
    }
    RotationInput.draw();

    DrawRectanglePro(shaderBox, {0, 0}, 0, Color{170, 170, 170, 255});
    DrawTextEx(Fonts::Carlito, SelectedObject->shader_path.c_str(),
               {shaderBox.x + 2, shaderBox.y + 10}, 18, 1, BLACK);
    DrawRectanglePro(clearShaders, {0, 0}, 0, Color{170, 170, 170, 255});
    DrawTextEx(Fonts::Carlito, "remove Shaders",
               {clearShaders.x + 2, clearShaders.y + 10}, 18, 1, BLACK);
  }
}
