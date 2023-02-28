#include "math_function.h"
#include <alloca.h>

MathFunctions::MathFunctions( DMDFrame& screen): boundaryWidth(screen.width), boundaryHeight(screen.height) {
  points = (Point*) malloc(screen.width * sizeof(Point));
  lenght = screen.width;
  for (size_t i = 0; i < lenght; i++) {
    points[i].x = -lenght / 2 -  i;
  }
  setPoints();
}
void MathFunctions::update(unsigned int elaspedTime) {

}
void MathFunctions::render( DMDFrame& screen)const {
  setPoints();
  screen.drawLine(screen.width / 2, 0, screen.width / 2, screen.height );
  screen.drawLine(0, screen.height / 2, screen.width , screen.height / 2 );
  for (size_t i = 0; i < lenght; i++) {
    points[i].render(screen);
  }
}
bool first = false;
void MathFunctions::setPoints() {

  for (size_t i = 0; i < lenght; i++) {
    float x = (points[i].x * 2 * M_PI / (boundaryWidth - 1)) - M_PI;
    points[i].y = sin(x) * 15;
    if (!first) {
      Serial.print("x :");
      Serial.print(points[i].x);
      Serial.print(" y :");
      Serial.println(points[i].y);
    }

    points[i] = graphPoint(points[i]);
    if (!first) {
      Serial.print("x :");
      Serial.print(points[i].x);
      Serial.print(" y :");
      Serial.println(points[i].y);
    }
  }
  first = true;
}
Point MathFunctions::graphPoint(const Point & point)const {
  Point ret ;
  if (!first) {
    Serial.print("x :");
    Serial.print(point.x);
    Serial.print(" y :");
    Serial.println(point.y);
  }
  ret.x = ( (2 * point.x * boundaryWidth) - (4 * point.x) + (boundaryWidth * boundaryWidth) - (4 * boundaryWidth) + 4) / (2 * boundaryWidth - 4);
  ret.y = ( (2 * point.y * boundaryHeight) - (4 * point.y) + (boundaryHeight * boundaryHeight) - (4 * boundaryHeight) + 4) / (2 * boundaryHeight - 4);
  if (!first) {
    Serial.print("x :");
    Serial.print(ret.x);
    Serial.print(" y :");
    Serial.println(ret.y);
  } return ret;
}
