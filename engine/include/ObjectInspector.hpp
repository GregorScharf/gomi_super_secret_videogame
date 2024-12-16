#pragma once
#include "GameObjects.hpp"
#include "ShaderIcon.hpp"
#include "TextInputWindows.hpp"
#include "containers.hpp"
#include "types.hpp"
#include <memory>
#include <raylib.h>

#define INSPECTOR_HEIGHT 512
#define INSPECTOR_WIDTH_IS_FULL 1

class ObjectInspector {
  shared_ptr<GameObjectContainer> GameObjects;
  shared_ptr<ShaderIconContainer> ShaderObjects;

  TextInputWindow ScaleInputx, ScaleInputy, PositionInputx, PositionInputy,
      RotationInput;
  ShaderIcon *selectedShader;

public:
  GameObject *SelectedObject;
  Rectangle box, add_shader, add_script, add_collider;
  ObjectInspector(shared_ptr<GameObjectContainer> GameObjectsRef,
                  shared_ptr<ShaderIconContainer> ShaderObjectsRef);
  void fill(GameObject *obj);
  void clear();

  void update();
  void draw();
};
