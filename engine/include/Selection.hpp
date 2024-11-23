#pragma once
#include "GameObjects.hpp"
#include "Icons.hpp"
#include "ObjectInspector.hpp"
#include "ShaderIcon.hpp"
#include "containers.hpp"
#include "list.hpp"
#include "selectable.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <boost/static_assert.hpp>
#include <memory>
#include <raylib.h>

class Selection {

  DLinkedList<Selectable *> Objects; // all objects get added here

  Selectable *Selected = nullptr;
  bool isSelected;
  Camera2D *camera;

  ObjectInspector inspector;

  shared_ptr<GameObjectContainer> GameObjectsRef;
  shared_ptr<IconContainer> IconsRef;

public:
  Rectangle selectionWindow;
  Rectangle *shaderBox;
  shared_ptr<ObjectInspector> InspectorRef;

  u8 *currentLayer;
  Selection(shared_ptr<GameObjectContainer> GOR, shared_ptr<IconContainer> IR,
            Camera2D *cameraRef);
  ~Selection();

  void update(bool IconsSeletable, bool ShadersSelectable);

  template <typename ObjectType>
  node<Selectable *> *new_object(Selectable *newObject, SelectableType Type) {

    BOOST_STATIC_ASSERT((std::is_base_of<Selectable, ObjectType>::value));

    // this is some crazy UB, fix this as soon as possible
    auto node = Objects.append(newObject);
    node->data->type = Type;
    node->data->key = node;
    node->data->ptr = newObject;
    return node;
  }
  void draw();
};
