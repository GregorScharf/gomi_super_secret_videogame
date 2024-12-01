#pragma once
#include "types.hpp"
#include <raylib.h>

class Fonts {
public:
  static Font defaultFont, Carlito;

  static void LoadFonts();

  static void UnloadFonts();
};
