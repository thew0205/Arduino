#include "DMD2.h"
/*
 DMDFrameDoubleBuffer class implementation.

 Non-hardware specific functions for updating the framebuffer

 Copyright (C) 2014 Freetronics, Inc. (info <at> freetronics <dot> com)

 Updated by Angus Gratton, based on DMD by Marc Alexander.

---

 This program is free software: you can redistribute it and/or modify it under
the terms of the version 3 GNU General Public License as published by the Free
Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.
*/

DMDFrameDoubleBuffer::DMDFrameDoubleBuffer(byte pixelsWide, byte pixelsHigh)
    : width(pixelsWide), height(pixelsHigh), font(0) {
  row_width_bytes =
      (pixelsWide + 7) / 8; // on full panels pixelsWide is a multiple of 8, but
                            // for sub-regions may not be
  height_in_panels = (pixelsHigh + PANEL_HEIGHT - 1) / PANEL_HEIGHT;
  first_bitmap = (uint8_t *)malloc(bitmap_bytes());
  second_bitmap = (uint8_t *)malloc(bitmap_bytes());
  memset((void *)first_bitmap, 0xFF, bitmap_bytes());
  memset((void *)sencond_bitmap, 0xFF, bitmap_bytes());
}

DMDFrameDoubleBuffer::DMDFrameDoubleBuffer(const DMDFrameDoubleBuffer &source)
    : width(source.width), height(source.height),
      row_width_bytes(source.row_width_bytes),
      height_in_panels(source.height_in_panels), font(source.font) {
  first_bitmap = (uint8_t *)malloc(bitmap_bytes());
  second_bitmap = (uint8_t *)malloc(bitmap_bytes());
  memset((void *)first_bitmap, 0xFF, bitmap_bytes());
  memset((void *)sencond_bitmap, 0xFF, bitmap_bytes());
}

DMDFrameDoubleBuffer::~DMDFrameDoubleBuffer() {
  free((void *)first_bitmap);
  free((void *)secondd_bitmap);
}

void DMDFrameDoubleBuffer::swapBuffers() {
#ifdef __AVR__
  // AVR can't write pointers atomically, so need to disable interrupts
  char oldSREG = SREG;
  cli();
#endif
  volatile uint8_t *temp = second_bitmap;
  second_bitmap = first_bitmap;
  first_bitmap = temp;
#ifdef __AVR__
  SREG = oldSREG;
#endif
}

void DMDFrameDoubleBuffer::swapBuffers() {
#ifdef __AVR__
  // AVR can't write pointers atomically, so need to disable interrupts
  char oldSREG = SREG;
  cli();
#endif
  volatile uint8_t *temp = first_bitmap;
  first_bitmap = second_bitmap;
  second_bitmap = temp;
#ifdef __AVR__
  SREG = oldSREG;
#endif
}

// Set a single LED on or off. Remember that the pixel array is inverted (bit
// set = LED off)
void DMDFrameDoubleBuffer::setPixel(unsigned int x, unsigned int y,
                                    DMDGraphicsMode mode) {
  if (x >= width || y >= height)
    return;

  int byte_idx = pixelToBitmapIndex(x, y);
  uint8_t bit = pixelToBitmask(x);
  switch (mode) {
  case GRAPHICS_ON:
    second_bitmap[byte_idx] &= ~bit; // and with the inverse of the bit - so
    break;
  case GRAPHICS_OFF:
    second_bitmap[byte_idx] |= bit; // set bit (which turns it off)
    break;
  case GRAPHICS_OR:
    second_bitmap[byte_idx] = ~(~second_bitmap[byte_idx] | bit);
    break;
  case GRAPHICS_NOR:
    second_bitmap[byte_idx] = (~second_bitmap[byte_idx] | bit);
    break;
  case GRAPHICS_XOR:
    second_bitmap[byte_idx] ^= bit;
    break;
  case GRAPHICS_INVERSE:
  case GRAPHICS_NOOP:
    break;
  }
}

bool DMDFrameDoubleBuffer::getPixel(unsigned int x, unsigned int y) {
  if (x >= width || y >= height)
    return false;
  int byte_idx = pixelToBitmapIndex(x, y);
  uint8_t bit = pixelToBitmask(x);
  bool res = !(first_bitmap[byte_idx] & bit);
  return res;
}

void DMDFrameDoubleBuffer::debugPixelLine(
    unsigned int y,
    char *
        buf) { // buf must be large enough (2x pixels+EOL+nul), or we'll overrun
  char *currentPixel = buf;
  for (int x = 0; x < width; x++) {
    bool set = getPixel(x, y);
    if (set) {
      *currentPixel = '[';
      currentPixel++;
      *currentPixel = ']';
    } else {
      *currentPixel = '_';
      currentPixel++;
      *currentPixel = '_';
    }
    currentPixel++;
  }
  *currentPixel = '\n';
  currentPixel++;
  *currentPixel = 0; // nul terminator
}

