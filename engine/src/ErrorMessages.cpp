#include "../include/ErrorMessages.hpp"
#include "fonts.hpp"
#include <raylib.h>

vector<ErrorMessage *> ErrorMessages::messages;
void ErrorMessage::draw(i32 index) {
  Rectangle r = {(f32)GetScreenWidth() - 300, (f32)150 * index + 40, 300, 128};
  DrawRectanglePro(r, {0, 0}, 0, Color{120, 120, 120, 255});
  DrawTextEx(Fonts::Carlito, TextFormat(errorMessage.c_str()),
             {r.x + 2, r.y + 10}, 16, 1, BLACK);
}

void ErrorMessages::draw() {
  for (u64 i = 0; i < messages.size(); i++) {
    messages[i]->draw(i);
  }
}

i32 ErrorMessages::add_new(ErrorCodes code, string &message) {
  auto p = new ErrorMessage;
  p->ErrorCode = code;
  p->errorMessage = "";
  switch (code) {
  case SHADER_FAILED_TO_COMPILE:
    p->errorMessage += "ERROR: FAILED TO COMPILE A SHADER\n";
    p->errorMessage += message;
    break;
  case TEXTURE_FAILED_TO_LOAD:
    p->errorMessage += "ERROR: FAILED TO LOAD A TEXTURE\n";
    p->errorMessage += message;
    break;
  case DYNAMIC_TYPE_CONVERSION_FAILED:
    p->errorMessage += "ERROR: FAILED TYPE CONVERSION\n";
    p->errorMessage += message;
    break;
  }

  i32 charsPerLine = (300 / 16) * 2;
  charsPerLine -= 5;
  i32 lines = p->errorMessage.size() / charsPerLine;

  for (i32 i = 0; i < lines; i++) {
    p->errorMessage.insert((i + 1) * charsPerLine, "\n");
  }

  messages.push_back(p);
  return messages.size() - 1;
}

void ErrorMessages::remove(i32 i) {
  delete messages[i];
  messages.erase(messages.begin() + i);
}
