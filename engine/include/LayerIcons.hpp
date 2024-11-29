#pragma once
#include "TextInputWindows.hpp"
#include "types.hpp"
#include <raylib.h>

class LayerIcon {

public:
  u8 LayerIndex;
  Rectangle box;
  TextInputWindow name;
  LayerIcon(u8 index, Rectangle *barFrame);
  void draw();
};
