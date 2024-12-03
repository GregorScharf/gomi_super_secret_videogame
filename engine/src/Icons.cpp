#include "../include/Icons.hpp"
#include "fonts.hpp"
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
<<<<<<< HEAD
  BorderThickness = 3;
  // this is kind of a hack but ehhh
  i32 charsPerLine = scale.width / fontsize;
  charsPerLine--;
=======
  border_thickness = 3;
}

void TextureIcon::make_ref(node<TextureIcon *> *reference) { ref = reference; }

void TextureIcon::draw(Rectangle *barFrame) {

  // this is kind of a hack but ehhh
  i32 charsPerLine = scale.width / fontsize;
  charsPerLine--;
  Rectangle dest = {scale.x, scale.y + (barFrame->height * 2),
                    f32((BOX_WIDTH)-border_thickness),
                    f32((scale.height) - 2 * border_thickness)};

>>>>>>> a304625 (serializer to toml initial file output)
  i32 lines = text.size() / charsPerLine;

  string drawText = text;

  for (i32 i = 0; i < lines; i++) {
    drawText.insert((i + 1) * charsPerLine, "\n");
  }
<<<<<<< HEAD
  text = drawText;
}

void TextureIcon::make_ref(node<TextureIcon *> *reference) { ref = reference; }

void TextureIcon::draw(Rectangle *barFrame) {
  Rectangle dest = {scale.x, scale.y + barFrame->height,
                    f32((BOX_WIDTH)-BorderThickness),
                    f32((scale.height) - 2 * BorderThickness)};

  DrawRectangleLinesEx(dest, BorderThickness, Color{30, 30, 30, 255});
=======
  DrawRectangleLinesEx(dest, border_thickness, Color{30, 30, 30, 255});
>>>>>>> a304625 (serializer to toml initial file output)

  DrawTextEx(Fonts::Carlito, text.c_str(), {dest.x + 10, dest.y + 3}, 18, 1,
             BLACK);

  DrawTexturePro(texture, {0, 0, (f32)texture.width, (f32)texture.height},
                 {dest.x + (f32)BOX_WIDTH / 2, dest.y + border_thickness,
                  (f32)(BOX_WIDTH / 2) - border_thickness * 2,
                  dest.height - 2 * border_thickness},
                 {0, 0}, 0, RAYWHITE);
}
