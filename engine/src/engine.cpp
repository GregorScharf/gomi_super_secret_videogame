#include "../include/engine.hpp"
#include "GameObjects.hpp"
#include "Icons.hpp"
#include "ObjectDragging.hpp"
#include "ObjectInspector.hpp"
#include "ShaderIcon.hpp"
#include "containers.hpp"
#include "utils.hpp"
#include <memory>
#include <raylib.h>

EngineState::EngineState() {

  // uggggghhhhhhhhhhhhhhhhhhhhhhhhh

  InitWindow(0, 0, "levelbuilder");

  i32 monitor = GetCurrentMonitor();

  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  if (!IsWindowFullscreen()) {
    ToggleFullscreen();
  }
  string path = fs::current_path();
  if (path.find("build") != string::npos) {
    path = path.substr(0, path.find("build"));
  }
  Objects = make_shared<GameObjectContainer>();
  icons = make_shared<IconContainer>();
  ShaderIcons = make_shared<ShaderIconContainer>();
  LayerIcons = make_shared<LayerContainer>(&Bar.barFrame, Objects);

  selection = make_unique<Selection>(Objects, icons, &SceneCam);

  inspector = make_unique<ObjectInspector>(&selection->selectionWindow);

  i32 left_offset_tx = 0;
  i32 left_offset_sh = 0;

  i32 top_offset_tx = 0;
  i32 top_offset_sh = 0;

  SceneCam.target = {
      (f32)(GetScreenWidth() - selection->selectionWindow.width) / 2,
      (f32)(GetScreenHeight() - INSPECTOR_HEIGHT) / 2};
  SceneCam.offset = {(f32)GetScreenWidth() / 2, (f32)GetScreenHeight() / 2};
  SceneCam.rotation = 0;
  SceneCam.zoom = 1;

  dragger = make_unique<Dragger>(&SceneCam);

  UICam.zoom = 1;     // this should never change, i hope
  UICam.rotation = 0; // same goes for here
  UICam.offset = {(f32)GetScreenWidth() / 2,
                  (f32)GetScreenHeight() / 2 - Bar.barFrame.height};
  UICam.target = {(f32)GetScreenWidth() / 2,
                  (f32)GetScreenHeight() / 2 + Bar.barFrame.height / 2};

  SetTargetFPS(60);

  Objects->currentLayer = &LayerIcons->currentLayer;
  selection->currentLayer = &LayerIcons->currentLayer;
  Bar.Layers->SelectedLayer = &LayerIcons->currentLayer;

  // sweet mother of jesus
  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.is_regular_file()) {
      if (endswith(entry.path(), ".png")) {
        TextureIcon *icon =
            icons->add_new(entry.path(), left_offset_tx * BOX_WIDTH,
                           top_offset_tx * (BOX_WIDTH / 2));
        selection->new_object<TextureIcon>(icon, ICON);
        left_offset_tx++;
        if (left_offset_tx * BOX_WIDTH >= BOX_WIDTH * 2) {
          left_offset_tx = 0;
          top_offset_tx++;
        }
      }
      if (endswith(entry.path(), ".frag") ||
          endswith(entry.path(), ".shader")) {
        ShaderIcon *icon =
            ShaderIcons->add_new(entry.path(), left_offset_sh * BOX_WIDTH,
                                 top_offset_sh * BOX_WIDTH);
        selection->new_object<ShaderIcon>(icon, SHADERICON);
      }
    }
  }

  this->loop();
}

EngineState::~EngineState() {
  this->selection.reset();
  this->Objects->foreach ([](GameObject *obj) {
    delete obj;
    obj = nullptr;
  });
  this->Objects.reset();
  this->icons->foreach ([](TextureIcon *icon) {
    delete icon;
    icon = nullptr;
  });
  this->icons.reset();
}

void EngineState::loop() {

  while (!WindowShouldClose()) {

    dragger->update();

    selection->update(Bar.icons->IsOpen);
    if (SceneCam.zoom + GetMouseWheelMove() * 0.02 > 0.0899998 &&
        SceneCam.zoom + GetMouseWheelMove() * 0.02 < 10) {
      SceneCam.zoom += (f32)GetMouseWheelMove() * 0.02;
    }

    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
      SceneCam.target.x -= GetMouseDelta().x * 1 / SceneCam.zoom;
      SceneCam.target.y -= GetMouseDelta().y * 1 / SceneCam.zoom;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mouse = GetMousePosition();
      if (CheckCollisionPointRec(mouse,
                                 {selection->selectionWindow.width, 0,
                                  GetScreenWidth() - selectionWindow.width,
                                  (f32)GetScreenHeight() - INSPECTOR_HEIGHT})) {
        inspector->clear();
        bool one_selected = false;
        Objects->foreach ([this, mouse, &one_selected](GameObject *obj) {
          Rectangle r = RecWorldToScreen(&obj->matrix, &SceneCam);

          r.x -= r.width / 2;
          r.y -= r.height / 2;
          if (CheckCollisionPointRec(mouse, r)) {
            inspector->fill(obj);
            dragger->fill(obj);
            one_selected = true;
          }
        });
        if (!one_selected) {
          dragger->clear();
          inspector->clear();
        }
      }
      if (Bar.Layers->IsOpen) {
      }
    }

    Bar.update();
    inspector->update();

    BeginDrawing();
    ClearBackground(BLACK);

    Objects->draw(&SceneCam);
    dragger->draw();
    DrawRectangleRec(selection->selectionWindow, Color{140, 140, 140, 255});
    if (Bar.icons->IsOpen) {
      icons->draw(&Bar.barFrame);
    }
    if (Bar.shaders->IsOpen) {
      ShaderIcons->draw(&Bar.barFrame);
    }
    if (Bar.Layers->IsOpen) {
    LayerIcons->update();
      LayerIcons->draw();
    }
    inspector->draw(&selection->selectionWindow);
    selection->draw();
    Bar.draw();
    EndDrawing();
  }
}
