#pragma once
#include "types.hpp"
#include <raylib.h>

// raysan, please don't make me regret this
class TextInputWindow {
  string text;
  Rectangle matrix;
  bool IsSelected;

public:
  TextInputWindow();
  void set_matrix(Rectangle newMatrix);
  string &getText();
  void update(Vector2 mouse);
  void draw();
  void setText(string newText);
};
