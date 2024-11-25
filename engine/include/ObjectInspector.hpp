#pragma once
#include "GameObjects.hpp"
#include "TextInputWindows.hpp"
#include "TextInputWindows.hpp"
#include "containers.hpp"
#include "types.hpp"
#include <raylib.h>

#define INSPECTOR_HEIGHT 400
#define INSPECTOR_WIDTH_IS_FULL 1

#define INSPECTOR_HEIGHT 400
#define INSPECTOR_WIDTH_IS_FULL 1

class ObjectInspector {
  shared_ptr<GameObjectContainer> GameObjects;

  TextInputWindow ScaleInputx, ScaleInputy, PositionInputx, PositionInputy,
      RotationInput;

public:
  GameObject *SelectedObject;
  Rectangle shaderBox, clearShaders;
  ObjectInspector(Rectangle *selectionWindow,
                  shared_ptr<GameObjectContainer> GameObjectsRef);
  void fill(GameObject *obj);
  void clear();

  void update();
  void draw(Rectangle *selectionWindow);
};