// void DMDFrameDoubleBuffer::movePixels(unsigned int from_x, unsigned int
// from_y,
//                                       unsigned int to_x, unsigned int to_y,
//                                       unsigned int width, unsigned int
//                                       height) {
//   // NB: This implementation is actually a copy-erase so
//   // it uses more RAM than a real move implementation would
//   // do (however bypasses issues around overlapping regions.)

//   if (from_x >= this->width || from_y >= this->height || to_x >= this->width
//   ||
//       to_y >= this->height)
//     return;

//   DMDFrameDoubleBuffer to_move = this->subFrame(from_x, from_y, width,
//   height); this->drawFilledBox(from_x, from_y, from_x + width - 1, from_y +
//   height - 1,
//                       GRAPHICS_OFF);
//   this->copyFrame(to_move, to_x, to_y);
// }

// Set the entire screen
void DMDFrameDoubleBuffer::fillScreen(bool on) {
  memset((void *)second_bitmap, on ? 0 : 0xFF, bitmap_bytes());
}

void DMDFrameDoubleBuffer::drawLine(int x1, int y1, int x2, int y2,
                                    DMDGraphicsMode mode) {
  int dy = y2 - y1;
  int dx = x2 - x1;
  int stepx, stepy;

  if (dy < 0) {
    dy = -dy;
    stepy = -1;
  } else {
    stepy = 1;
  }
  if (dx < 0) {
    dx = -dx;
    stepx = -1;
  } else {
    stepx = 1;
  }
  dy = dy * 2;
  dx = dx * 2;

  setPixel(x1, y1, mode);
  if (dx > dy) {
    int fraction = dy - (dx / 2); // same as 2*dy - dx
    while (x1 != x2) {
      if (fraction >= 0) {
        y1 += stepy;
        fraction -= dx; // same as fraction -= 2*dx
      }
      x1 += stepx;
      fraction += dy; // same as fraction -= 2*dy
      setPixel(x1, y1, mode);
    }
  } else {
    int fraction = dx - (dy / 2);
    while (y1 != y2) {
      if (fraction >= 0) {
        x1 += stepx;
        fraction -= dy;
      }
      y1 += stepy;
      fraction += dx;
      setPixel(x1, y1, mode);
    }
  }
}

void DMDFrameDoubleBuffer::drawCircle(unsigned int xCenter,
                                      unsigned int yCenter, int radius,
                                      DMDGraphicsMode mode) {
  // Bresenham's circle drawing algorithm
  int x = -radius;
  int y = 0;
  int error = 2 - 2 * radius;
  while (x < 0) {
    setPixel(xCenter - x, yCenter + y, mode);
    setPixel(xCenter - y, yCenter - x, mode);
    setPixel(xCenter + x, yCenter - y, mode);
    setPixel(xCenter + y, yCenter + x, mode);
    radius = error;
    if (radius <= y)
      error += ++y * 2 + 1;
    if (radius > x || error > y)
      error += ++x * 2 + 1;
  }
}

void DMDFrameDoubleBuffer::drawBox(unsigned int x1, unsigned int y1,
                                   unsigned int x2, unsigned int y2,
                                   DMDGraphicsMode mode) {
  drawLine(x1, y1, x2, y1, mode);
  drawLine(x2, y1, x2, y2, mode);
  drawLine(x2, y2, x1, y2, mode);
  drawLine(x1, y2, x1, y1, mode);
}

void DMDFrameDoubleBuffer::drawFilledBox(unsigned int x1, unsigned int y1,
                                         unsigned int x2, unsigned int y2,
                                         DMDGraphicsMode mode) {
  for (unsigned int b = x1; b <= x2; b++) {
    drawLine(b, y1, b, y2, mode);
  }
}

// void DMDFrameDoubleBuffer::scrollY(int scrollBy) {
//   if (abs(scrollBy) >= height) { // scrolling over the whole display
//     // scrolling will erase everything
//     drawFilledBox(0, 0, width - 1, height - 1, GRAPHICS_OFF);
//   } else if (scrollBy < 0) { // Scroll up
//     movePixels(0, -scrollBy, 0, 0, width, height + scrollBy);
//     drawFilledBox(0, height + scrollBy, width, height, GRAPHICS_OFF);
//   } else if (scrollBy > 0) { // Scroll down
//     movePixels(0, 0, 0, scrollBy, width, height - scrollBy);
//     drawFilledBox(0, 0, width, scrollBy, GRAPHICS_OFF);
//   }
// }

// void DMDFrameDoubleBuffer::scrollX(int scrollBy) {
//   if (abs(scrollBy) >= width) { // scrolling over the whole display!
//     // scrolling will erase everything
//     drawFilledBox(0, 0, width - 1, height - 1, GRAPHICS_OFF);
//   } else if (scrollBy < 0) { // Scroll left
//     movePixels(-scrollBy, 0, 0, 0, width + scrollBy, height);
//     drawFilledBox(width + scrollBy, 0, width, height, GRAPHICS_OFF);
//   } else { // Scroll right
//     movePixels(0, 0, scrollBy, 0, width - scrollBy, height);
//     drawFilledBox(0, 0, scrollBy, height, GRAPHICS_OFF);
//   }
// }

