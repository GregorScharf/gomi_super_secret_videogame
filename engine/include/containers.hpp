#pragma once

#include "GameObjects.hpp"
#include "Icons.hpp"
#include "ShaderIcon.hpp"
#include "list.hpp"
#include "selectable.hpp"
#include "types.hpp"
#include <raylib.h>

class GameObjectContainer {
  vector<DLinkedList<GameObject *> *> Layers;

public:
  GameObject *add_new(TextureIcon *icon, Camera2D *camera, u8 Layer);

  // this can get really, really expensive, so be careful
  void foreach (std::function<void(GameObject *)> func);

  void draw(Camera2D *camera);
};

class IconContainer {
  DLinkedList<TextureIcon *> Icons;

public:
  TextureIcon *add_new(string path, i32 x, i32 y);

  void foreach (std::function<void(TextureIcon *)> func);

  void draw(Rectangle *barFrame);
};

class ShaderIconContainer {
  DLinkedList<ShaderIcon *> Icons;

public:
  ShaderIcon *add_new(string path, i32 x, i32 y);

  void foreach (std::function<void(ShaderIcon *)> func);

  void draw(Rectangle *barFrame);
};
