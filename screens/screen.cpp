
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include "screen.h"




void  Screen::update(unsigned int elaspedTime) {

}


Screen::Screen (byte newWidth , byte neWHeight):mainBuffer{newWidth, neWHeight} , secondBuffer(newWidth, neWHeight),function{secondBuffer}  {
  
  Serial.begin(9600);
  secondBuffer.clearScreen();
  mainBuffer.setBrightness(255);
  mainBuffer.selectFont(SystemFont5x7);
  mainBuffer.begin();
  secondBuffer.selectFont(SystemFont5x7);
  width = mainBuffer.width;
  height = mainBuffer.height;
  Serial.println("game started");

}

void Screen::render() {
  function.render(secondBuffer);
  //  secondBuffer.drawBox(0, 0, width - 1 , height - 1);
}

void Screen::restart() {

}

void Screen::input() {
  if (Serial.available()) {
    byte direction = Serial.read();
    if ( direction == 'w' || direction == 'W') {
      Serial.println("w");
    }
    else if ( direction == 'a' || direction == 'A') {
      Serial.println("a");
    }

    else if ( direction == 's' || direction == 'S') {
      Serial.println("s");
    }

    else if ( direction == 'd' || direction == 'D') {
      Serial.println("d");
    }
    else if ( direction == 'p' || direction == 'P') {
      Serial.println("p");
    }
    else if ( direction == 'b' || direction == 'B' ) {
      Serial.println("b");
    }
  }
}


void Screen::mainLoop() {
  while (true) {
    input();
    unsigned int elaspedTime = millis() - perviousTime;
    if (elaspedTime > UPDATETIME) {
      update(elaspedTime);
      perviousTime = millis();
    }
    render();
    swapBuffers();
  }
}


void Screen::swapBuffers() {
  mainBuffer.swapBuffers(secondBuffer);
}
