#ifndef _GAME_FUNCTION_H_
#define _GAME_FUNCTION_H_
#include <Arduino.h>
#include <DMD2.h>
#include "array.h"
#include "math_function.h"

#define UPDATETIME 500
#define WIDTH 1
#define HEIGHT 1


class Screen {
    unsigned long perviousTime = millis();
    SPIDMD mainBuffer; // DMD controls the entire display
    SPIDMD secondBuffer;
    MathFunctions function;



  public:
    Screen (byte width , byte height);
    byte width;
    byte height;

    void update(unsigned int elaspedTime);
    void render();
    void swapBuffers();
    void input();
    void mainLoop();
    

    void restart();



};


#endif //_GAME_FUNCTION_H_
