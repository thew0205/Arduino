#pragma once
#include <Arduino.h>
#include <DMD2.h>
class Point {
  public:
    byte x ;
    byte y;
    Point (byte x = 0, byte y = 0);
    bool operator==(const Point & point)const ;
    void render(DMDFrame& screen)const;
};

//#pragma once
//template<typename T, size_t n>
//class Array {
//    T elements[n];
//    size_t _lenght{0};
//  public:
//    Array();
//    Array(T * newElements, size_t elementSize): _lenght(elementSize) {
//      for (size_t i ; i < lenght; i++) {
//        elements[i] = newElements[i];
//      }
//    }
//    T& operator[](size_t i) const {
//      return  elements[i];
//    }
//
//    constexpr size_t size() const {
//      return n;
//    }
//    constexpr size_t lenght() const {
//      return _lenght;
//    }
//
//
//    void add(T element) {
//      if ( _lenght + 1 < n) {
//        elements[_lenght] = element;
//        _lenght++;
//      }
//    }
//
//};
