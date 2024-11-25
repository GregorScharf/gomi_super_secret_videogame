#include "../include/TextInputWindows.hpp"
#include "utils.hpp"
#include <raylib.h>
#include <string>

string &TextInputWindow::getText() { return text; }

TextInputWindow::TextInputWindow() {
  matrix = {0, 0, 0, 0};
  IsSelected = false;
  callBackAvailable = false;
}

bool TextInputWindow::can_callback() { return callBackAvailable; }

string TextInputWindow::callback() {
  IsSelected = false;
  callBackAvailable = false;
  return text;
}

void TextInputWindow::draw() {
  DrawRectangleRounded(matrix, 3, 0, Color{120, 120, 120, 255});
  DrawRectangleRoundedLines(matrix, 3, 0, Color{170, 170, 170, 255});
  DrawText(text.c_str(), matrix.x + 10, matrix.y + 5, 18, RAYWHITE);
}

void TextInputWindow::set_matrix(Rectangle newMatrix) { matrix = newMatrix; }

#define MAX_LETTERS_INPUT 12

i32 TextInputWindow::setText(string newText) {
  if (!IsSelected) {
    text = newText;
    return true;
  }
  return false;
}

void TextInputWindow::update(Vector2 mouse) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (CheckCollisionPointRec(mouse, matrix)) {
      IsSelected = true;
      text.clear();

    } else {
      IsSelected = false;
    }
  }
  if (IsSelected) {
    char key = GetCharPressed();
    while (key > 0) {
      if (((key >= 48) && (key <= 57)) || key == 46) {
        if (text.size() <= MAX_LETTERS_INPUT) {
          text.push_back(key);
        }
      }
      key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && text.size() > 0) {
      text.erase(text.size() - 1, 1);
    }
    if (IsKeyPressed(KEY_ENTER)) {
      switch (input_type) {
      case STRING:
        callBackAvailable = true;
        break;
      case INTEGER:
        if (is_int(text)) {
          callBackAvailable = true;
        } else {
          callBackAvailable = false;
          // TODO: log some user error here or something
        }
        break;
      case UNSIGNED_INT:
        if (is_uint(text)) {
          callBackAvailable = true;
        } else {
          callBackAvailable = false;
          // add the error here aswell
        }
        break;
      case FLOAT:
        if (is_float(text)) {
          callBackAvailable = true;
        } else {
          callBackAvailable = false;
          // add the error here aswell
        }

        break;
      case NO_TYPE:
        callBackAvailable = false;
        break;
      }
    }
  }
}