// void DMDFrameDoubleBuffer::marqueeScrollX(int scrollBy) {
//   // Scrolling is basically the same as normal scrolling, but we save/restore
//   // the overlapping area in between to create the marquee effect
//   scrollBy = scrollBy % width;

//   if (scrollBy < 0) { // Scroll left
//     DMDFrameDoubleBuffer frame =
//         subFrame(0, 0, -scrollBy, height);                    // save
//         leftmost
//     movePixels(-scrollBy, 0, 0, 0, width + scrollBy, height); // move
//     copyFrame(frame, width + scrollBy, 0); // drop back at right edge
//   } else {                                 // Scroll right
//     DMDFrameDoubleBuffer frame =
//         subFrame(width - scrollBy, 0, scrollBy, height);     // save
//         rightmost
//     movePixels(0, 0, scrollBy, 0, width - scrollBy, height); // move
//     copyFrame(frame, 0, 0); // drop back at left edge
//   }
// }

// void DMDFrameDoubleBuffer::marqueeScrollY(int scrollBy) {
//   scrollBy = scrollBy % height;

//   if (scrollBy < 0) {                 // Scroll up
//                                       // DMDFrameDoubleBuffer frame =
//     subFrame(0, 0, width, -scrollBy); // save topmost
//     movePixels(0, -scrollBy, 0, 0, width, height + scrollBy); // move
//     copyFrame(frame, 0, height + scrollBy); // drop back at bottom edge
//   } else {                                  // Scroll down
//     DMDFrameDoubleBuffer frame =
//         subFrame(0, height - scrollBy, width, scrollBy);     // save
//         bottommost
//     movePixels(0, 0, 0, scrollBy, width, height - scrollBy); // move
//     copyFrame(frame, 0, 0); // drop back at top edge
//   }
// }

// void DMDFrameDoubleBuffer::subFrame(unsigned int left, unsigned int top,
//                                     unsigned int width, unsigned int height)
//                                     {
//   // DMDFrameDoubleBuffer result(width, height);

//   if ((left % 8) == 0 && (width % 8) == 0) {
//     // Copying from/to byte boundaries, can do simple/efficient copies
//     for (unsigned int to_y = 0; to_y < height; to_y++) {
//       unsigned int from_y = top + to_y;
//       unsigned int from_end = pixelToBitmapIndex(left + width, from_y);
//       unsigned int to_byte = pixelToBitmapIndex(0, to_y);
//       for (unsigned int from_byte = pixelToBitmapIndex(left, from_y);
//            from_byte < from_end; from_byte++) {
//         second_bitmap[to_byte++] = first_bitmap[from_byte];
//       }
//     }
//   } else {
//     // Copying not from a byte boundary. Slow pixel-by-pixel for now.
//     for (unsigned int to_y = 0; to_y < height; to_y++) {
//       for (unsigned int to_x = 0; to_x < width; to_x++) {
//         bool val = this->getPixel(to_x + left, to_y + top);
//         setPixel(to_x, to_y, val ? GRAPHICS_ON : GRAPHICS_OFF);
//       }
//     }
//   }

//   // return result;
// }

// void DMDFrameDoubleBuffer::copyFrame(unsigned int left, unsigned int top) {
//   if ((left % 8) == 0 && (width % 8) == 0) {
//     // Copying rows on byte boundaries, can do simple/efficient copies
//     unsigned int to_bottom = top + height;
//     if (to_bottom > this->height)
//       to_bottom = this->height;
//     unsigned int to_right = left + width;
//     if (to_right > this->width)
//       to_right = this->width;
//     unsigned int _y = 0;
//     for (unsigned int to_y = top; to_y < to_bottom; to_y++) {
//       unsigned int to_end = pixelToBitmapIndex(to_right, to_y);
//       unsigned int _byte = pixelToBitmapIndex(0, _y);
//       for (unsigned int to_byte = pixelToBitmapIndex(left, to_y);
//            to_byte < to_end; to_byte++) {
//         this->second_bitmap[to_byte] = first_bitmap[_byte++];
//       }
//       _y++;
//     }
//   } else {
//     // Copying not to a byte boundary. Slow pixel-by-pixel for now.
//     for (unsigned int _y = 0; _y < height; _y++) {
//       for (unsigned int _x = 0; _x < width; _x++) {
//         bool val = getPixel(_x, _y);
//         this->setPixel(_x + left, _y + top, val ? GRAPHICS_ON :
//         GRAPHICS_OFF);
//       }
//     }
//   }
// }

/* Lookup table for DMD pixel locations, marginally faster than bitshifting */
const PROGMEM uint8_t DMD_Pixel_Lut[] = {
    0x80, // 0, bit 7
    0x40, // 1, bit 6
    0x20, // 2. bit 5
    0x10, // 3, bit 4
    0x08, // 4, bit 3
    0x04, // 5, bit 2
    0x02, // 6, bit 1
    0x01  // 7, bit 0
};
