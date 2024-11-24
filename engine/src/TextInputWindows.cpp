#include "../include/TextInputWindows.hpp"
#include <raylib.h>

string &TextInputWindow::getText() { return text; }

TextInputWindow::TextInputWindow() {
  matrix = {0, 0, 0, 0};
  IsSelected = false;
}

void TextInputWindow::draw() {
  DrawRectangleRounded(matrix, 3, 0, Color{120, 120, 120, 255});
  DrawRectangleRoundedLines(matrix, 3, 0, Color{170, 170, 170, 255});
  DrawText(text.c_str(), matrix.x + 10, matrix.y + 5, 18, RAYWHITE);
}

void TextInputWindow::set_matrix(Rectangle newMatrix) { matrix = newMatrix; }

#define MAX_LETTERS_INPUT 12

void TextInputWindow::setText(string newText) { text = newText; }

void TextInputWindow::update(Vector2 mouse) {
  if (CheckCollisionPointRec(mouse, matrix)) {

    int key = GetCharPressed();

    while (key > 0) {
      if ((key >= 32) && (key <= 125) && (text.size() < MAX_LETTERS_INPUT)) {
        text.append((char *)&(key)); // not sure if this works
      }
      key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
      text.erase(text.size(), 1);
    }
  }
}
