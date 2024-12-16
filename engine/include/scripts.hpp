#pragma once
#include "GameObjects.hpp"
#include "types.hpp"

class script {
  GameObject *gameObject;
  string name;

  script(GameObject *, string script_name);

  virtual void update();
  virtual void start();

  ~script();
};

void generate_new_script(string name);
