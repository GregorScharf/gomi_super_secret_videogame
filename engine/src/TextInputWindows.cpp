#include "../include/TextInputWindows.hpp"
#include "fonts.hpp"
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
  DrawRectangleRounded(matrix, 2, 0, Color{120, 120, 120, 255});
  if (!IsSelected) {
    DrawRectangleRoundedLines(matrix, 2, 0, Color{170, 170, 170, 255});
  } else {
    DrawRectangleRoundedLines(matrix, 2, 0, Color{100, 170, 255, 255});
  }
  DrawTextEx(Fonts::Carlito, text.c_str(), {matrix.x + 10, matrix.y + 5}, 18, 1,
             RAYWHITE);
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

    } else {
      IsSelected = false;
    }
  }
  if (IsSelected) {
    char key = GetCharPressed();
    while (key > 0) {
      switch (input_type) {
      case STRING:
        if (text.size() <= max_input_length) {
          text.push_back(key);
        }
        break;
      case INTEGER:
        if (((key >= 48) && (key <= 57)) || key == 45) {
          if (text.size() <= max_input_length) {
            text.push_back(key);
          }
        }
        break;
      case UNSIGNED_INT:
        if (((key >= 48) && (key <= 57))) {
          if (text.size() <= max_input_length) {
            text.push_back(key);
          }
        }
        break;
      case FLOAT:
        if (((key >= 48) && (key <= 57)) || key == 46) {
          if (text.size() <= max_input_length) {
            text.push_back(key);
          }
        }
        break;
      }
      key = GetCharPressed();
    }
    if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) &&
        text.size() > 0) {
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
