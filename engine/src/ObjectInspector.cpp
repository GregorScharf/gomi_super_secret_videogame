#include "../include/ObjectInspector.hpp"
#include "Colliders.hpp"
#include "ShaderIcon.hpp"
#include "fonts.hpp"
#include "uids.hpp"
#include <raylib.h>
#include <string>
ObjectInspector::ObjectInspector(
    shared_ptr<GameObjectContainer> GameObjectsRef,
    shared_ptr<ShaderIconContainer> ShaderObjectsRef) {
  box = {(f32)GetScreenWidth() - INSPECTOR_HEIGHT, 0, INSPECTOR_HEIGHT,
         (f32)GetScreenHeight()};

  this->selectedShader = nullptr;
  this->GameObjects = GameObjectsRef;
  this->ShaderObjects = ShaderObjectsRef;
  this->SelectedObject = nullptr;
  this->PositionInputx.set_matrix({box.x + 200, box.y + 10, 128, 28});
  this->PositionInputy.set_matrix({box.x + 350, box.y + 10, 128, 28});
  this->ScaleInputx.set_matrix({box.x + 200, box.y + 50, 128, 28});
  this->ScaleInputy.set_matrix({box.x + 350, box.y + 50, 128, 28});
  this->RotationInput.set_matrix({box.x + 200, box.y + 90, 128, 28});
  RotationInput.input_type = FLOAT;
  ScaleInputx.input_type = FLOAT;
  ScaleInputy.input_type = FLOAT;
  PositionInputx.input_type = FLOAT;
  PositionInputy.input_type = FLOAT;

  add_collider = {box.x + 10, box.y + 140, 128, 32};
  add_shader = {box.x + 150, box.y + 140, 128, 32};
  add_script = {box.x + 290, box.y + 140, 128, 32};
}

void ObjectInspector::update() {
  Vector2 mouse = GetMousePosition();
  ScaleInputx.update(mouse);
  ScaleInputy.update(mouse);
  RotationInput.update(mouse);
  PositionInputx.update(mouse);
  PositionInputy.update(mouse);

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

    if (IsKeyPressed(KEY_DELETE)) {
      GameObjects->erase(SelectedObject->ObjectListKey);

      // add the other list removal here when it crashes

      delete SelectedObject;
      clear();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (CheckCollisionPointRec(mouse, add_collider)) {
        SelectedObject->colliders.emplace(
            "new Collider " + std::to_string(UIDGenerator::GetNewUid()),
            new Collider);
      }
      if (CheckCollisionPointRec(mouse, add_shader)) {
        SelectedObject->shaders.push_back(nullptr);
      }
      if (CheckCollisionPointRec(mouse, add_script)) {
        SelectedObject->scripts.push_back("new_script.cpp");
      }
      ShaderObjects->foreach ([mouse, this](ShaderIcon *icon) {
        if (CheckCollisionPointRec(mouse, icon->scale)) {
          selectedShader = icon;
          cout << "found something\n";
        }
      });
    }
  }
}

void ObjectInspector::fill(GameObject *obj) { SelectedObject = obj; }

void ObjectInspector::clear() { SelectedObject = nullptr; }

void ObjectInspector::draw() {
  DrawRectanglePro(box, {0, 0}, 0, Color{140, 140, 140, 255});
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

    DrawRectanglePro(add_collider, {0, 0}, 0, Color{200, 200, 200, 255});
    DrawTextEx(Fonts::Carlito, "add collider", {box.x + 13, box.y + 142}, 18, 1,
               BLACK);

    DrawRectanglePro(add_shader, {0, 0}, 0, Color{200, 200, 200, 255});
    DrawTextEx(Fonts::Carlito, "add shader", {box.x + 153, box.y + 142}, 18, 1,
               BLACK);

    DrawRectanglePro(add_script, {0, 0}, 0, Color{200, 200, 200, 255});
    DrawTextEx(Fonts::Carlito, "add script", {box.x + 293, box.y + 142}, 18, 1,
               BLACK);

    u64 i = 0;
    for (i = 0; i < SelectedObject->shaders.size(); i++) {
      DrawRectangle(box.x + 1, 250 + (i * 50), INSPECTOR_HEIGHT, 50,
                    {220, 200, 200, 255});
      DrawRectangleLines(box.x + 1, 250 + (i * 50), INSPECTOR_HEIGHT, 50,
                         BLACK);
      if (SelectedObject->shaders[i]) {
        DrawTextEx(
            Fonts::Carlito,
            SelectedObject->shaders[i]
                ->path
                .substr(SelectedObject->shaders[i]->path.find_last_of("/"))
                .c_str(),
            {box.x + 10, (f32)250 + (i * 50) + 5}, 18, 1, BLACK);
      }
      DrawRectangleRounded({box.x + 300, (f32)250 + (i * 50) + 5, 200, 30}, 0.5,
                           1, {170, 170, 170, 255});
      DrawTextEx(Fonts::Carlito, "drag shader here",
                 {box.x + 302, (f32)250 + (i * 50) + 10}, 18, 1, BLACK);

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && selectedShader) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(
                mouse, {box.x + 300, (f32)250 + (i * 50) + 5, 200, 30})) {
          SelectedObject->shaders[i] = selectedShader->shader;
        }
      }
    }
    for (auto collider : SelectedObject->colliders) {
      DrawRectangle(box.x + 1, 250 + (i * 50), INSPECTOR_HEIGHT, 50,
                    {200, 220, 200, 255});
      DrawRectangleLines(box.x + 1, 250 + (i * 50), INSPECTOR_HEIGHT, 50,
                         BLACK);
      DrawTextEx(Fonts::Carlito, collider.first.c_str(),
                 {box.x + 10, (f32)250 + (i * 50) + 5}, 18, 1, BLACK);
      i++;
    }
    for (auto script : SelectedObject->scripts) {
      DrawRectangle(box.x + 1, 250 + (i * 50), INSPECTOR_HEIGHT, 50,
                    {200, 200, 220, 255});
      DrawRectangleLines(box.x + 1, 250 + (i * 50), INSPECTOR_HEIGHT, 50,
                         BLACK);
      DrawTextEx(Fonts::Carlito, script.c_str(),
                 {box.x + 10, (f32)250 + (i * 50) + 5}, 18, 1, BLACK);
      i++;
    }
  }
}
