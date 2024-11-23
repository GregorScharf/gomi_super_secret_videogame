#pragma once
#include "GameObjects.hpp"
#include "containers.hpp"
#include "types.hpp"
#include <raylib.h>

// subclass of the selection
class ObjectInspector {
  GameObject *SelectedObject;
  shared_ptr<GameObjectContainer> GameObjects;

public:
  ObjectInspector();
  void fill(GameObject *obj);
  void clear();

  void update();
  void draw(Rectangle *selectionWindow);
};
