#pragma once
#include "GameObjects.hpp"
#include "TextInputWindows.hpp"
#include "containers.hpp"
#include "types.hpp"
#include <raylib.h>

#define INSPECTOR_HEIGHT 400
#define INSPECTOR_WIDTH_IS_FULL 1


// subclass of the selection
class ObjectInspector {
  GameObject *SelectedObject;
  shared_ptr<GameObjectContainer> GameObjects;

  TextInputWindow ScaleInputx, ScaleInputy, PositionInputx, PositionInputy,
      RotationInput;

public:
  ObjectInspector(Rectangle *selectionWindow);
  void fill(GameObject *obj);
  void clear();

  void update();
  void draw(Rectangle *selectionWindow);
};
