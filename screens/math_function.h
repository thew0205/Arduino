#pragma once
#include <Arduino.h>
#include <DMD2.h>
#include "array.h"

enum class Functions {
  sin,
  cos,
  tan,
  exp
};
class MathFunctions {
    byte boundaryWidth;
    byte boundaryHeight;
    Point* points;
    Functions function {Functions::sin};
    size_t lenght;

  public :
    MathFunctions( DMDFrame& screen);

    void update(unsigned int elaspedTime);
    void render( DMDFrame& screen)const;
    void  setPoints();

    Point graphPoint(const Point & point)const;
};
