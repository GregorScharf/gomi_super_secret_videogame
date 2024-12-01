#include "../include/fonts.hpp"
#include <raylib.h>

Font Fonts::defaultFont;
Font Fonts::Carlito;

void Fonts::LoadFonts() {
  defaultFont = GetFontDefault();
  Carlito = LoadFont("/usr/share/fonts/truetype/crosextra/Carlito-Regular.ttf");
  GenTextureMipmaps(&defaultFont.texture);
  GenTextureMipmaps(&Carlito.texture);
  SetTextureFilter(defaultFont.texture, TEXTURE_FILTER_BILINEAR);
  SetTextureFilter(Carlito.texture, TEXTURE_FILTER_BILINEAR);
}

void Fonts::UnloadFonts() { UnloadFont(defaultFont); }
