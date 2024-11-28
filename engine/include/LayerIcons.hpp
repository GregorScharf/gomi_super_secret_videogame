#pragma once
#include "types.hpp"
#include <raylib.h>

class LayerIcon {

public:
  u8 LayerIndex;
  Rectangle box;
  LayerIcon(u8 index, Rectangle *barFrame);
  void draw();
};
