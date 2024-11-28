#include "../include/Icons.hpp"
#include <raylib.h>

TextureIcon::TextureIcon(string path, i32 x, i32 y) {
  scale = {
      f32(x),
      f32(y),
      BOX_WIDTH,
      128,
  };
  texture = LoadTexture(path.c_str());

  text = path.substr(path.find_last_of('/') + 1,
                     path.size() - path.find_last_of('/') - 1);
  fontsize = 18;
  BorderThickness = 3;
}

void TextureIcon::make_ref(node<TextureIcon *> *reference) { ref = reference; }

void TextureIcon::draw(Rectangle *barFrame) {

  // this is kind of a hack but ehhh
  i32 charsPerLine = scale.width / fontsize;
  charsPerLine--;
  Rectangle dest = {scale.x, scale.y + barFrame->height,
                    f32((BOX_WIDTH)-BorderThickness),
                    f32((scale.height) - 2 * BorderThickness)};

  i32 lines = text.size() / charsPerLine;

  string drawText = text;

  for (i32 i = 0; i < lines; i++) {
    drawText.insert((i + 1) * charsPerLine, "\n");
  }
  DrawRectangleLinesEx(dest, BorderThickness, Color{30, 30, 30, 255});

  DrawText(TextFormat(drawText.c_str()), dest.x + fontsize, dest.y + fontsize,
           fontsize, BLACK);

  DrawTexturePro(texture, {0, 0, (f32)texture.width, (f32)texture.height},
                 {dest.x + (f32)BOX_WIDTH / 2, dest.y + BorderThickness,
                  (f32)(BOX_WIDTH / 2) - BorderThickness * 2,
                  dest.height - 2 * BorderThickness},
                 {0, 0}, 0, RAYWHITE);
}
