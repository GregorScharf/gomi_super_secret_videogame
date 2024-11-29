#include "../include/containers.hpp"
#include "GameObjects.hpp"
#include "Icons.hpp"
#include "LayerIcons.hpp"
#include "ShaderIcon.hpp"
#include "list.hpp"
#include <memory>
#include <raylib.h>

// don't show this to anyone i beg of you
void IconContainer::foreach (std::function<void(TextureIcon *)> func) {
  Icons.foreach (func);
}

void IconContainer::draw(Rectangle *barFrame) {

  Icons.foreach ([barFrame](TextureIcon *icon) { icon->draw(barFrame); });
}
TextureIcon *IconContainer::add_new(string path, i32 x, i32 y) {

  TextureIcon *newIcon = new TextureIcon(path, x, y);
  auto ref = Icons.append(newIcon);
  newIcon->make_ref(ref);
  return newIcon;
}

GameObjectContainer::GameObjectContainer() {
  Layers.push_back(new DLinkedList<GameObject *>());
}

GameObject *GameObjectContainer::add_new(TextureIcon *icon, Camera2D *camera,
                                         u8 Layer) {
  if (Layer >= Layers.size()) {
    for (i32 i = Layers.size(); i <= Layer; i++) {
      Layers.push_back(new DLinkedList<GameObject *>());
    }
  }

  Vector2 mouse = GetMousePosition();
  auto newObject = new GameObject(GetScreenToWorld2D(mouse, *camera),
                                  &icon->texture, icon->text, Layer);
  auto ref = Layers[Layer]->append(newObject);
  newObject->ObjectListKey = ref;
  return newObject;
}

void GameObjectContainer::foreach (std::function<void(GameObject *)> func) {
  for (auto layer : Layers) {
    layer->foreach (func);
  }
}

void GameObjectContainer::draw(Camera2D *camera) {

  for (auto layer : Layers) {
    if (!(Layers[*currentLayer] == layer)) {
      layer->foreach ([camera](GameObject *obj) {
        Vector2 screen_pos =
            GetWorldToScreen2D({obj->matrix.x, obj->matrix.y}, *camera);
        Rectangle drawMatrix = {screen_pos.x, screen_pos.y,
                                obj->matrix.width * camera->zoom,
                                obj->matrix.height * camera->zoom};
        DrawTexturePro(
            *obj->texture,
            {0, 0, (f32)obj->texture->width, (f32)obj->texture->height},
            drawMatrix, {drawMatrix.width / 2, drawMatrix.height / 2},
            obj->rotation, RAYWHITE);
      });
    }
  }
  Layers[*currentLayer]->foreach ([camera](GameObject *obj) {
    Vector2 screen_pos =
        GetWorldToScreen2D({obj->matrix.x, obj->matrix.y}, *camera);
    Rectangle drawMatrix = {screen_pos.x, screen_pos.y,
                            obj->matrix.width * camera->zoom,
                            obj->matrix.height * camera->zoom};
    DrawTexturePro(*obj->texture,
                   {0, 0, (f32)obj->texture->width, (f32)obj->texture->height},
                   drawMatrix, {drawMatrix.width / 2, drawMatrix.height / 2},
                   obj->rotation, RAYWHITE);
  });
}
void ShaderIconContainer::foreach (std::function<void(ShaderIcon *)> func) {
  Icons.foreach (func);
}

void ShaderIconContainer::draw(Rectangle *barFrame) {

  Icons.foreach ([barFrame](ShaderIcon *icon) { icon->draw(barFrame); });
}
ShaderIcon *ShaderIconContainer::add_new(string path, i32 x, i32 y) {

  ShaderIcon *newIcon = new ShaderIcon(path, x, y);
  auto ref = Icons.append(newIcon);
  newIcon->make_ref(ref);
  return newIcon;
}

LayerContainer::LayerContainer(Rectangle *barFrame,
                               shared_ptr<GameObjectContainer> GameObjects) {
  this->GameObjectstRef = GameObjects;
  this->LayerAmount = 1;
  this->currentLayer = 0;
  this->barFrameRef = barFrame;
  this->Icons.append(new LayerIcon(currentLayer, barFrame));
  this->selected = nullptr;
}

void LayerContainer::draw() {
  Icons.foreach ([this](LayerIcon *icon) {
    if (icon->LayerIndex == currentLayer) {
      DrawRectangleRec({0, icon->box.y, 2 * BOX_WIDTH, BOX_WIDTH / 4},
                       Color{100, 200, 255, 200});
    }
    icon->draw();
  });
  DrawRectangleRounded(
      {barFrameRef->x + 300, barFrameRef->height + 20, 128, 20}, 2, 0,
      Color{170, 170, 170, 255});
  DrawRectangleRoundedLinesEx(
      {barFrameRef->x + 300, barFrameRef->height + 20, 128, 20}, 2, 0, 2,
      BLACK);
  DrawText("Add new Layer", barFrameRef->x + 305, barFrameRef->height + 21, 18,
           BLACK);
}

void LayerContainer::add_new() {

  // hard cap that shit
  if (!(LayerAmount > 254)) {
    Icons.append(new LayerIcon(LayerAmount, barFrameRef));
    GameObjectstRef->Layers.push_back(new DLinkedList<GameObject *>());
    LayerAmount++;
  }
}

void LayerContainer::update() {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse = GetMousePosition();
    Icons.foreach ([this, mouse](LayerIcon *icon) {
      if (CheckCollisionPointRec(mouse, icon->box)) {
        if (!CheckCollisionPointRec(
                mouse,
                {barFrameRef->x + 300, barFrameRef->height + 20, 128, 20})) {
          currentLayer = icon->LayerIndex;
          selected = icon;
        }
      }
    });
    if (CheckCollisionPointRec(
            mouse, {barFrameRef->x + 300, barFrameRef->height + 20, 128, 20})) {
      add_new();
    }
  }
  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && selected) {
    Vector2 mouse = GetMousePosition();
    Icons.foreach ([this, mouse](LayerIcon *icon) {
      if (CheckCollisionPointRec(mouse, icon->box)) {
        Rectangle tmp;
        tmp = selected->box;
        selected->box = icon->box;
        icon->box = tmp;
        u8 layer_swp;
        layer_swp = selected->LayerIndex;
        selected->LayerIndex = icon->LayerIndex;
        icon->LayerIndex = layer_swp;
      }
    });
  }
}
