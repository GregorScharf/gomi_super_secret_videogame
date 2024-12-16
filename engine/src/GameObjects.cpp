#include "../include/GameObjects.hpp"
#include "utils.hpp"
#include <raylib.h>

GameObject::GameObject(Vector2 pos, Texture *textureRef, string &textPath,
                       u8 Layer) {
  this->texture = textureRef;
  this->matrix.x = pos.x;
  this->matrix.y = pos.y;
  this->matrix.width = textureRef->width;
  this->matrix.height = textureRef->height;

  this->rotation = 0;
  this->scale = {0, 0};
  // this->collider.reset();
  this->texture_path = textPath;
  this->UID = UIDGenerator::GetNewUid();
  this->layer_id = Layer;
  this->type = OBJECT;
  this->shader = nullptr;
  this->rts[0] = LoadRenderTexture(texture->width, texture->height);
  this->rts[1] = LoadRenderTexture(texture->width, texture->height);
}

void GameObject::clearShader() {
  shader_path.clear();
  shader = nullptr;
}

void GameObject::setShader(string &path, ShaderObject *shaderRef) {
  shader_path = path;
  shader = shaderRef;
}

void GameObject::draw(Camera2D *cam) {
  /* if (shader) {
     BeginShaderMode(*shader->get());
     DrawTexturePro(*texture, {0, 0, (f32)texture->width, (f32)texture->height},
                    matrix, {matrix.width / 2, matrix.height / 2}, rotation,
                    RAYWHITE);
     EndShaderMode();
   } else {
     DrawTexturePro(*texture, {0, 0, (f32)texture->width, (f32)texture->height},
                    matrix, {matrix.width / 2, matrix.height / 2}, rotation,
                    RAYWHITE);
   }
 */
  EndMode2D();
  if (shaders.size() > 0 && shaders[0]) {
    BeginTextureMode(rts[0]);
    BeginShaderMode(*shaders[0]->get());
    Rectangle source = {0, 0, (float)texture->width, -(float)texture->height};
    Rectangle dest = {0, 0, (float)texture->width, (float)texture->height};
    DrawTexturePro(*texture, source, dest, {0, 0}, 0.0f, WHITE);

    EndShaderMode();
    EndTextureMode();
  } else {
    // case for no shaders
    BeginMode2D(*cam);
    DrawTexturePro(*texture, {0, 0, (f32)texture->width, (f32)texture->height},
                   matrix, {matrix.width / 2, matrix.height / 2}, rotation,
                   RAYWHITE);
    return;
  }

  u64 i = 1;
  for (i = 1; i < shaders.size() && shaders[i]; i++) {
    BeginTextureMode(rts[extractBits(i, 0, 1)]);
    BeginShaderMode(*shaders[i]->get());
    DrawTexture(rts[!extractBits(i, 0, 1)].texture, 0, 0, WHITE);
    EndShaderMode();
    EndTextureMode();
  }

  Rectangle source = {0, 0, (f32)texture->width, (f32)texture->height};

  if (!extractBits(i, 0, 1)) {
    source.height -= 2 * source.height;
  }
  BeginMode2D(*cam);
  DrawTexturePro(rts[!extractBits(i, 0, 1)].texture, source, matrix,
                 {matrix.width / 2, matrix.height / 2}, rotation, RAYWHITE);
}
