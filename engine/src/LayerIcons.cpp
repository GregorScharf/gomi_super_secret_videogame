#include "../include/LayerIcons.hpp"
#include "Icons.hpp"

LayerIcon::LayerIcon(u8 index, Rectangle *barFrame) {
  this->LayerIndex = index;

  this->box = {barFrame->x, barFrame->height + (index * (BOX_WIDTH / 4)),
               BOX_WIDTH * 2, BOX_WIDTH / 4};
}

void LayerIcon::draw() {
  DrawRectangleLinesEx(box, 3, Color{10, 10, 10, 255});
  DrawText(TextFormat("Layer %i", LayerIndex), box.x + 5, box.y + 25, 20,
           BLACK);
}
