#pragma once
#include "GameObjects.hpp"
#include "TextInputWindows.hpp"
#include "containers.hpp"
#include "types.hpp"
#include <raylib.h>

// subclass of the selection
class ObjectInspector {
  GameObject *SelectedObject;
  shared_ptr<GameObjectContainer> GameObjects;

  TextInputWindow ScaleInput, PositionInput, RotationInput;

public:
  ObjectInspector(Rectangle *selectionWindow);
  void fill(GameObject *obj);
  void clear();

  void update();
  void draw(Rectangle *selectionWindow);
};
