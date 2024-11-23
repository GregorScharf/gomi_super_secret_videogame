#pragma once
#include "GameObjects.hpp"
#include "Icons.hpp"
#include "ObjectInspector.hpp"
#include "Selection.hpp"
#include "containers.hpp"
#include "list.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "windowbar.hpp"
#include <functional>
#include <memory>
#include <raylib.h>

class EngineState {
  shared_ptr<GameObjectContainer> Objects;
  shared_ptr<IconContainer> icons;
  shared_ptr<ShaderIconContainer> ShaderIcons;
  unique_ptr<Selection> selection;
  Rectangle selectionWindow;
  Camera2D SceneCam;
  Camera2D UICam;
  WindowBar Bar;
  unique_ptr<ObjectInspector> inspector;

public:
  EngineState();
  ~EngineState();
  void loop();
};
