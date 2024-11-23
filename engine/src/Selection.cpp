#include "../include/Selection.hpp"
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

void Selection::update(bool IconsSeletable) {

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isSelected) {
    Vector2 Mouse = GetMousePosition();

    cout << Mouse.x << "  " << Mouse.y << endl;
    Objects.foreach ([this, Mouse, IconsSeletable](Selectable *object) {
      switch (object->type) {
      case ICON:
        cout << "ICON\n";
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
        cout << "OBJECT\n";
        GameObject *p = (GameObject *)object->ptr;
        Vector2 screen =
            GetWorldToScreen2D({p->matrix.x, p->matrix.y}, *camera);
        cout << screen.x << "  " << screen.y << "  " << p->matrix.width << "  "
             << p->matrix.height << endl;

        if (CheckCollisionPointRec(Mouse, {screen.x, screen.y, p->matrix.width,
                                           p->matrix.height})) {
        }
        break;
      }
    });
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && Selected && isSelected) {
    Vector2 Mouse = GetMousePosition();
    Rectangle WindowRec = {0, 0, (f32)GetScreenWidth(), (f32)GetScreenHeight()};
    switch (Selected->type) {
    case ICON:
      if (!CheckCollisionPointRec(Mouse, selectionWindow) &&
          CheckCollisionPointRec(Mouse, WindowRec)) {
        TextureIcon *p = (TextureIcon *)Selected->ptr;
        auto pt = GameObjectsRef->add_new(p, camera, currentLayer);
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
    }
  }
}

void Selection::draw() {
  DrawRectangleRec(selectionWindow, Color{140, 140, 140, 255});
}

Selection::~Selection() { delete Selected; }
