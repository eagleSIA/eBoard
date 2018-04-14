///@file neo_animation.cpp
///@brief a simple neo-animation example


#define IGNORE_SIZE
#define EBOARD_USE_UTILITY 0x0
#define EBOARD_DEBUG_MODE 0x0
#define EBOARD_CHECK_PINS 0x0
#define EBOARD_CHECK_PINS_PWM 0x0
#define EBOARD_NANO 0x1
#define EBOARD_NEO 0x1
#include <eBoard.h>
#define PIXELS_COUNT 5
#define RED    240
#define GREEN  120
#define BLUE     0
///@brief the NeoPixel-object we use
NeoPixel pixels = NeoPixel(PIXELS_COUNT);

/**
 * @brief this will perform a single shift operation!
 * @param pixBuf the pixelBuffer [reference]
 */
void shiftPx(uint8_t &pixBuf)
{
  for(uint8_t i = 1; i < (PIXELS_COUNT+1); i++)
    pixels.setPixelColor(i-1,(bitRead(pixBuf,i))?(NeoPixel::Color((RED/((PIXELS_COUNT+1)-i)),(GREEN/((PIXELS_COUNT+1)-i)),(BLUE/((PIXELS_COUNT+1)-i)))):(0));
  //lock communication here
  pixels.show();
  //unlock communication here
  pixBuf <<= 1;
  //if inverted: pixBuf >>= 1
}

/**
    @image html out.gif

    @note you can copy paste this code into your ARDUINO IDE - keep in mind to change the path!

    Compiled Size for ARUDINO NANO:  2,870 bytes \n
 */
int main()
{
  uint8_t pixBuf, j;
  pixels.begin();
  pixels.setBrightness(50);
  for(;;) {
    pixBuf = 0x3;
    //if inverted: pixBuf = 192
    for(j = 0; j < 7; j++) {
      shiftPx(pixBuf);
      delay(120 + 4*j); // you can do anything in this time!
    }
  }
  return 0;
}
