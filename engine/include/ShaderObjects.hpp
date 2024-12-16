#pragma once
#include "types.hpp"
#include <raylib.h>

class ShaderObject {
  Shader shader;
  unordered_map<string, i32> uniforms;

public:
  string path;
  Shader *get();
  ShaderObject(string path);
  bool check();
  ~ShaderObject();
};
