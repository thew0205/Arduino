#include "array.h"

Point::Point(byte x , byte y ): x(x), y(y) {}

bool Point::operator==(const Point & other)const {
  return x == other.x && y == other.y;
}

void Point::render(DMDFrame& screen) const {
  screen.setPixel(x, y);
}
