#pragma once

#include "types.hpp"
#include <raylib.h>

enum ErrorCodes {
  SHADER_FAILED_TO_COMPILE = 0,
  TEXTURE_FAILED_TO_LOAD = 1,
  DYNAMIC_TYPE_CONVERSION_FAILED = 2,
};

class ErrorMessage {
public:
  ErrorCodes ErrorCode;
  string errorMessage;
  void draw(i32 index);
};

class ErrorMessages {
  static vector<ErrorMessage *> messages;

public:
  static i32 add_new(ErrorCodes code, string &message);

  static void remove(i32 i);

  static void draw();
};
