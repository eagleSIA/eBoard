///@file lcd_debug.cpp
///@brief a lcd debug example

///@brief we need the I2C functionality
#define EBOARD_I2C 0x1
///@brief we want to use the LCD
#define EBOARD_LCD 0x1
#include "/eagleoutice/projects/github/eBoard/eBoard.h"
/// @brief the board object
SoccerBoard board;
/// @brief the lcd object
LCD lcd(board);
/// @brief the dBoard object
DynamixelBoard dBoard(board);
/// @brief left servo
/// @note untested!
AX12Servo links(dBoard,1);
/// @brief right servo
/// @note untested
AX12Servo rechts(dBoard,2);
/**
  @note you can copy paste this code into your ARDUINO IDE - keep in mind to change the path!

  Compiled Size for ARUDINO UNO:   8,526 bytes => 3.0: 6,734 bytes \n
  Compiled Size for ARUDINO MEGA: 10,058 bytes => 3.0: 8,170 bytes
*/
int main()
{
    links.storePosition(40);
    rechts.storePosition(200);
    //lcd.changeID(0x3C);
    board.sleep(1);
    lcd.clear();
    lcd.print(links.getPosition());
    lcd.print(1,0,rechts.getPosition());
    dBoard.action();
    board.sleep(1);
    lcd.changeBackground(true);
    lcd.print(2,0,links.getPosition());
    lcd.print(3,0,rechts.getPosition());
    return 0;
  }
