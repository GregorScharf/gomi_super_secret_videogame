#include "../include/Selection.hpp"
#include "Icons.hpp"
#include "ShaderIcon.hpp"
#include "containers.hpp"
#include "selectable.hpp"
#include "utils.hpp"
#include <memory>
#include <raylib.h>

Selection::Selection(shared_ptr<GameObjectContainer> GOR,
                     shared_ptr<IconContainer> IR, Camera2D *cameraRef) {
  GameObjectsRef = GOR;
  IconsRef = IR;
  Selected = new Selectable;
  currentLayer = 0;
  camera = cameraRef;
  isSelected = false;
  selectionWindow = {0, 0, BOX_WIDTH * 2, (f32)GetScreenHeight()};
}

void Selection::update(bool IconsSeletable, bool ShadersSelectable) {

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isSelected) {
    Vector2 Mouse = GetMousePosition();

    Objects.foreach (
        [this, Mouse, IconsSeletable, ShadersSelectable](Selectable *object) {
          switch (object->type) {
          case ICON:
            if (IconsSeletable) {
              if (CheckCollisionPointRec(Mouse,
                                         ((TextureIcon *)object->ptr)->scale)) {
                this->Selected->ptr = (Selectable *)object->ptr;
                this->Selected->type = ICON;
                this->isSelected = true;
              }
            }
            break;
          case OBJECT:
            break;
          case SHADERICON:
            if (ShadersSelectable) {
              if (CheckCollisionPointRec(Mouse,
                                         ((ShaderIcon *)object->ptr)->scale)) {
                this->Selected->ptr = (Selectable *)object->ptr;
                this->Selected->type = ICON;
                this->isSelected = true;
              }
            }
            break;
          }
        });
  }

  if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && Selected && isSelected) {
      Vector2 Mouse = GetMousePosition();
      Rectangle WindowRec = {0, 0, (f32)GetScreenWidth(),
                             (f32)GetScreenHeight()};
      switch (Selected->type) {
      case ICON:
        if (!CheckCollisionPointRec(Mouse, selectionWindow) &&
            CheckCollisionPointRec(Mouse, WindowRec)) {
          TextureIcon *p = (TextureIcon *)Selected->ptr;
          auto pt = GameObjectsRef->add_new(p, camera, *currentLayer);
          auto node = Objects.append(pt);
          node->data->type = OBJECT;
          pt->ptr = pt;
          pt->key = node;
          isSelected = false;
          Selected->ptr = nullptr;
          Selected->key = nullptr;
        }
        break;
      case OBJECT:
        break;
      case SHADERICON:
        if (CheckCollisionPointRec(Mouse, *shaderBox)) {
          if (InspectorRef->SelectedObject) {
            auto p = (ShaderIcon *)Selected->ptr;
            InspectorRef->SelectedObject->setShader(p->text, &p->shader);
          }
        }
        break;
      }
    } else {
      isSelected = false;
      Selected->key = nullptr;
      Selected->ptr = nullptr;
    }
  }
}

void Selection::draw() {
  if (isSelected && Selected) {
    if (Selected->type == ICON) {
      auto p = (TextureIcon *)Selected->ptr;
      Vector2 mouse = GetMousePosition();

      DrawTexturePro(p->texture,
                     {0, 0, (f32)p->texture.width, (f32)p->texture.height},
                     {mouse.x, mouse.y, p->texture.width * (f32)0.4,
                      p->texture.height * (f32)0.4},
                     {(f32)p->texture.width * (f32)0.4 / 2,
                      (f32)p->texture.height * (f32)0.4 / 2},
                     0, Color{100, 200, 255, 100});
    }
  }
}

Selection::~Selection() { delete Selected; }
