#pragma once
#include "containers.hpp"
#include "types.hpp"


class Serializer {
private:
  //
public:
  static void ToToml(GameObjectContainer& g_obj_cont, IconContainer& icon_cont /*, &ShaderIcon shade_cont*/);
  static void FromToml(void /*GameObjectContainer& g_obj_cont, IconContainer& icon_cont */ /*, &ShaderIcon shade_cont*/);
};
