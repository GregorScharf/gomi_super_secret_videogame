#include "../include/LayerIcons.hpp"
#include "Icons.hpp"
#include "TextInputWindows.hpp"
#include <raylib.h>
#include <string>

LayerIcon::LayerIcon(u8 index, Rectangle *barFrame) {
  this->LayerIndex = index;

  this->box = {barFrame->x, barFrame->height + (index * (BOX_WIDTH / 4)),
               BOX_WIDTH * 2, BOX_WIDTH / 4};
  this->name.set_matrix({box.x + 10, box.y + 10, 250, 28});
  this->name.setText("Layer " + std::to_string(*(i32*)&index));
  this->name.input_type = STRING;
  this->name.max_input_length = 20;
}

void LayerIcon::draw() {
  name.update(GetMousePosition());
  DrawRectangleLinesEx(box, 3, Color{10, 10, 10, 255});
  this->name.set_matrix({box.x + 10, box.y + 10, 250, 28});
  name.draw();
}
