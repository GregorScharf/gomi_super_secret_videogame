#pragma once

#include "Colliders.hpp"
#include "ShaderObjects.hpp"
#include "list.hpp"
#include "selectable.hpp"
#include "types.hpp"
#include "uids.hpp"
#include <boost/optional.hpp>
#include <boost/optional/optional.hpp>
#include <raylib.h>
#include <unordered_map>

class GameObject : public Selectable {
public:
  Rectangle matrix;
  Vector2 scale;
  f32 rotation;
  Collider collider; // ! deprecated
  unordered_map<string, Collider *> colliders;
  vector<ShaderObject *> shaders;
  vector<string> scripts; // name of the script as a path
  string texture_path, shader_path;
  Texture *texture;
  ShaderObject *shader;
  u64 UID;
  u8 layer_id;
  node<GameObject *> *ObjectListKey;
  RenderTexture2D rts[2];

  GameObject(Vector2 pos, Texture *textureRef, string &textPath, u8 Layer);

  void setShader(string &path, ShaderObject *shaderRef);
  void clearShader();

  void draw(Camera2D *cam);
};

/*
 *  just some concepting about scripting and object attributes for now
 *
 *  scripts:
 *    - either using c++ with some inheritance shenanigans or embedding lua (im
 *      personally for doing c++ since i don't have experience with lua or
 *      embedding it)
 *    - for c++ we can have the script be attached by a path reference in the
 *      GameObject it is applied to and then in the script file we have a
 *      generic class that inherits from GameObject class called script
 *      with virtual methods like start() and update()
 *    - addressing shaders and colliders via that kind of c++ script will be
 *      a bit cumbersome but since we know what attributes the object will
 *      have at scene load time we can use a "perfect" hashmap to search for
 *      attributes
 *  required changes to GameObject class:
 *      map for colliders
 *      map for shaders
 *      vector for scripts that contains paths to the actual scripts
 *        (every object gets a uid which we can use to assign said object to its
 *        script)
 *
 *
 *
 *
 * */
