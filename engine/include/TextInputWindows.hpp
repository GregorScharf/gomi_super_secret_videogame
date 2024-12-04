#pragma once
#include "types.hpp"
#include <raylib.h>

// raysan, please don't make me regret this
// update: i hate you raysan

typedef enum INPUT_TYPES {
  STRING = 0,
  INTEGER = 1,
  UNSIGNED_INT = 2,
  FLOAT = 3,
  NO_TYPE = 4 // default, set to something else after construction
} INPUT_TYPES;

class TextInputWindow {
  string text;
  Rectangle matrix;
  bool callBackAvailable;

public:
  u64 max_input_length = 12;
  bool IsSelected;
  INPUT_TYPES input_type;
  bool can_callback();
  string callback();
  TextInputWindow();
  void set_matrix(Rectangle newMatrix);
  string &getText();
  void update(Vector2 mouse);
  void draw();
  i32 setText(string newText);
};
