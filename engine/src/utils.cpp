#include "../include/utils.hpp"
#include <cstring>
#include <raylib.h>

bool endswith(string s, const char *end) {
  if (strlen(end) > s.size()) {
    return false;
  }
  string thisend = s.substr(s.size() - strlen(end), s.size() + 1);
  string str = end;
  return strcmp(thisend.c_str(), str.c_str()) == 0;
}

Rectangle RecWorldToScreen(Rectangle *rec, Camera2D *camera) {
  Vector2 tmp = GetWorldToScreen2D({rec->x, rec->y}, *camera);
  return {tmp.x, tmp.y, rec->width * camera->zoom, rec->height * camera->zoom};
}
Rectangle RecScreenToWorld(Rectangle *rec, Camera2D *camera) {
  Vector2 tmp = GetScreenToWorld2D({rec->x, rec->y}, *camera);
  return {tmp.x, tmp.y, rec->width * camera->zoom, rec->height * camera->zoom};
}

bool is_int(string &s) {
  bool minus = false;
  for (char c : s) {
    if (c < 48 || c > 57) {
      if (c != '-' || minus) {
        return false;
      } else {
        minus = true;
      }
    }
  }
  return true;
}

bool is_uint(string &s) {
  for (char c : s) {
    if (c < 48 || c > 57) {
      return false;
    }
  }
  return true;
}

bool is_float(string &s) {
  bool dot = false;

  if(s.size() == 0) {
    return false;
  }

  for (char c : s) {
    if (c < 48 || c > 57) {
      if (c != '.' || dot) {
        return false;
      } else {
        dot = true;
      }
    }
  }
  return true;
}
