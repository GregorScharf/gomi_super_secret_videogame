#pragma once

#include "GameObjects.hpp"
#include "Icons.hpp"
#include "LayerIcons.hpp"
#include "ShaderIcon.hpp"
#include "list.hpp"
#include "selectable.hpp"
#include "types.hpp"
#include <memory>
#include <raylib.h>

struct Layer {
  u64 uid;
  DLinkedList<GameObject *> *Layer;
};

class GameObjectContainer {

public:
public:
  vector<Layer *> Layers;
  GameObjectContainer();
  u8 *currentLayer;
  GameObject *add_new(TextureIcon *icon, Camera2D *camera, u8 Layer);
  void erase(node<GameObject *> *node);

  // this can get really, really expensive, so be careful
  void foreach (std::function<void(GameObject *)> func);

  void draw(Camera2D *camera);
};

class IconContainer {
  DLinkedList<TextureIcon *> Icons;

public:
  void load();

  TextureIcon *add_new(string path, i32 x, i32 y);

  void foreach (std::function<void(TextureIcon *)> func);

  void draw(Rectangle *barFrame);
};

class ShaderIconContainer {
  DLinkedList<ShaderIcon *> Icons;
  Rectangle *shaderAttributeBox;

public:
  void load();

  ShaderIcon *add_new(string path, i32 x, i32 y);

  void update();

  void foreach (std::function<void(ShaderIcon *)> func);

  void draw(Rectangle *barFrame);
};

class LayerContainer {
  DLinkedList<LayerIcon *> Icons;
  Rectangle *barFrameRef;
  u8 LayerAmount;
  shared_ptr<GameObjectContainer> GameObjectstRef;
  LayerIcon *selected;

public:
  u8 currentLayer;
  LayerContainer(Rectangle *barFrame,
                 shared_ptr<GameObjectContainer> GameObjects);
  void add_new();
  void update();
  void draw();
  void clear();
};
