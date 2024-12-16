#include "ShaderObjects.hpp"
#include "ErrorMessages.hpp"
#include "types.hpp"
#include <raylib.h>
#include <string>

ShaderObject::ShaderObject(string path) {
  shader = LoadShader(0, path.c_str());
  if (!IsShaderReady(shader)) {
    delete this;
  }

  ifstream file(path);
  if (!file.is_open()) {
    string ermsg = "couldn't open file: {" + path + "} for uniform indexing";
    ErrorMessages::add_new(SHADER_FAILED_TO_COMPILE, ermsg);
  }
  string line, tmp;
  while (std::getline(file, line)) {
    if (line.find("uniform")) {
      tmp = line.substr(line.find_last_of(' ') + 1);
      uniforms.emplace(tmp, GetShaderLocation(shader, tmp.c_str()));
    }
  }
  this->path = path;
}
Shader *ShaderObject::get() { return &this->shader; }

bool ShaderObject::check() { return IsShaderReady(shader); }

ShaderObject::~ShaderObject() { UnloadShader(shader); }
