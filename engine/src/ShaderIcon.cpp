#include "../include/ShaderIcon.hpp"
#include "ErrorMessages.hpp"
#include "ShaderObjects.hpp"
#include "fonts.hpp"
#include <raylib.h>

ShaderIcon::ShaderIcon(string &path, i32 x, i32 y) {
  scale = {
      f32(x),
      f32(y),
      BOX_WIDTH,
      128,
  };

  shader = make_unique<ShaderObject>(path);
  // just realized this wont be portable for windows
  text = path.substr(path.find_last_of('/') + 1,
                     path.size() - path.find_last_of('/') - 1);
  if (!shader->check()) {
    string errorMessage;
    errorMessage =
        "Shader {" + text +
        "} failed to be loaded, please check if the shader could compile";

    ErrorMessages::add_new(SHADER_FAILED_TO_COMPILE,
                           errorMessage); // this is kind of a hack but ehhh
    i32 charsPerLine = scale.width / fontsize;
    charsPerLine--;
    i32 lines = text.size() / charsPerLine;

    string drawText = text;

    for (i32 i = 0; i < lines; i++) {
      drawText.insert((i + 1) * charsPerLine, "\n");
    }
    text = drawText;
  }

  fontsize = 18;
  BorderThickness = 3;
}
void ShaderIcon::draw(Rectangle *barFrame) {
  Rectangle dest = {scale.x, scale.y + (barFrame->height),
                    f32((BOX_WIDTH)-BorderThickness),
                    f32((scale.height) - 2 * BorderThickness)};

  DrawRectangleLinesEx(dest, BorderThickness, Color{30, 30, 30, 255});

  DrawTextEx(Fonts::Carlito, TextFormat(text.c_str()), {dest.x + 5, dest.y + 3},
             fontsize, 1, BLACK);
}

void ShaderIcon::make_ref(node<ShaderIcon *> *reference) { ref = reference; }
