#include "../include/GameObjects.hpp"
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
  this->type = OBJECT;
  this->shader = nullptr;
}

void GameObject::clearShader() {
  shader_path.clear();
  shader = nullptr;
}

void GameObject::setShader(string &path, Shader *shaderRef) {
  shader_path = path;
  shader = shaderRef;
}

void GameObject::draw() {
  if (shader) {
    BeginShaderMode(*shader);
    DrawTexturePro(*texture, {0, 0, (f32)texture->width, (f32)texture->height},
                   matrix, {(f32)texture->width / 2, (f32)texture->height / 2},
                   0, RAYWHITE);
    EndShaderMode();
  }
  else{
    DrawTexturePro(*texture, {0, 0, (f32)texture->width, (f32)texture->height},
                   matrix, {(f32)texture->width / 2, (f32)texture->height / 2},
                   0, RAYWHITE);
 
  }
}
