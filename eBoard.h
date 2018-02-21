///EagleoutIce 2018
///IF YOU SEE THIS THIS IS THE UNPROCESSED FILE! GO TO 'SOURCE CODE' IN THE DOCS
/**
 * @file eBoard.h
 */

 #pragma GCC diagnostic push
 #pragma GCC diagnostic ignored "-Wall"
 #pragma GCC diagnostic ignored "-Wextra"

/**
 @mainpage eBoard 2.2b - shackle the Arduino!

 @note It was an explicit decision to pack everything needed in one headerfile - readability is granted by the doc
 @note This code was written for the Arduino UNO R3 used with the Smart Servo Shield and allows to copy-paste Code running on a qfixSoccerboard

 @warning This code comes with absolutely <b>no</b> warranty


 @pre This Header file was created to port Codes running on the qfix SoccerBoard [DynamixelBoard etc...] directly onto the Arduino UNO R3 [with Smart Servo Shield].
 \n To use it you'll have to replace all qfix-related header-files [*.h] with the following:
 @code
 #include <SPI.h>
 #include "/path/to/eBoard.h" //replace this :D
 @endcode

 If you wan't to use the I2C extensions you should have this two lines the beginning of your code:
 @code
 #define EBOARD_I2C 0x1
 #include <WIRE.h>
 @endcode

 While in development you shouldn't disable any macro...
 If you change to release mode, write (as a minimum) the following before all includings:
 @code
 #define EBOARD_DEBUG_MODE 0x0
 @endcode


 @section s1 Macros
 There are multiple macros you can manipulate the behaviour of this header [full list is here: @ref macro]:
 @note The constants will appear with their default values in codeSnippets -> be careful with assumptions ;)

 <b>General</b>

 - [IGNORE_SIZE]             : DEF: the size of this program will grow but the used variable-space will shrink...
 - #EBOARD_DEBUG_MODE        : 0x0: disable [DEBUG_MODE]
 - #EBOARD_DEBUG_SPEED       : if [DEBUG_MODE]: set Speed (9600...)
 - #EBOARD_CHECK_PINS        : 0x0: disable range-check for normal READ and WRITE
 - #EBOARD_CHECK_PINS_PWM    : 0x0: disable range-check for PWM-WRITE
 - #EBOARD_USE_SPI           : 0x0: disables internal SPI-handling
 - #EBOARD_USE_UTILITY       : 0x0: removes useless code-parts
 - #EBOARD_SPI_SERVO_MAX     : Sets the amount of the visible, connected AX-12
 - #EBOARD_I2C               : 0x1: enables I2C tools
 - #EBOARD_SHIFT_REGISTER    : 0x1: enables SHIFT_REGISTER
 - #EBOARD_BLUETOOTH         : 0x1: enables Bluetooth support
 - #EBOARD_PWM_SPE           : Sets the duty cycle for @ref su111
 - #EBOARD_CLAMP             : 0x0: disables clamp
 - #EBOARD_USE_RESET         : 0x0: disable software reset
 - #EBOARD_LCD               : 0x1: enable support for LCD display. Needs #EBOARD_I2C set to 0x1

 <b>Pins</b>
 - #PIN_BLUETOOTH_RX         : pinID(2|19) of RX-Pin   -- why? [@ref su3]
 - #PIN_BLUETOOTH_TX         : pinID(3|18) of TX-Pin   -- why? [@ref su3]
 - #PIN_MOTOR_DIR            : pinID(4) for MotorControl [DIR]
 - #PIN_MOTOR_SPE            : pinID(5) for MotorControl [SPE]
 - #PIN_SHIFT_CLK            : pinID(6) of shift-Clock
 - #PIN_SHIFT_DAT            : pinID(7) of shift-Data
 - #PIN_SHIFT_LAT            : pinID(8) of shift-Latch
 - #PIN_BLUETOOTH_STATE      : If == RX-Pin: not set. Else: Pin of HC-05 connection-state

 @section s2 Smart Servo Shield
 @image html /home/eagleoutice/Dokumente/proj/_sia/sss.jpeg
 @image latex /home/eagleoutice/Dokumente/proj/_sia/sss.jpeg
 This is the smart-servo shield this code was written for its connected by SPI with the UNO R3. In case of an emergency it is possible to hardcode a connection interface to drive the AX-12A Servo directly from the arduino... but this is very expensive :/
 @note to use the motors properly you <i>have</i> to connect the Board with a ~12V power supply!

 @section s4 Philosophy
 On small projects I prefer the single-file header! \n Your able to 'manage the includings' via the preprocessor constants

 @note There is no internal reset command on the Arduino. To 'create' a remote reset mechanism use the onBoard Reset-Pin!

 @subsection su111 Async task execution

 The Arduino is a single core processor. That means it isn't possible to do multiple tasks at once. \n
 To enable async task execution eBoard provides this mechanism (write this before including the eBoard header!). \n
 The execution cycle is #EBOARD_PWM_SPE seconds and the method will be invoked after the resend of the Motor-PWM value.
 @code
 #define REPT_TASK
 void rept_task(void){
   //do some stuff - non blocking!!!!
 }
 @endcode

 @warning Don't put any endless loop etc. in this method! The execution time <b>has</b> to be lower than #EBOARD_PWM_SPE seconds !

 @section s3 Tutorials

 - @ref i2cEx
 - @ref shiftEx
 - @ref blueEx
 - @ref lcdEx
 - @ref portTu
*/
/**
 @page page1 About
 @brief Something about the Author :D - me ;P
 @author Florian Sihler - EagleoutIce
 @copyright EagleoutIce 2018
 @version 2.2b
 @date 7.2.2018

 @section m1 Motivation
 This header was created to port SoccerBoard-Code to the Arduino UNO R3 [or MEGA R3]\n
 It was written in a funny amount of time (@ref p5) and documented by Doxygen 1.8.15. \n


 @section m2 General Information
 I am an 18-year old programmer and I am coding since i was a kid. \n
 @bug 🐉 Any Errors or Bugs? florian.sihler@web.de



  @image html /home/eagleoutice/Dokumente/proj/_sia/pp.jpeg
  @image latex /home/eagleoutice/Dokumente/proj/_sia/pp.jpeg


*/
/**
  @page stats Statistics
  @brief Cuz everyone loves them :O
    @warning it's easy to misinterpret this statistics!
     \n eBoard is taking care of many things and only occupying a minimum of space! Most things you would have to write by yourselve otherwise (which may resulted in an even higher amount of used space!)

    @note every test was run with an Arduino UNO R3 It is possible that the code size vary

    @section ss1 1 Occupied Space

    Because everyone loves statistics♥:

    @note Development Build:
    @code
    #include <Wire.h>
    #define EBOARD_I2C 0x1
    #define EBOARD_SHIFT_REGISTER 0x1
    #include <SoftwareSerial.h>
    #define EBOARD_BLUETOOTH 0x1
    #include <SPI.h>
    //[VER 2.0c]
    #define REPT_TASK
    void rept_task (void) {}
    #define EBOARD_LCD 0x1
    @endcode

    @note Release Build:
    @note removed I2C due to the hope that Bluetooth is enough ^^
    @code
    #define IGNORE_SIZE
    #define EBOARD_USE_UTILITY 0x0
    #define EBOARD_DEBUG_MODE 0x0
    #define EBOARD_CHECK_PINS 0x0
    #define EBOARD_CHECK_PINS_PWM 0x0
    #define EBOARD_SHIFT_REGISTER 0x1
    #include <SoftwareSerial.h>
    #define EBOARD_BLUETOOTH 0x1
    #include <SPI.h>
    //[VER 2.0c]
    #define EBOARD_LCD 0x1
    @endcode


    @subsection ssu1 1.1 Empty program

    @note Used:
    @code
    //[...]
    int main() {return 0;}
    @endcode

    Following results: \n
    <b> [Version: 1.2a] </b> \n
    [Dev]: 'Binäre Sketchgröße: 6.994 Bytes (von einem Maximum von 32.256 Bytes)' \n
    [Rel]: 'Binäre Sketchgröße: 3.264 Bytes (von einem Maximum von 32.256 Bytes)' \n
    \n
    <b> [Version: 2.0c] </b> \n
    [Dev]: 'Binäre Sketchgröße: 7.530 Bytes (von einem Maximum von 32.256 Bytes)' \n
    [Rel]: 'Binäre Sketchgröße: 3.770 Bytes (von einem Maximum von 32.256 Bytes)' \n

    @subsection ssu2 1.2 Output to an OLED-Display

    @note Used Code:
    @code
    #include <Wire.h>
    #define EBOARD_I2C 0x1
    #define EBOARD_LCD 0x1
    #include <SPI.h>
    #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"
    SoccerBoard board;
    LCD lcd(board);

    int main() {
        lcd.print("Hallo Welt"); //Actually there is no println! => shame
        lcd.print("Scheint die Sonne?");
        for(int i = 0; i < 2000; i++){
            lcd.print(i);
            board.msleep(100);
            lcd.clear();
            board.msleep(100);
        }
        return 0;
    }
    @endcode

    Following results: \n
    <b> [Version: 2.0c] </b> \n
    [SAM]: 'Binäre Sketchgröße: 7.716 Bytes (von einem Maximum von 32.256 Bytes)' \n

*/
/**
  @page p5 Changelog
  @brief A short overview about the developing process
  @section ver1 Version 1 - Olivander 🐁

  @note this changelog is maintained by EagleoutIce

  @subsection su1 Version 1.0e 🐪 - I ate the alpha-cookie :D [~130m]

   leaving the alpha-state :D [after 130 minutes :P]

  <b>Added</b>

   + Macros to enable full control over included content
   + Documantation
   + Todo list ._.

  <b>Removed</b>

   - logfile support

  @subsection su2 Version 1.1b 🐓 - Hello Slave [~70m]

    Added support for several external devices

 <b>Added</b>

    + Macros for devices
    + I²C support
    + S.C.H.I.E.L.D support
    + Shift-register support

  @subsection su3 Version 1.2e 🐧 - On your command, master [~100m]

    Added support for remote control

 <b>Changed</b>

    + Changed #PIN_BLUETOOTH_RX and #PIN_BLUETOOTH_TX to 2,3 for SoftwareSerial based on common problems
    + Rewritten ServoCds55
    + Tried to make code more compact :D
    + Optimized PWM support

  <b>Added</b>

    + Async Task execution
    + RB14Scan [No protocoll!]

  <b>Removed</b>

    + #EBOARD_CHECK_PINS doesn't checks full range anymore ... should be fixed

  @subsection su4 Version 1.3g 🐊 - Make this safe! [~30m]

  Optimized and added some safety and control features

  <b>Changed</b>

    + Clamped Motorpositions
    + Cleaned Code
    + Grouped Examples
    + Animated Logo & New Colors

  <b>Added</b>

    + Global Break function
    + Preprocessor support for ARDUINO MEGA 2560

  <b>Removed</b>

    + Control over #EBOARD_COPY_AND_PASTE

  @section ver2 Version 2 - Scofield 🐩

  @subsection su5 Version 2.0c 🐈 - Facing Interfaces [~130m]

    Added support for the OLED 128x64 Monochrome Display

    <b>Added</b>

    - LCD-Display support via I2C

    <b>Changed</b>

    - Cleaned Code

  @subsection su6 Version 2.1d 🐺 - \#Oversize [~60m]

  Included many Optimizations and fixes

  <b>Added</b>

    - New statistics
    - Pre flags
    - New tutorial stuff
    - Port-tutorial

  <b>Changed</b>

    - Cleaned Code (a lot ^^) [with 2.0]
    - Some tutorial declarations
    - Serial feature on MEGA R3 [No need for SoftwareSerial anymore :D]

  <b>Fixes</b>
    - Fixed bug in I2CInOut  (private access failure)
    - Fixed bug in AX12Servo (double clamp on AX12Servo::storePosition())
    - Fixed bug of clamp_overflow (no check for in_range and out_range in AX12Servo::setPosition())

    @subsection su7 Version 2.2b 🐏 - Optimize it

    Fixed many bugs

    <b>Added</b>

      - images for LCD
      - dancing_dragon as funny example (created while debugging)
      - lcd_debug as debug example

    <b>Fixes</b>
      - Fixed blocking bug on Hardware-calls (pre init)
      - Fixed LCD err send
      - Fixed several bugs/optimized ranges to avoid undefined behaviour
      - warranty misspell^^
*/
//i am a guard... leave me alone :D
#ifndef EBOARD_HEADER_GUARD
    #define EBOARD_HEADER_GUARD

    #ifdef DOC
        #define ARDUINO 200
        /**
         * @macro_def This will appear as 0x1 in the docs but the real default value is 0x0
         */
        #define EBOARD_I2C 0x1
        /**
         * @macro_def This will appear as 0x1 in the docs but the real default value is 0x0
         * This will enable the support for the OLED I²C 128x64 Monochrome display
         */
        #define EBOARD_LCD 0x1
         /**
          * @macro_def This will appear as 0x1 in the docs but the real default value is 0x0
          */
        #define EBOARD_SHIFT_REGISTER 0x1
        /**
         * @macro_def This will appear as 0x1 in the docs but the real default value is 0x0
         */
        #define EBOARD_BLUETOOTH 0x1
        /**
         * @macro_def This constant won't be defined by default :D
         */
        #define REPT_TASK
        /**
         * @macro_def This is the Macro that will be defined automatically by the ARUDINO IDE if you compile this program for an ARDUINO MEGA 2560
         */
        #define __AVR_ATmega2560__
        /**
         * @macro_def This is the Macro that will be defined automatically by the ARUDINO IDE if you compile this program for an ARDUINO UNO R3
         */
        #define __AVR_ATmega328P__

        /**
         * @macro_def This isn't defined by default. If you define it the LCD will be addressed with 400kHz. This will only work if every connected device supports 400kHz I²C!
         *
         * @warning Don't do if you don't know!
         */
        #define HIGHSPEED
    #endif

    #if defined(ARDUINO) //general platform-check [No tab]

    /**
     * @macro_def This is used for copy_and_paste and renames the copied main-method
     */
    #define main eVirtual_main //main has a different meaning^^

    #if ARDUINO >= 100  //this could be only Arduino.h but this snippet is portable :D
        #include "Arduino.h"
    #else
        #include <wiring.h>
    #endif

    #if not ( defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328P__))
        #error "This library was build for ARDUINO UNO R3 Aand ARDUINO MEGA 2560!"
    #endif

    #if defined(__AVR_ATmega2560__)
        /**
         * @macro_def This defines the Maximum to-address pin. On MEGA its 49 on UNO its 9
         */
        #define PIN_MAX 0x32 //53 pins to address - 4 !!53 is SS
    #else
        #define PIN_MAX 0xA // 13 Pins to address - 4 !!10 is SS
    #endif

    #include <avr/io.h>
    #include <avr/interrupt.h>
    #if (EBOARD_I2C > 0x0) && (EBOARD_LCD > 0x0)
        #include <avr/pgmspace.h>
    #endif

    /**
     * @macro_def this will end any loop done by eBoard
     * @note you can manipulate this with #REPT_TASK
     * @note to avoid desync bug this won't stop the nonblocking LCD connection!
     */
    static bool STOP = false;

    /**
     * @macro_def if you define IGNORE_SIZE before including this file. The size of this program will grow but the used variable-space will shrink...
     */
    #ifdef IGNORE_SIZE
        typedef byte optVAL_t;
    #else
        typedef int optVAL_t;
    #endif

    /**
     * @macro_def you should definitly set EBOARD_DEBUG_MODE to 0x0 when completed developing. This will shrink the size of the program :D
     */
    #ifndef EBOARD_DEBUG_MODE
        #define EBOARD_DEBUG_MODE 0x1
    #endif

    /**
     * @macro_def this is a copy and paste guard to check if the pins used are still in Bound... it was designed for digital pins and shouldnt be disabled
     */
    #ifndef EBOARD_CHECK_PINS
        #define EBOARD_CHECK_PINS 0x1
    #endif

    #ifndef EBOARD_SHIFT_REGISTER
    /**
     * @macro_def set this to 0x1 to enable the control for shiftregister
     */
        #define EBOARD_SHIFT_REGISTER 0x0
    #endif

    /**
     * @macro_def this should be disabled when reaching RELEASED-state. This will check if an PWM-controlled pin is really capable of HPWM ^^
     */
    #ifndef EBOARD_CHECK_PINS_PWM
        #define EBOARD_CHECK_PINS_PWM 0x1
    #endif
    /**
     * @macro_def this has to be enabled to use the shield
     */
    #ifndef EBOARD_USE_SPI
        #define EBOARD_USE_SPI 0x1
    #endif
    /**
     * @macro_def this sets the speed of the Serial connection.... you probably don't need to change this
     */
    #ifndef EBOARD_DEBUG_SPEED
        #define EBOARD_DEBUG_SPEED 9600
    #endif
    /**
     * @macro_def this sets the amount of connected servos to the shield
     */
    #ifndef EBOARD_SPI_SERVO_MAX
        #define EBOARD_SPI_SERVO_MAX 2
    #endif
    /**
     * @macro_def this will remove multiple wrapper from compile-segment. Probably *won't* change program size
     */
    #ifndef EBOARD_USE_UTILITY
        #define EBOARD_USE_UTILITY 0x1
    #endif
    /**
     * @macro_def unable to disable
     */
    #define EBOARD_COPY_AND_PASTE 0x1
    /**
     * @macro_def duty cycle for async task execution... should be higher than 1
     */
    #ifndef EBOARD_PWM_SPE
        #define EBOARD_PWM_SPE 1
    #endif

    #ifndef EBOARD_I2C
        /**
         * @macro_def set this to 0x1 to enable internal I²C support
         */
        #define EBOARD_I2C 0x0 //disabled by default
    #endif

    #ifndef EBOARD_BLUETOOTH
        /**
         * @macro_def set this to 0x1 to enable bluetooth support
         */
        #define EBOARD_BLUETOOTH 0x0
    #endif
    /**
     * @macro_def set this to 0x0 to disable clamp
     */
    #ifndef EBOARD_CLAMP
        #define EBOARD_CLAMP 0x1
    #endif
    /**
     * @macro_def set this to 0x0 to disable software reset
     */
    #ifndef EBOARD_USE_RESET
        #define EBOARD_USE_RESET 0x1
    #endif

    #if EBOARD_USE_RESET > 0x0
        #include <avr/wdt.h>
    #endif

    /**
     * @macro_def this is the STATE PIN. If it is equal to the #PIN_BLUETOOTH_RX it won't be used!
     */
    #ifndef PIN_BLUETOOTH_STATE
        #if defined(__AVR_ATmega2560__)
            #define PIN_BLUETOOTH_STATE 0x13 // 19
        #else
            #define PIN_BLUETOOTH_STATE 0x2
        #endif
    #endif

    /**
     * @macro_def this is the RX-Pin reserved for bluetooth communictaion
     */
    #ifndef PIN_BLUETOOTH_RX
        #if defined(__AVR_ATmega2560__)
            #define PIN_BLUETOOTH_RX 0x13 // 19
        #else
            #define PIN_BLUETOOTH_RX 0x2
        #endif
    #endif

    /**
     * @macro_def this is the TX-Pin reserved for bluetooth communictaion
     */
    #ifndef PIN_BLUETOOTH_TX
        #if defined(__AVR_ATmega2560__)
            #define PIN_BLUETOOTH_TX 0x12 // 18
        #else
            #define PIN_BLUETOOTH_TX 0x3
        #endif
    #endif

    /**
     * @macro_def this is the DiOut pin reserved to control the dir of the main motor
     */
    #ifndef PIN_MOTOR_DIR
        #define PIN_MOTOR_DIR 0x4
    #endif

    /**
     * @macro_def this is the DiOut FAST_PWM [~1kHz] pin reserved to control the dir of the main motor
     */
    #ifndef PIN_MOTOR_SPE
        #define PIN_MOTOR_SPE 0x5
    #endif

    /**
     * @macro_def this is the clock pin for the SN74HC595
     */
    #ifndef PIN_SHIFT_CLK
        #define PIN_SHIFT_CLK 0x6
    #endif
    /**
     * @macro_def this is the data pin for the SN74HC595
     */
    #ifndef PIN_SHIFT_DAT
        #define PIN_SHIFT_DAT 0x7
    #endif
    /**
     * @macro_def this is the latch pin for the SN74HC595
     */
    #ifndef PIN_SHIFT_LAT
        #define PIN_SHIFT_LAT 0x8
    #endif

    //done by arduino
    //if this has an effect... something went wrong :D
    #ifndef HIGH
        #define HIGH 1
    #endif
    #ifndef LOW
        #define LOW 0
    #endif

    #if (EBOARD_BLUETOOTH > 0x0) && defined(__AVR_ATmega328P__)
        /**
         * @brief this is the recomenned-to-use _serial object for bluetooth communcation :D
         *
         * The used pins are based on #PIN_BLUETOOTH_RX and PIN_BLUETOOTH_TX
         */
        SoftwareSerial _serial(PIN_BLUETOOTH_RX,PIN_BLUETOOTH_TX);
    #endif

    #if EBOARD_DEBUG_MODE > 0x0
        /**
         * @macro_def [DEBUG_MODE] enables to use custom assert output
         */
        #define __ASSERT_USE_STDERR
        #include <assert.h>
        /**
         @brief [DEBUG_MODE] custom assert message
         @param __func the function name
         @param __file the file name
         @param __lineno the line number
         @param __sexp the expression
         @note Example output when using a not-allowed pin:
         @verbatim
         Error with: checkIdx in /home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h @222
                 >>idx>0x1 && idx < 0xA
             This happens if an out of bounds exception
             has occured. Following pins shouldn't be used:
             D2&D3 : Used for Bluetooth communictaion
             D4&D5 : Used for main motor control
             D10-13: Used for smart-servo-shield
         @endverbatim
        */
        void __assert (const char *__func, const char *__file, optVAL_t __lineno, const char *__sexp);
        ///@cond
        void __assert (const char *__func, const char *__file, optVAL_t __lineno, const char *__sexp){
            Serial.print("Error with: "); Serial.print(__func);
            Serial.print(" in "); Serial.print(__file);
            Serial.print(" @"); Serial.println(__lineno, DEC);
            Serial.print("         >>");
            Serial.println(__sexp);
            if(strcmp(__func,"checkIdx")==0){
                Serial.println("   This happens if an out of bounds exception");
                Serial.println("   has occured. Following pins shouldn't be used:");
                Serial.print("   D");Serial.print(PIN_BLUETOOTH_RX);Serial.print("&");
                Serial.print("D");Serial.print(PIN_BLUETOOTH_TX);
                Serial.println(" : Used for Bluetooth communictaion");
                Serial.print("   D");Serial.print(PIN_MOTOR_DIR);Serial.print("&");
                Serial.print("D");Serial.print(PIN_MOTOR_SPE);
                Serial.println(" : Used for main motor control");
                #if EBOARD_USE_SPI > 0x0
                    Serial.print("   D10-13");
                    Serial.println(": Used for smart-servo-shield");
                #endif
            }
            Serial.flush();
            abort(); // halt after outputting information
        }
        ///@endcond
    #endif

    /**
        @brief [DEBUG_MODE] used to check if a pin index is in bounds
        @note if not, an assert-error will be raised
        @param idx the index of the pin to check
        @return nothing, blocks on error
     */
    inline void checkIdx(optVAL_t idx);
    ///@cond
    inline void checkIdx(optVAL_t idx){
        #if EBOARD_DEBUG_MODE > 0x0
            assert(idx>=0x0 && idx < PIN_MAX); //changed pins? change me! (didn't want to use macros)
            assert(idx!=PIN_BLUETOOTH_RX&&idx!=PIN_BLUETOOTH_TX);
        #endif
    }
    ///@endcond

    #if EBOARD_COPY_AND_PASTE > 0x0
        #if EBOARD_CHECK_PINS_PWM > 0x0
            /*!
                @brief [COPY&PASTE] [CHECK_PWM] counts high-bits in an int/byte (determined by IGNORE_SIZE)

                @param x  the number to check
                @return the amount of high-bits
            */
            optVAL_t countSetBits (optVAL_t x);
            ///@cond
            optVAL_t countSetBits (optVAL_t x) {
                optVAL_t count; //dont't want to overuse global space^^
                for (count = 0; x; count++)
                    x &= x - 1;
                return count;
            }
            ///@endcond
        #endif

        #if EBOARD_CHECK_PINS > 0x0
            /*!
                @note [COPY&PASTE] [CHECK_PINS] bool set of already declared OUTPUT pins
            */
            unsigned pin_out = 0x0;
            /*!
                @note [COPY&PASTE] [CHECK_PINS] bool set of already declared INPUT pins
            */
            unsigned pin_in  = 0x0;
            /*!
                @brief [COPY&PASTE] [CHECK_PINS] Check if a pin is set to a specific mode
                @note this is no hardware test... this test is based on hard coded data
                @param idx the index of the pin to check
                @param mode the mode the pin should be checked for

                @returns true if the pin is in the requested mode

                🔧 I prevent errors!
            */
            inline bool checkPin(optVAL_t idx, optVAL_t mode = OUTPUT);
            ///@cond
            inline bool checkPin(optVAL_t idx, optVAL_t mode){
                checkIdx(idx);
                return (mode == OUTPUT)? ((pin_out & (1<<idx))>0x0):((pin_in & (1<<idx))>0x0);
            }
            ///@endcond
        #endif

        /*!
            @brief [COPY&PASTE] set a pin to a certain mode => checkPin() will return true then
            @param idx  the index of the pin to set
            @param mode  the mode the pin should be set to
        */
        void setPin(optVAL_t idx, optVAL_t mode = OUTPUT);
        ///@cond
        void setPin(optVAL_t idx, optVAL_t mode){
            #if EBOARD_CHECK_PINS > 0x0
                checkIdx(idx);
                if(mode==OUTPUT) {  //possible to read from OUTPUT digital ... we won't do it
                    pin_out |=  (1<<idx);
                    pin_in  &=  ~(1<<idx);
                }
                else {
                    pin_in  |= (1<<idx);
                    pin_out &= ~(1<<idx);
                }
            #endif
            pinMode(idx, mode);
        }
        ///@endcond
    #endif

    #if EBOARD_BLUETOOTH > 0x0

        /*!
            @brief [BLUETOOTH] reads a single value from bluetooth if available!

            @param oF the character returned on failure

            @return the character read. Returns {oF} on failure!
         */
        inline char readVal(char oF = '.');
        /*!
            @brief [BLUETOOTH] checks if theres a lack of Data!
            @note if this happens you should consider to lower the sending or faster the receiving rate ;)
            @return true if the overflow has happened
            @return false if used on MEGA with default pins as there is no hardware based buffer control :/
            @return false if there is no overflow (recognized)
        */
        inline bool checkOverflow(void);
        /*!
            @brief [BLUETOOTH] writes Data to bluetooth
            @param val This is the data to be written. Can be int, str etc...
        */
        template <typename T>
        inline void writeVal(const T& val);

        /*!
            @brief [BLUETOOTH] this will check if the HC-05 is paired

            @return if #PIN_BLUETOOTH_STATE != #PIN_BLUETOOTH_RX: \n
            &nbsp;&nbsp;&nbsp; true if the HC-05 is paired \n
            &nbsp;&nbsp;&nbsp; false if the HC-05 is disconnected

            @return if #PIN_BLUETOOTH_STATE == #PIN_BLUETOOTH_RX \n
            &nbsp;&nbsp;&nbsp; true in any case - because we don't know ^^

          */
        inline bool isConnected(void);
        ///@cond
        inline bool checkOverflow(void) {
            #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
                return false; //there is no hardware provided control for hardwareserial overflow
            #else
                return (_serial.overflow());
            #endif
        }
        inline char readVal(char oF) {
            #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
                return ((Serial1.available())?(Serial1.read()):(oF));
            #else
                return ((_serial.available())?(_serial.read()):(oF));
            #endif
        }
        template<typename T>
        inline void writeVal(const T& val){
            #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
                Serial1.write(val);
            #else
                _serial.write(val);
            #endif
        }
        inline bool isConnected(void) {
            #if PIN_BLUETOOTH_RX != PIN_BLUETOOTH_STATE
                return digitalRead(PIN_BLUETOOTH_STATE);
            #else
                return true;
            #endif
        }
        ///@endcond
    #endif

    #if EBOARD_SHIFT_REGISTER > 0x0
        /**
            @brief [SHIFT] Manipulate me to set Pins via bitSet operations
        */
        long store_bits = 0L;
        /**
            @brief [SHIFT] Changes a single output Pin

            @param idx index of the bit :D
            @param val the new state of this bit

            @note uses store_bits
        */
        inline void shiftSingle(optVAL_t idx, bool val);
        /**
            @brief [SHIFT] Changes bits according to store_bits
        */
        void shiftAll(void);
        ///@cond
        inline void shiftSingle(optVAL_t idx, bool val) {
            bitWrite(store_bits,idx,val);
            shiftAll();
        }

        void shiftAll(void){
            digitalWrite(PIN_SHIFT_LAT,LOW);
            for(optVAL_t c = 0; (c<32 && !STOP); c++){
                digitalWrite(PIN_SHIFT_CLK,LOW);
                shiftOut(PIN_SHIFT_DAT,PIN_SHIFT_CLK,MSBFIRST,bitRead(store_bits,c));
            }
            digitalWrite(PIN_SHIFT_LAT,LOW);
        }
        ///@endcond
    #endif

    ///@note this is the current to-write PWM value
    optVAL_t _pwmValue = 0x0, _OpwmValue = 0x0;

    /*!
        @brief write a clamped pwm value to an output pin

        @note this will use #PIN_MOTOR_SPE \n The value gets updated every #EBOARD_PWM_SPE seconds

        @param val the pwm value [0-255] to use
    */
    inline void writePWM (optVAL_t val);
    ///@cond
    inline void writePWM(optVAL_t val){
        val = min(val,0xFF); val = max(0x0,val);
        _pwmValue = val;
    }

    #ifdef REPT_TASK
        extern void rept_task(void);
    #endif

    ISR(TIMER1_COMPA_vect) {
      if (_pwmValue!=_OpwmValue){
        analogWrite(PIN_MOTOR_SPE,_pwmValue);
        _OpwmValue = _pwmValue;
      }
        #ifdef REPT_TASK
            rept_task();
        #endif
    }

    ///@endcond
    /*!
        @brief write a boolean state to an output pin

        @note this will automatically call setPin if COPY&PASTE
        @note if SHIFT_REGISTER is enabled all you can assign the outputs 0-based from 100

        @param idx  the index of the pin to use
        @param val  the state the pin should have
    */
    inline void writePin(optVAL_t idx,bool val);
    ///@cond
    inline void writePin(optVAL_t idx,bool val){
        #if EBOARD_SHIFT_REGISTER > 0x0
            if(idx>0x63) {
                idx -= 0x64;
                shiftSingle(idx,val);
                return;
            }
        #endif
        #if EBOARD_CHECK_PINS > 0x0
            checkIdx(idx);
            if(!checkPin(idx))
        #endif
        #if EBOARD_COPY_AND_PASTE > 0x0
            setPin(idx);
        #else
            pinMode(idx,OUTPUT);
        #endif
        digitalWrite(idx,val);
    }
    ///@endcond
    /*!
        @brief read a digital state from an INPUTpin

        @note this will automatically call setPin if COPY&PASTE

        @param idx  the index of the pin to use
        @param dig  determines if the value should be from the digital or the analog pins

        @return the read value as optVAL_t
    */
    inline optVAL_t readPin(optVAL_t idx,bool dig = true);
    ///@cond
    inline optVAL_t readPin(optVAL_t idx,bool dig){
        #if EBOARD_CHECK_PINS > 0x0
            if(dig) checkIdx(idx);
            #if defined (__AVR_ATmega2560__)
                else if (idx<0||idx>0x5){ //use I2C? change => Wire
            #else
                else if (idx<0||idx>0xF){ //use I2C? change => Wire
            #endif
            #if EBOARD_DEBUG_MODE > 0x0
              assert(false);
            #endif
            return 0;
            }
            if(dig && !checkPin(idx,INPUT))
        #endif
        #if EBOARD_COPY_AND_PASTE > 0x0
            setPin(idx,INPUT);
        #else
            pinMode(idx,INPUT);
        #endif
        return((dig)? digitalRead(idx) : analogRead(idx));
    }
    ///@endcond

    #if EBOARD_USE_SPI > 0x0
        /*!
            @struct ServoCds55

            @author EagleoutIce

            @brief [SPI] This is used to communicate with the smart servo shield
            \n &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <b>Don't use manually</b>

            @warning [COPY&PASTE] use SoccerBoard, DynamixelBoard and I2CInOut !
            @warning <b>Don't</b> use this!

            @copyright This code is based on the offical library [https://github.com/leffhub/ServoCds55 (undocumented :/)] cheers!

            [COPY&PASTE] [SPI] You can use this class like this:
            @code
            _servoHandler.write(0,150); //will move servo id 0 to pos 150 [standard limit is 300]
            @endcode
            [SPI] You can use this class like this:
            @code
            //in setup:
            _servoHandler.begin();

            //... in code:
            _servoHandler.write(0,150); //will move servo id 0 to pos 150 [standard limit is 300]
            @endcode
        */
        struct ServoCds55 {
            /*!
                @brief The constructor

                @note There should be only the already created _servoHandler.
                @note This class isn't static!

             */
            #if defined(__AVR_ATmega2560__)
                ServoCds55(optVAL_t CS=53);
            #else
                ServoCds55(optVAL_t CS=10);
            #endif
            /// @brief begin the communication and setup SPI
            void begin();
            /**
                @brief Moves a Servo to a certain position

                @param ID the target ID of the Servo
                @param Pos the target position of the Servo

                @note don't use this function... use write() instead
            */
            void WritePos(optVAL_t ID,optVAL_t Pos);
            /**
                @brief Moves a Servo to a certain position

                @param ID the target ID of the Servo
                @param Pos the target position of the Servo
            */
            inline void write(optVAL_t ID,optVAL_t Pos);
            /**
                @brief Sets the default speed of servos

                @param velocity the new speed value...
            */
            void setVelocity(optVAL_t velocity);
            /**
                @brief Sets the position limits for the servos

                @param posLimit the new positionLimit

                @attention the values are neither clamped nor masked!
            */
            void setPosLimit(optVAL_t posLimit);
            /**
                @brief makes nothing
            */
            void rotate(optVAL_t,optVAL_t);
            /**
                @brief (probably) set the posLimit for only one servo (will be overwritten by write() => writePos())

                @param ID the target ID of the Servo
                @param upperLimit (probably) the upperLimit for a specific servo

                @warning could do something different... lack of documentation
            */
            void SetServoLimit(optVAL_t ID,optVAL_t upperLimit);
            /**
                @brief (probably) set the velocity of only one Servo

                @param ID the target ID of the Servo
                @param velocity (probably) the speed for a specific servo

                @warning could do something different... lack of documentation
            */
            void SetMotormode(optVAL_t ID, optVAL_t velocity);
            /**
                @brief change the ID of a special Servo

                @param ID the target ID of the Servo
                @param newID the newID of the Servo

                @warning using this may result in a total failure of the program... pls no what you're doing!
            */
            void SetID(optVAL_t ID, optVAL_t newID);
            /**
                @brief resets a servo

                @param ID the target ID of the Servo
            */
            void Reset(optVAL_t ID);
            /**
                @brief sends data. This is used internally and shouldnt be used!

                @param what the byte to send

                @returns feedback of SPI.transfer();
            */
            byte sendWait(const byte what);

            /// @brief stores the posLimit value send with write()
            int upperLimit_temp;

        private:
            /// @brief stores the velocity value send with writePos()
            optVAL_t velocity_temp;
            /// @brief stores the ControlPin id
            optVAL_t cs;
            // @brief prevents arduino from endless recallocating memory
            byte tmp;
        };
        ///@cond
        ServoCds55::ServoCds55 (optVAL_t CS):cs(CS) {
            this->velocity_temp = 0x96;
            this->upperLimit_temp = 0x12C; //keep default range of +-300
        }

        void ServoCds55::begin() {
            pinMode(this->cs,OUTPUT);
            digitalWrite(this->cs,HIGH);
            SPI.begin ();
            SPI.setClockDivider(SPI_CLOCK_DIV8);
        }

        byte ServoCds55::sendWait(const byte what) {
            this->tmp = SPI.transfer (what);
            delayMicroseconds (20);
            return this->tmp;
        }

        inline void ServoCds55::setVelocity(optVAL_t velocity){this->velocity_temp = velocity;}
        inline void ServoCds55::setPosLimit(optVAL_t posLimit){this->upperLimit_temp =  posLimit;}

          inline void ServoCds55::write(optVAL_t ID,optVAL_t Pos){
            WritePos(ID,Pos);
        }

        void ServoCds55::rotate(optVAL_t ID,optVAL_t velocity){}

        void ServoCds55::WritePos(optVAL_t ID,optVAL_t Pos){
            digitalWrite(this->cs, LOW);
            sendWait('p');          sendWait(ID);                                sendWait((Pos>>0x8 & 0xff));
            sendWait((Pos & 0xff)); sendWait((this->velocity_temp>>0x8 & 0xff)); sendWait((this->velocity_temp & 0xff));
            sendWait('\t');         sendWait('\r');                              sendWait('\n');
            digitalWrite(this->cs, HIGH);
            delay(8);
        }

        void ServoCds55::SetServoLimit(optVAL_t ID,optVAL_t upperLimit_tempT){
            digitalWrite(this->cs, LOW);
            sendWait('s');                       sendWait(ID);   sendWait((upperLimit_tempT>>0x8 & 0xff));
            sendWait((upperLimit_tempT & 0xff)); sendWait('\t'); sendWait('\r');
            sendWait('\n');
            digitalWrite(this->cs, HIGH);
            delay(8);
        }

        void ServoCds55::SetMotormode(optVAL_t ID, optVAL_t velocity){
            digitalWrite(this->cs, LOW);
            sendWait('m');               sendWait(ID);   sendWait((velocity>>0x8 & 0xff));
            sendWait((velocity & 0xff)); sendWait('\t'); sendWait('\r');
            sendWait('\n');
            digitalWrite(this->cs, HIGH);
            delay(8);
        }

        void ServoCds55::SetID(optVAL_t ID, optVAL_t newID){
            digitalWrite(this->cs, LOW);
            sendWait('i');  sendWait(ID);   sendWait(newID);
            sendWait('\t'); sendWait('\r'); sendWait('\n');
            digitalWrite(this->cs, HIGH);
            delay(8);
        }

        void ServoCds55::Reset(optVAL_t ID){
            digitalWrite(this->cs, LOW);
            sendWait('r');  sendWait(ID); sendWait('\t');
            sendWait('\r'); sendWait('\n');
            digitalWrite(this->cs, HIGH);
            delay(8);
        }
        ///@endcond
        ///@brief this is the "to_use" instance of ServoCds55
        ServoCds55 _servoHandler;
    #endif

    #if EBOARD_COPY_AND_PASTE > 0x0

        /*!
            @struct SoccerBoard

            @author EagleoutIce

            @brief [COPY&PASTE] This is the SoccerBoard ghost struct :D

            @note Some calls like led-calls won't have any effect due to the hardware of the UNO \n But they will work on the MEGA!

            [COPY&PASTE] You can use this class like this:
            @code
            #include <SPI.h>
            #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"
            bool toggle = true;
            SoccerBoard board;

            int main() {
                while(true){
                    board.power(3,toggle);
                    board.sleep(1);
                    toggle = !toggle;
                }
            }
            @endcode
        */
        struct SoccerBoard {
            /*!
                @brief The constructor
                @note Its important to mention the fact that there is nothing interesting about this ;D
            */
            inline SoccerBoard(void);
            //inline ~SoccerBoard(void) {}
            #if EBOARD_USE_UTILITY > 0x0 or defined(__AVR_ATmega2560__) //won't shrink space... just speed things up
                /**
                    *  @brief [MEGA] Control the OnBoard LED
                    *
                    *  @warning this will take control over the Di13 pin on the MEGA
                    *
                    *  @param idx the index of the LED. Won't be checked always be assumed as 1
                    *  @param state the state of the LED
                 */
                inline void led(int idx,bool state);
                /**
                    *  @brief [MEGA] Activate the OnBoard LED
                    *
                    *  @warning this will take control over the Di13 pin on the MEGA
                    *
                    *  @param idx the index of the LED. Won't be checked always be assumed as 1
                    */
                inline void ledOn(int idx);
                /**
                    *  @brief [MEGA] Deactivate the OnBoard LED
                    *
                    *  @warning this will take control over the Di13 pin on the MEGA
                    *
                    *  @param idx the index of the LED. Won't be checked always be assumed as 1
                */
                inline void ledOff(int idx);
                /**
                    *  @brief [MEGA] Deactivate the OnBoard LED
                    *
                    *  @warning this will take control over the Di13 pin on the MEGA
                    */
                inline void ledsOff(void);
                /**
                    *  @brief [MEGA] Activate the OnBoard LED
                    *
                    *  @warning this will take control over the Di13 pin on the MEGA
                    */
                inline void ledMeter(int);

            #endif
            #if EBOARD_USE_UTILITY > 0x0
                /// @brief 🔧 I prevent errors!
                inline void /*bool*/ button(int);
                /// @brief 🔧 I prevent errors!
                inline void waitForButton(int);
                /// @brief 🔧 I prevent errors!
                inline void motor(int,int8_t); //if shield_type known: change to address servos?
                /// @brief 🔧 I prevent errors!
                inline void motorsOff(void);       //probably NOT => DynamixelBoard
            #endif
            //ARDUINO UNO PINOUT
            //D0,D1   => Bluetooth connection
            //D4,D5   => MotorControl (D5: 980Hz)
            //D10,D13 => SPI

            /**
                @brief Set the state of a certain D-pin

                @note unlike the soccerboard you can (if SHIFT_REGISTER enabled) use pinIDs from 100 to 131 (if provided by SN74HC595) directly to set shift-register Pins
                @note if you want to have e.g. 64 bits you can hack the specific code (shiftAll()) to your needs;)

                @param id The id of the pin
                @param state The state the pin should have
            */
            inline void power(optVAL_t id, bool state);
            /**
                @brief Set the state of a certain D-pin to HIGH

                @note unlike the soccerboard you can (if SHIFT_REGISTER enabled) use pinIDs from 100 to 131 (if provided by SN74HC595) directly to set shift-register Pins
                @note if you want to have e.g. 64 bits you can hack the specific code (shiftAll()) to your needs;)
                @note shortcut for power(id, HIGH)

                @param id The id of the pin
            */
            inline void powerOn(optVAL_t id);
            /**
                @brief Set the state of a certain D-pin to LOW

                @note unlike the soccerboard you can (if SHIFT_REGISTER enabled) use pinIDs from 100 to 131 (if provided by SN74HC595) directly to set shift-register Pins
                @note if you want to have e.g. 64 bits you can hack the specific code (shiftAll()) to your needs;)
                @note shortcut for power(id, LOW)

                @param id The id of the pin
            */
            inline void powerOff(optVAL_t id);
            /**
                @brief Say goodnight!

                @param t time in seconds the UNO gets to sleep ;)
            */
            inline void sleep(uint16_t t);
            /**
                @brief Say goodnight!

                @param t time in milliseconds the UNO gets to sleep ;)
            */
            inline void msleep(uint16_t t);
            /**
                @brief Reads a digital value from a pin

                @param id The id of the pin

                @return returns the value read
            */
            inline bool digital (optVAL_t id);
            /**
                @brief Reads an analog value from a pin

                @param id The id of the pin

                @return returns the value read
            */
            inline optVAL_t  analog (optVAL_t id);
            /// @brief Resets the Soccerboard if #EBOARD_USE_RESET is set to true
            inline void reset(void); /* use crash-reset? =>*/ /* wdt_enable(WDTO_15MS); while(1) {} */
        };
        ///@cond
        SoccerBoard::SoccerBoard(void) {}

        #if defined(__AVR_ATmega2560__)
            inline void SoccerBoard::led(int idx, bool state) {writePin(13,state);}
            void SoccerBoard::ledOn(int) {writePin(13,HIGH);}
            void SoccerBoard::ledOff(int) {writePin(13,LOW);}
            void SoccerBoard::ledsOff(void) {writePin(13,LOW);}
            void SoccerBoard::ledMeter(int) {writePin(13,HIGH);}
        #elif EBOARD_USE_UTILITY > 0x0
            void SoccerBoard::led(int, bool) {}
            void SoccerBoard::ledOn(int) {}
            void SoccerBoard::ledOff(int) {}
            void SoccerBoard::ledsOff(void) {}
            void SoccerBoard::ledMeter(int) {}
        #endif

        #if EBOARD_USE_UTILITY > 0x0
            void SoccerBoard::button(int) {}
            void SoccerBoard::waitForButton(int) {}
            void SoccerBoard::motor(int,int8_t) {}
            void SoccerBoard::motorsOff(void) {}
        #endif

        void SoccerBoard::reset(void) {
            #if EBOARD_USE_RESET > 0x0
                wdt_enable(WDTO_15MS);
                while(true) {}
            #endif
        }

        void SoccerBoard::power(optVAL_t id, bool state) {writePin(id,state);}
        void SoccerBoard::powerOn(optVAL_t id) {this->power(id,1);}
        void SoccerBoard::powerOff(optVAL_t id) {this->power(id,0);}
        void SoccerBoard::sleep(uint16_t t) {delay(1000*t);}
        void SoccerBoard::msleep(uint16_t t) {delay(t);}
        bool SoccerBoard::digital (optVAL_t id) {return readPin(id);}
        optVAL_t  SoccerBoard::analog (optVAL_t id) {return readPin(id,0);}

        //@endcond
        //To avoid not_found issues
        /// @macro_def I2CInOut servant
        #define DIGITAL_IN            0x0
        /// @macro_def I2CInOut servant
        #define DIGITAL_IN_INV        0x1
        /// @macro_def I2CInOut servant
        #define DIGITAL_IN_PULLUP     0x2
        /// @macro_def I2CInOut servant
        #define DIGITAL_IN_PULLUP_INV 0x3
        /// @macro_def I2CInOut servant
        #define DIGITAL_OUT           0x4
        /// @macro_def I2CInOut servant
        #define DIGITAL_OUT_INV       0x5
        /// @macro_def I2CInOut servant
        #define DIGITAL_OUT_LOW       0x6
        /// @macro_def I2CInOut servant
        #define DIGITAL_OUT_HIGH      0x7
        /// @macro_def I2CInOut servant
        #define ANALOG_IN_8_BIT       0x8
        /// @macro_def I2CInOut servant
        #define ANALOG_IN_10_BIT      0x9
        /// @macro_def I2CInOut servant
        #define ANALOG_IN_MEAN_8_BIT  0xA
        /// @macro_def I2CInOut servant
        #define ANALOG_IN_MEAN_10_BIT 0xB
        /// @macro_def I2CInOut servant
        #define COUNTER_8_BIT         0xC
        /// @macro_def I2CInOut servant
        #define COUNTER_16_BIT        0xD
        /// @macro_def I2CInOut servant
        #define COUNTER_RISE_8_BIT    0xE
        /// @macro_def I2CInOut servant
        #define COUNTER_RISE_16_BIT   0xF
        /// @macro_def I2CInOut servant
        #define PWM_SLOW              0x8
        /// @macro_def I2CInOut servant
        #define PWM_FAST              0x9
        /// @macro_def I2CInOut servant
        #define FREQ_LOW              0xA
        /// @macro_def I2CInOut servant
        #define FREQ_HIGH             0xB
        /// @macro_def I2CInOut servant
        #define COUNTER_B_DIR         0xC
        /// @macro_def I2CInOut servant
        #define COUNTER_B_DIR_PULLUP  0xD
        /// @macro_def I2CInOut servant
        #define COUNTER_MEAN_8_BIT    0xE
        /// @macro_def I2CInOut servant
        #define COUNTER_MEAN_16_BIT   0xF

        /*!
            @struct I2CInOut

            @author EagleoutIce

            @brief [COPY&PASTE] This is the I2CInOut ghost struct :D

            @note any assignment to Port A won't has anny effect!

            [COPY&PASTE] You can use this class like this:
            @code
            #include <Wire.h>
            #define EBOARD_I2C 0x1
            #include <SPI.h>
            #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"
            SoccerBoard board;
            //nothing in this brackets will have any effect :D
            I2CInOut io1(board,127,ANALOG_IN_10_BIT,COUNTER_RISE_8_BIT, FREQ_HIGH);
            int main() {
                io1.B = HIGH;
                io1.C = 108;
                io1.write();
            }
            @endcode
        */
        struct I2CInOut{
            /*!
                @brief The constructor

                @note It does nothing! :D (well its initalizing pin values but.... nothing special^^)
            */
            I2CInOut(SoccerBoard&, optVAL_t, optVAL_t, optVAL_t, optVAL_t);
            #if EBOARD_USE_UTILITY > 0x0
                ///  @brief 🔧 I prevent errors!
                inline void read(void);
                ///  @brief 🔧 I prevent errors!
                inline void changeAddress(optVAL_t);
                ///  @brief 🔧 I prevent errors!
                inline void changeModes(optVAL_t,optVAL_t,optVAL_t);
            #endif
            /**
                @brief this will write values stored in B and C
                @note 404 'A' not found :D
            */
            inline void write(void);

            ///@brief storing value for A-pin (🔧 I prevent errors!)
            optVAL_t A; //if you've used uint16_t values you'll have to replace it here
            //we only have B - DiOut and C - AO [OUT]
            ///@brief storing value for B-pin [MOTOR DIR]
            optVAL_t B;
            ///@brief storing value for C-pin [MOTOR SPE]
            optVAL_t C;
        };
        ///@cond
        I2CInOut::I2CInOut(SoccerBoard&, optVAL_t, optVAL_t, optVAL_t, optVAL_t) {
            this->A=0x0;this->B=0x0;this->C=0x0;
        }
        #if EBOARD_USE_UTILITY > 0x0
            void I2CInOut::read(void) {}
            void I2CInOut::changeAddress(optVAL_t){}
            void I2CInOut::changeModes(optVAL_t,optVAL_t,optVAL_t) {}
        #endif
        void I2CInOut::write(void){
            setPin(PIN_MOTOR_DIR,((this->B)!=0x0));
            writePWM(this->C);
        }
        ///@endcond

        ///@cond
        struct DynamixelBoard;
        ///@endcond


        /*!
            @struct AX12Servo

            @author EagleoutIce

            @brief [COPY&PASTE] This is the AX12Servo ghost struct :D

            [COPY&PASTE] You can use this class like this:
            @code
            #include <SPI.h>
            #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"
            SoccerBoard board;
            DynamixelBoard servoBoard(board);
            AX12Servo Links(servoBoard,1);
            AX12Servo Rechts(servoBoard,2);

            int main() {
                Links.setPosition(500);
                Rechts.setPosition(200);
                while(true) {}
            }
            @endcode
        */
        struct AX12Servo {
            /*!
                @brief The constructor
                @warning This constructor shouldn't be called!
            */
            AX12Servo(void);
            /*!
                @brief The constructor

                @param dBoard this will be used to register new Servos
                @param servoID the ID of the AX-12 Servo
            */
            AX12Servo(DynamixelBoard &dBoard, optVAL_t servoID); //if borders => setPosLimit

            DynamixelBoard *_conBoard;

            #if EBOARD_USE_UTILITY > 0x0
                /**
                    @brief change the AX-12 Servo this object should speak to

                    @param newID the new ID of the Servo

                    @note why should anyone need that?
                */
                inline void setID(optVAL_t newID);
                /**
                    @brief change the AX-12 Servo this object should speak to

                    @param newID the new ID of the Servo

                    @note this should change the hardwareID of the Servo... but we don't want to mess things up do we?
                    @note if we want to:  _servoHandler.setID(this->id, newID);
                */
                inline void changeMotorID(optVAL_t newID);                    //this should change the hardwareaddress...
                /**
                    @brief set the AX-12 Servo to positionMode

                    @note as there is no rotationMode there is nothing this does
                */
                inline void setPositionMode(void);
                /**
                    @brief set the AX-12 Servo *NOT* to speedMode

                    @note as there is no rotationMode there is nothing this does
                */
                inline void setSpeedMode(void);
                /**
                    @brief 🔧 I prevent errors!

                    @note as there is no rotationMode there is nothing this does
                */
                inline void setSpeed(optVAL_t);
                ///@brief Noone needs the AX-12 Servo LED^^
                inline void ledOff(void);
                ///@brief Noone needs the AX-12 Servo LED^^
                inline void ledOn(void);
                ///@brief 🔧 I prevent errors!
                inline void setTorque(uint16_t);
            #endif

            /**
                @brief This moves the Servo to the new position

                This will overwrite storedPos and storedSpeed!
                @param pos the Position the Servo should go to [0;1023 (w #EBOARD_CLAMP)]
                @param speed the speed of the Servo
            */
            void setPosition(int pos, int speed=0x3FF);
            /**
                @brief This saves the Servo Position

                Sets the values used by DynamixelBoard::action()
                @param pos the Position the Servo should go to [0;1023 (w #EBOARD_CLAMP)]
                @param speed the speed of the Servo
            */
            inline void storePosition(int pos, int speed = 0x3FF);
            /**
                @brief This "kind of" returns the Servo-Position

                @returns The position the servo is (actually driving to)
            */
            inline optVAL_t getPosition(void);
            /**
                @brief Use this if you wan't to have a nice way of writing false

                @note this doesnt talk to the servo

                @returns false
            */
            inline bool isMoving(void);
            /**
                @brief stores the position the Servo should go to DynamixelBoard::action()

                @note pls do me a favour and don't change them manually... use AX12Servo::storePosition()
            */
            int storedPos;
            /**
                @brief stores the Speed of the Servo DynamixelBoard::action()

                @note pls do me a favour and don't change them manually... use AX12Servo::storePosition()
            */
            int storedSpe;

            //bool posMode; //we don't care wich mode we are in ^^

            ///@brief stores the id of the AX12Servo obejct
            optVAL_t id;
        private:
            ///@brief stores the actual pos or move-to pos of the AX12Servo
            int actPos;
            ///@brief stores the actual 'would use speed' of the AX12Servo
            int actSpe;

        }; //shield //set limits auto register for begin

        ///@cond
        AX12Servo::AX12Servo(void) {}
        #if EBOARD_USE_UTILITY > 0x0
            void AX12Servo::setID(optVAL_t newID) {this->id = newID;_servoHandler.SetServoLimit(this->id,_servoHandler.upperLimit_temp);}
            void AX12Servo::changeMotorID(optVAL_t newID) {this->id = newID;} //this should change the hardwareaddress...
            //IF needed: _servoHandler.setID(this->id, newID);
            void AX12Servo::setPositionMode(void)  {}
            void AX12Servo::setSpeedMode(void) {}
            void AX12Servo::setSpeed(optVAL_t) {} //i won't use the rotate functions...
            void AX12Servo::ledOff(void) {} //noone needs the AX12-Servo LED
            void AX12Servo::ledOn(void) {} //really.... noone ^^
            void AX12Servo::setTorque(uint16_t) {} //which damn register? xD
        #endif

        void AX12Servo::setPosition(int pos, int speed) {
            #if EBOARD_CLAMP > 0x0
                if(pos>1023 || speed > 1023) return;
                this->actPos=pos; this->storedPos=pos; this->storedSpe = speed;
                speed = speed*600/1023 - 300;
                pos   = pos  *600/1023 - 300;

            #else
                if(pos>300 || speed > 300) return;
                this->actPos=pos; this->storedPos=pos; this->storedSpe = speed;
            #endif
            if(speed != actSpe){ _servoHandler.setVelocity(speed); this->actSpe=speed;}
            _servoHandler.write(this->id,pos);
        }
        optVAL_t AX12Servo::getPosition(void) {
            return this->actPos; //when moving... false value;
        }
        bool AX12Servo::isMoving(void) {return false;} //we don't know^^
        ///@endcond

        /*!
            @struct DynamixelBoard

            @author EagleoutIce

            @brief [COPY&PASTE] This is the DynamixelBoard ghost struct :D

            [COPY&PASTE] You can use this class like this:
            @code
            #include <SPI.h>
            #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"
            SoccerBoard board;
            DynamixelBoard servoBoard(board);
            AX12Servo Links(servoBoard,1);
            AX12Servo Rechts(servoBoard,2);

            int main() {
                Links.setPosition(500);
                Rechts.setPosition(200);
                while(true) {}
            }
            @endcode
        */
        struct DynamixelBoard {
            /*!
                @brief The constructor
            */
            inline DynamixelBoard(SoccerBoard&);
            //inline ~DynamixelBoard(void) {}
            #if EBOARD_USE_UTILITY > 0x0
                ///@brief 🔧 I prevent errors!
                inline void changeId(optVAL_t);
                ///@brief 🔧 I prevent errors!
                inline void changeMotorID(optVAL_t);
                ///@brief 🔧 I prevent errors!
                inline void ledOn(optVAL_t);
                ///@brief 🔧 I prevent errors!
                inline void ledOff(optVAL_t);
            #endif
            ///@brief will force every AX12Servo to drive to AX12Servo::storedPos with AX12Servo::storedSpeed
            inline void action(void);

            ///@brief it's always good to keep your friends close
            friend struct AX12Servo;
        protected:
            /**
                @brief stores the pointers to the registerd AX12Servo

                @note in the docs, the Number will appear as 2, but it's the value of #EBOARD_SPI_SERVO_MAX
            */
            AX12Servo* connected[EBOARD_SPI_SERVO_MAX];
        };
        ///@cond
        DynamixelBoard::DynamixelBoard(SoccerBoard&) {
            for(optVAL_t i = 0; i < EBOARD_SPI_SERVO_MAX; i++ ) {this->connected[i] = NULL;} //wanna use nullptr... wanna have c++11^^
        }
        //inline ~DynamixelBoard(void) {}
        #if EBOARD_USE_UTILITY > 0x0
            void DynamixelBoard::changeId(optVAL_t) {}
            void DynamixelBoard::changeMotorID(optVAL_t) {}
            void DynamixelBoard::ledOn(optVAL_t) {}
            void DynamixelBoard::ledOff(optVAL_t) {}
        #endif
        void DynamixelBoard::action(void) {
            for(optVAL_t i = 0; (i < EBOARD_SPI_SERVO_MAX && !STOP); i++ ){
                if(this->connected[i] != NULL)
                    (*connected[i]).setPosition((*connected[i]).storedPos,(*connected[i]).storedSpe);
            }
        }


        void AX12Servo::storePosition(int pos, int speed){
            if(this->id < EBOARD_SPI_SERVO_MAX) _conBoard->connected[this->id] = this;
            this->storedPos=pos;this->storedSpe=speed;
        }
        AX12Servo::AX12Servo(DynamixelBoard &dBoard, optVAL_t servoID): _conBoard( &dBoard),id(servoID-1), actSpe(0x96) {
            //#if EBOARD_DEBUG_MODE > 0x0
            //    assert(servoID<EBOARD_SPI_SERVO_MAX);
            //#endif
        }
        ///@endcond

        #if EBOARD_BLUETOOTH > 0x0
            /*!
                @struct RB14Scan

                @author EagleoutIce

                @brief [COPY&PASTE] [BLUETOOTH] This is the RB14Scan ghost struct :D

                @pre to use this class on UNO:
                @code
                #include <SoftwareSerial.h>
                #define EBOARD_BLUETOOTH   0x1
                @endcode
                \n \n  If you don't reconfigure the TX and RX on MEGA:
                @code
                #define EBOARD_BLUETOOTH 0x1
                @endcode

                [COPY&PASTE] [BLUETOOTH] You can use this class like this on UNO:
                @code
                #include <SoftwareSerial.h>
                #define EBOARD_BLUETOOTH   0x1
                #include <SPI.h>
                #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"

                RB14Scan remote;

                int main() {
                    int x = remote.channel(0); //stores value, if available, in 'x'
                }
                @endcode
            */
            struct RB14Scan {
                /*!
                    @brief The constructor
                */
                inline RB14Scan(void);
                ///@brief this will check for connection status [will return true if pin not connected]
                ///@return the state of the connection [1 if paired or unknown; 0 if disconnected]
                inline int raw(optVAL_t);
                ///@brief will return the next char received by the module. A 64 byte Serial buffer is included!
                ///@return the next character in queue
                inline char channel(optVAL_t);
                /**
                    @brief this will write a constant string to the output

                    @note this is a new function :D
                */
                inline void write(const char* const  val);
            };
            ///@cond
            inline RB14Scan::RB14Scan(void) {}
            inline int RB14Scan::raw(optVAL_t) {return isConnected();}
            inline char RB14Scan::channel(optVAL_t) {return ((isConnected())?(readVal()):(-1));}
            inline void RB14Scan::write(const char* const val) {writeVal(val);}
            ///@endcond
        #endif

        /**
            @page page2 The source code

            @brief Welcome to the matrix (:

            @includelineno /home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h
        */
    #endif
#if EBOARD_I2C > 0x0
        /**
            @brief Sends a buffer of bytes to a certain I²C-Device

            @note Using I²C won't block the analog pins!

            @param deviceID the target device
            @param buf the buffer to send
            @param buf_len size of buffer

            @return 0 Transmission went well :D
            @return 1 ERROR: data too long for transmit buffer
            @return 2 ERROR: NACK transmitting address
            @return 3 ERROR: NACK transmitting data
            @return 4 ERROR: UNKNOWN
        */
        inline optVAL_t sendI2C(optVAL_t deviceID,byte *buf, byte buf_len);

        /**
            @brief Sends a byte to a certain I2C-Device

            @note Using I2C won't block the analog pins!

            @param deviceID the target device
            @param buf the buffer to send

            @return 0 Transmission went well :D
            @return 1 ERROR: data too long for transmit buffer
            @return 2 ERROR: NACK transmitting address
            @return 3 ERROR: NACK transmitting data
            @return 4 ERROR: UNKNOWN
        */
        inline optVAL_t sendI2C(optVAL_t deviceID, byte buf);

        /**
            @brief Sends a byte to a certain I²C-Device

            @note Using I²C won't block the analog pins!

            @param ret an array of optVAL_t
            @param ret_len the length of the array
        */
        inline void pingI2C(optVAL_t ret[], optVAL_t ret_len);
        ///@cond
        inline void pingI2C(optVAL_t ret[], optVAL_t ret_len){
            optVAL_t count = 0;
            for (byte i = 1; (i < 255 && !STOP); i++) /*ignore special*/ {
                if(i==200)continue; //internal
                Wire.beginTransmission (i);
                if (Wire.endTransmission () == 0) {
                    if(count < ret_len) ret[count] = i;
                        count++;
                    delay (1);
                }
            }
        }
        inline optVAL_t sendI2C(optVAL_t deviceID,byte *buf, byte buf_len) {
            Wire.beginTransmission(deviceID);
            Wire.write(buf,buf_len);
            return Wire.endTransmission();
        }

        inline optVAL_t sendI2C(optVAL_t deviceID, byte buf){
            Wire.beginTransmission(deviceID);
            Wire.write(buf);
            return Wire.endTransmission();
        }
        ///@endcond

        /**
            @brief Reads a special amount of bits from a certain I²C-Device

            @note Using I²C won't block the analog pins!

            @param deviceID the target device
            @param ret the buffer to send
            @param ret_len size of buffer
            @param blocking should the Arduino wait until there is Data?
        */
        inline void readI2C(optVAL_t deviceID, optVAL_t ret[], optVAL_t ret_len,bool blocking=true);
        ///@cond
        inline void readI2C(optVAL_t deviceID,optVAL_t ret[] , optVAL_t ret_len,bool blocking) {
            for(optVAL_t rect = 0x0; (Wire.available() || (((blocking && (rect < ret_len))) && (!STOP))); rect++)
                ret[rect] = Wire.read();
        }
        ///@endcond

        //Beginof LCD configuration
        #if EBOARD_LCD > 0x0

            PROGMEM const byte basicFont[][8] = {
	            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	            {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
	            {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
	            {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
	            {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
	            {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
	            {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
	            {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
	            {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
	            {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
	            {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
	            {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
	            {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
	            {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
	            {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
	            {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
	            {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
	            {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
	            {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
	            {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
	            {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
	            {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
	            {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
	            {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
	            {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
	            {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
	            {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
	            {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
	            {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
	            {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
	            {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
	            {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
	            {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
	            {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
	            {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
	            {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
	            {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
	            {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
	            {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
	            {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
	            {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
	            {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
	            {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
	            {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
	            {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
	            {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
	            {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
	            {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
	            {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
	            {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
	            {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
	            {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
	            {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
	            {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
	            {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
	            {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
	            {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
	            {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
	            {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
	            {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
	            {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
	            {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
	            {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
	            {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
	            {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
	            {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
	            {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
	            {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
	            {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
	            {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
	            {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
	            {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
	            {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
	            {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
	            {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
	            {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
	            {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
	            {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
	            {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
	            {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
	            {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
	            {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
	            {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
	            {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
	            {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
	            {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
	            {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
	            {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
	            {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
	            {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
	            {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
	            {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
	            {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
	            {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
	            {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
	            {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}
            };
            /*
             *  @note if you don't mind the space this is the extended font set!
             *
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 0x00
                {0x7E,0x81,0x95,0xB1,0xB1,0x95,0x81,0x7E},	// 0x01
                {0x7E,0xFF,0xEB,0xCF,0xCF,0xEB,0xFF,0x7E},	// 0x02
                {0x0E,0x1F,0x3F,0x7E,0x3F,0x1F,0x0E,0x00},	// 0x03
                {0x08,0x1C,0x3E,0x7F,0x3E,0x1C,0x08,0x00},	// 0x04
                {0x38,0x3A,0x9F,0xFF,0x9F,0x3A,0x38,0x00},	// 0x05
                {0x10,0x38,0xBC,0xFF,0xBC,0x38,0x10,0x00},	// 0x06
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 0x07
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 0x08
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 0x09
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 0x0A
                {0x70,0xF8,0x88,0x88,0xFD,0x7F,0x07,0x0F},	// 0x0B
                {0x00,0x4E,0x5F,0xF1,0xF1,0x5F,0x4E,0x00},	// 0x0C
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 0x0D
                {0xC0,0xFF,0x7F,0x05,0x05,0x65,0x7F,0x3F},	// 0x0E
                {0x99,0x5A,0x3C,0xE7,0xE7,0x3C,0x5A,0x99},	// 0x0F
                {0x7F,0x3E,0x3E,0x1C,0x1C,0x08,0x08,0x00},	// 0x10
                {0x08,0x08,0x1C,0x1C,0x3E,0x3E,0x7F,0x00},	// 0x11
                {0x00,0x24,0x66,0xFF,0xFF,0x66,0x24,0x00},	// 0x12
                {0x00,0x5F,0x5F,0x00,0x00,0x5F,0x5F,0x00},	// 0x13
                {0x06,0x0F,0x09,0x7F,0x7F,0x01,0x7F,0x7F},	// 0x14
                {0xDA,0xBF,0xA5,0xA5,0xFD,0x59,0x03,0x02},	// 0x15
                {0x00,0x70,0x70,0x70,0x70,0x70,0x70,0x00},	// 0x16
                {0x80,0x94,0xB6,0xFF,0xFF,0xB6,0x94,0x80},	// 0x17
                {0x00,0x04,0x06,0x7F,0x7F,0x06,0x04,0x00},	// 0x18
                {0x00,0x10,0x30,0x7F,0x7F,0x30,0x10,0x00},	// 0x19
                {0x08,0x08,0x08,0x2A,0x3E,0x1C,0x08,0x00},	// 0x1A
                {0x08,0x1C,0x3E,0x2A,0x08,0x08,0x08,0x00},	// 0x1B
                {0x3C,0x3C,0x20,0x20,0x20,0x20,0x20,0x00},	// 0x1C
                {0x08,0x1C,0x3E,0x08,0x08,0x3E,0x1C,0x08},	// 0x1D
                {0x30,0x38,0x3C,0x3E,0x3E,0x3C,0x38,0x30},	// 0x1E
                {0x06,0x0E,0x1E,0x3E,0x3E,0x1E,0x0E,0x06},	// 0x1F
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 0x20
                {0x00,0x06,0x5F,0x5F,0x06,0x00,0x00,0x00},	// 0x21
                {0x00,0x07,0x07,0x00,0x07,0x07,0x00,0x00},	// 0x22
                {0x14,0x7F,0x7F,0x14,0x7F,0x7F,0x14,0x00},	// 0x23
                {0x24,0x2E,0x6B,0x6B,0x3A,0x12,0x00,0x00},	// 0x24
                {0x46,0x66,0x30,0x18,0x0C,0x66,0x62,0x00},	// 0x25
                {0x30,0x7A,0x4F,0x5D,0x37,0x7A,0x48,0x00},	// 0x26
                {0x04,0x07,0x03,0x00,0x00,0x00,0x00,0x00},	// 0x27
                {0x00,0x1C,0x3E,0x63,0x41,0x00,0x00,0x00},	// 0x28
                {0x00,0x41,0x63,0x3E,0x1C,0x00,0x00,0x00},	// 0x29
                {0x08,0x2A,0x3E,0x1C,0x1C,0x3E,0x2A,0x08},	// 0x2A
                {0x08,0x08,0x3E,0x3E,0x08,0x08,0x00,0x00},	// 0x2B
                {0x00,0xA0,0xE0,0x60,0x00,0x00,0x00,0x00},	// 0x2C
                {0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00},	// 0x2D
                {0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00},	// 0x2E
                {0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x00},	// 0x2F
                {0x3E,0x7F,0x59,0x4D,0x7F,0x3E,0x00,0x00},	// 0x30
                {0x42,0x42,0x7F,0x7F,0x40,0x40,0x00,0x00},	// 0x31
                {0x62,0x73,0x59,0x49,0x6F,0x66,0x00,0x00},	// 0x32
                {0x22,0x63,0x49,0x49,0x7F,0x36,0x00,0x00},	// 0x33
                {0x18,0x1C,0x16,0x13,0x7F,0x7F,0x10,0x00},	// 0x34
                {0x27,0x67,0x45,0x45,0x7D,0x39,0x00,0x00},	// 0x35
                {0x3C,0x7E,0x4B,0x49,0x79,0x30,0x00,0x00},	// 0x36
                {0x03,0x63,0x71,0x19,0x0F,0x07,0x00,0x00},	// 0x37
                {0x36,0x7F,0x49,0x49,0x7F,0x36,0x00,0x00},	// 0x38
                {0x06,0x4F,0x49,0x69,0x3F,0x1E,0x00,0x00},	// 0x39
                {0x00,0x00,0x6C,0x6C,0x00,0x00,0x00,0x00},	// 0x3A
                {0x00,0xA0,0xEC,0x6C,0x00,0x00,0x00,0x00},	// 0x3B
                {0x08,0x1C,0x36,0x63,0x41,0x00,0x00,0x00},	// 0x3C
                {0x14,0x14,0x14,0x14,0x14,0x14,0x00,0x00},	// 0x3D
                {0x00,0x41,0x63,0x36,0x1C,0x08,0x00,0x00},	// 0x3E
                {0x02,0x03,0x51,0x59,0x0F,0x06,0x00,0x00},	// 0x3F
                {0x3E,0x7F,0x41,0x5D,0x5D,0x1F,0x1E,0x00},	// 0x40
                {0x7C,0x7E,0x13,0x13,0x7E,0x7C,0x00,0x00},	// 0x41
                {0x41,0x7F,0x7F,0x49,0x49,0x7F,0x36,0x00},	// 0x42
                {0x1C,0x3E,0x63,0x41,0x41,0x63,0x22,0x00},	// 0x43
                {0x41,0x7F,0x7F,0x41,0x63,0x7F,0x1C,0x00},	// 0x44
                {0x41,0x7F,0x7F,0x49,0x5D,0x41,0x63,0x00},	// 0x45
                {0x41,0x7F,0x7F,0x49,0x1D,0x01,0x03,0x00},	// 0x46
                {0x1C,0x3E,0x63,0x41,0x51,0x73,0x72,0x00},	// 0x47
                {0x7F,0x7F,0x08,0x08,0x7F,0x7F,0x00,0x00},	// 0x48
                {0x00,0x41,0x7F,0x7F,0x41,0x00,0x00,0x00},	// 0x49
                {0x30,0x70,0x40,0x41,0x7F,0x3F,0x01,0x00},	// 0x4A
                {0x41,0x7F,0x7F,0x08,0x1C,0x77,0x63,0x00},	// 0x4B
                {0x41,0x7F,0x7F,0x41,0x40,0x60,0x70,0x00},	// 0x4C
                {0x7F,0x7F,0x06,0x0C,0x06,0x7F,0x7F,0x00},	// 0x4D
                {0x7F,0x7F,0x06,0x0C,0x18,0x7F,0x7F,0x00},	// 0x4E
                {0x1C,0x3E,0x63,0x41,0x63,0x3E,0x1C,0x00},	// 0x4F
                {0x41,0x7F,0x7F,0x49,0x09,0x0F,0x06,0x00},	// 0x50
                {0x1E,0x3F,0x21,0x71,0x7F,0x5E,0x00,0x00},	// 0x51
                {0x41,0x7F,0x7F,0x19,0x39,0x6F,0x46,0x00},	// 0x52
                {0x26,0x67,0x4D,0x59,0x7B,0x32,0x00,0x00},	// 0x53
                {0x03,0x41,0x7F,0x7F,0x41,0x03,0x00,0x00},	// 0x54
                {0x7F,0x7F,0x40,0x40,0x7F,0x7F,0x00,0x00},	// 0x55
                {0x1F,0x3F,0x60,0x60,0x3F,0x1F,0x00,0x00},	// 0x56
                {0x7F,0x7F,0x30,0x18,0x30,0x7F,0x7F,0x00},	// 0x57
                {0x63,0x77,0x1C,0x08,0x1C,0x77,0x63,0x00},	// 0x58
                {0x07,0x4F,0x78,0x78,0x4F,0x07,0x00,0x00},	// 0x59
                {0x67,0x73,0x59,0x4D,0x47,0x63,0x71,0x00},	// 0x5A
                {0x00,0x7F,0x7F,0x41,0x41,0x00,0x00,0x00},	// 0x5B
                {0x01,0x03,0x06,0x0C,0x18,0x30,0x60,0x00},	// 0x5C
                {0x00,0x41,0x41,0x7F,0x7F,0x00,0x00,0x00},	// 0x5D
                {0x08,0x0C,0x06,0x03,0x06,0x0C,0x08,0x00},	// 0x5E
                {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},	// 0x5F
                {0x00,0x00,0x03,0x07,0x04,0x00,0x00,0x00},	// 0x60
                {0x20,0x74,0x54,0x54,0x3C,0x78,0x40,0x00},	// 0x61
                {0x41,0x3F,0x7F,0x44,0x44,0x7C,0x38,0x00},	// 0x62
                {0x38,0x7C,0x44,0x44,0x6C,0x28,0x00,0x00},	// 0x63
                {0x30,0x78,0x48,0x49,0x3F,0x7F,0x40,0x00},	// 0x64
                {0x38,0x7C,0x54,0x54,0x5C,0x18,0x00,0x00},	// 0x65
                {0x48,0x7E,0x7F,0x49,0x03,0x02,0x00,0x00},	// 0x66
                {0x98,0xBC,0xA4,0xA4,0xF8,0x7C,0x04,0x00},	// 0x67
                {0x41,0x7F,0x7F,0x08,0x04,0x7C,0x78,0x00},	// 0x68
                {0x00,0x44,0x7D,0x7D,0x40,0x00,0x00,0x00},	// 0x69
                {0x40,0xC4,0x84,0xFD,0x7D,0x00,0x00,0x00},	// 0x6A
                {0x41,0x7F,0x7F,0x10,0x38,0x6C,0x44,0x00},	// 0x6B
                {0x00,0x41,0x7F,0x7F,0x40,0x00,0x00,0x00},	// 0x6C
                {0x7C,0x7C,0x0C,0x18,0x0C,0x7C,0x78,0x00},	// 0x6D
                {0x7C,0x7C,0x04,0x04,0x7C,0x78,0x00,0x00},	// 0x6E
                {0x38,0x7C,0x44,0x44,0x7C,0x38,0x00,0x00},	// 0x6F
                {0x84,0xFC,0xF8,0xA4,0x24,0x3C,0x18,0x00},	// 0x70
                {0x18,0x3C,0x24,0xA4,0xF8,0xFC,0x84,0x00},	// 0x71
                {0x44,0x7C,0x78,0x44,0x1C,0x18,0x00,0x00},	// 0x72
                {0x48,0x5C,0x54,0x54,0x74,0x24,0x00,0x00},	// 0x73
                {0x00,0x04,0x3E,0x7F,0x44,0x24,0x00,0x00},	// 0x74
                {0x3C,0x7C,0x40,0x40,0x3C,0x7C,0x40,0x00},	// 0x75
                {0x1C,0x3C,0x60,0x60,0x3C,0x1C,0x00,0x00},	// 0x76
                {0x3C,0x7C,0x60,0x30,0x60,0x7C,0x3C,0x00},	// 0x77
                {0x44,0x6C,0x38,0x10,0x38,0x6C,0x44,0x00},	// 0x78
                {0x9C,0xBC,0xA0,0xA0,0xFC,0x7C,0x00,0x00},	// 0x79
                {0x4C,0x64,0x74,0x5C,0x4C,0x64,0x00,0x00},	// 0x7A
                {0x08,0x08,0x3E,0x77,0x41,0x41,0x00,0x00},	// 0x7B
                {0x00,0x00,0x00,0x77,0x77,0x00,0x00,0x00},	// 0x7C
                {0x41,0x41,0x77,0x3E,0x08,0x08,0x00,0x00},	// 0x7D
                {0x02,0x03,0x01,0x03,0x02,0x03,0x01,0x00},	// 0x7E
                {0x78,0x7C,0x46,0x43,0x46,0x7C,0x78,0x00},	// 0x7F
                {0x1E,0xBF,0xE1,0x61,0x33,0x12,0x00,0x00},	// 0x80
                {0x3A,0x7A,0x40,0x40,0x7A,0x7A,0x40,0x00},	// 0x81
                {0x38,0x7C,0x56,0x57,0x5D,0x18,0x00,0x00},	// 0x82
                {0x02,0x23,0x75,0x55,0x55,0x7D,0x7B,0x42},	// 0x83
                {0x21,0x75,0x54,0x54,0x7D,0x79,0x40,0x00},	// 0x84
                {0x20,0x75,0x57,0x56,0x7C,0x78,0x40,0x00},	// 0x85
                {0x00,0x22,0x77,0x55,0x55,0x7F,0x7A,0x40},	// 0x86
                {0x1C,0xBE,0xE2,0x62,0x36,0x14,0x00,0x00},	// 0x87
                {0x02,0x3B,0x7D,0x55,0x55,0x5D,0x1B,0x02},	// 0x88
                {0x39,0x7D,0x54,0x54,0x5D,0x19,0x00,0x00},	// 0x89
                {0x38,0x7D,0x57,0x56,0x5C,0x18,0x00,0x00},	// 0x8A
                {0x01,0x45,0x7C,0x7C,0x41,0x01,0x00,0x00},	// 0x8B
                {0x02,0x03,0x45,0x7D,0x7D,0x43,0x02,0x00},	// 0x8C
                {0x00,0x45,0x7F,0x7E,0x40,0x00,0x00,0x00},	// 0x8D
                {0x79,0x7D,0x26,0x26,0x7D,0x79,0x00,0x00},	// 0x8E
                {0x70,0x7A,0x2D,0x2D,0x7A,0x70,0x00,0x00},	// 0x8F
                {0x44,0x7C,0x7E,0x57,0x55,0x44,0x00,0x00},	// 0x90
                {0x20,0x74,0x54,0x54,0x7C,0x7C,0x54,0x54},	// 0x91
                {0x7C,0x7E,0x0B,0x09,0x7F,0x7F,0x49,0x00},	// 0x92
                {0x32,0x7B,0x49,0x49,0x7B,0x32,0x00,0x00},	// 0x93
                {0x32,0x7A,0x48,0x48,0x7A,0x32,0x00,0x00},	// 0x94
                {0x30,0x79,0x4B,0x4A,0x78,0x30,0x00,0x00},	// 0x95
                {0x3A,0x7B,0x41,0x41,0x7B,0x7A,0x40,0x00},	// 0x96
                {0x38,0x79,0x43,0x42,0x78,0x78,0x40,0x00},	// 0x97
                {0xBA,0xBA,0xA0,0xA0,0xFA,0x7A,0x00,0x00},	// 0x98
                {0x39,0x7D,0x44,0x44,0x44,0x7D,0x39,0x00},	// 0x99
                {0x3D,0x7D,0x40,0x40,0x7D,0x3D,0x00,0x00},	// 0x9A
                {0x38,0x7C,0x64,0x54,0x4C,0x7C,0x38,0x00},	// 0x9B
                {0x68,0x7E,0x7F,0x49,0x43,0x66,0x20,0x00},	// 0x9C
                {0x5C,0x3E,0x73,0x49,0x67,0x3E,0x1D,0x00},	// 0x9D
                {0x44,0x6C,0x38,0x38,0x6C,0x44,0x00,0x00},	// 0x9E
                {0x40,0xC8,0x88,0xFE,0x7F,0x09,0x0B,0x02},	// 0x9F
                {0x20,0x74,0x56,0x57,0x7D,0x78,0x40,0x00},	// 0xA0
                {0x00,0x44,0x7E,0x7F,0x41,0x00,0x00,0x00},	// 0xA1
                {0x30,0x78,0x48,0x4A,0x7B,0x31,0x00,0x00},	// 0xA2
                {0x38,0x78,0x40,0x42,0x7B,0x79,0x40,0x00},	// 0xA3
                {0x7A,0x7B,0x09,0x0B,0x7A,0x73,0x01,0x00},	// 0xA4
                {0x7A,0x7B,0x19,0x33,0x7A,0x7B,0x01,0x00},	// 0xA5
                {0x00,0x26,0x2F,0x29,0x2F,0x2F,0x28,0x00},	// 0xA6
                {0x00,0x26,0x2F,0x29,0x29,0x2F,0x26,0x00},	// 0xA7
                {0x30,0x78,0x4D,0x45,0x60,0x20,0x00,0x00},	// 0xA8
                {0x1C,0x22,0x7D,0x4B,0x5B,0x65,0x22,0x1C},	// 0xA9
                {0x08,0x08,0x08,0x08,0x38,0x38,0x00,0x00},	// 0xAA
                {0x61,0x3F,0x1F,0xCC,0xEE,0xAB,0xB9,0x90},	// 0xAB
                {0x61,0x3F,0x1F,0x4C,0x66,0x73,0xD9,0xF8},	// 0xAC
                {0x00,0x00,0x60,0xFA,0xFA,0x60,0x00,0x00},	// 0xAD
                {0x08,0x1C,0x36,0x22,0x08,0x1C,0x36,0x22},	// 0xAE
                {0x22,0x36,0x1C,0x08,0x22,0x36,0x1C,0x08},	// 0xAF
                {0xAA,0x00,0x55,0x00,0xAA,0x00,0x55,0x00},	// 0xB0
                {0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55},	// 0xB1
                {0x55,0xFF,0xAA,0xFF,0x55,0xFF,0xAA,0xFF},	// 0xB2
                {0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00},	// 0xB3
                {0x10,0x10,0x10,0xFF,0xFF,0x00,0x00,0x00},	// 0xB4
                {0x70,0x78,0x2C,0x2E,0x7B,0x71,0x00,0x00},	// 0xB5
                {0x72,0x79,0x2D,0x2D,0x79,0x72,0x00,0x00},	// 0xB6
                {0x71,0x7B,0x2E,0x2C,0x78,0x70,0x00,0x00},	// 0xB7
                {0x1C,0x22,0x5D,0x55,0x55,0x41,0x22,0x1C},	// 0xB8
                {0x14,0x14,0xF7,0xF7,0x00,0xFF,0xFF,0x00},	// 0xB9
                {0x00,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00},	// 0xBA
                {0x14,0x14,0xF4,0xF4,0x04,0xFC,0xFC,0x00},	// 0xBB
                {0x14,0x14,0x17,0x17,0x10,0x1F,0x1F,0x00},	// 0xBC
                {0x18,0x3C,0x24,0xE7,0xE7,0x24,0x24,0x00},	// 0xBD
                {0x2B,0x2F,0xFC,0xFC,0x2F,0x2B,0x00,0x00},	// 0xBE
                {0x10,0x10,0x10,0xF0,0xF0,0x00,0x00,0x00},	// 0xBF
                {0x00,0x00,0x00,0x1F,0x1F,0x10,0x10,0x10},	// 0xC0
                {0x10,0x10,0x10,0x1F,0x1F,0x10,0x10,0x10},	// 0xC1
                {0x10,0x10,0x10,0xF0,0xF0,0x10,0x10,0x10},	// 0xC2
                {0x00,0x00,0x00,0xFF,0xFF,0x10,0x10,0x10},	// 0xC3
                {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},	// 0xC4
                {0x10,0x10,0x10,0xFF,0xFF,0x10,0x10,0x10},	// 0xC5
                {0x22,0x77,0x55,0x57,0x7E,0x7B,0x41,0x00},	// 0xC6
                {0x72,0x7B,0x2D,0x2F,0x7A,0x73,0x01,0x00},	// 0xC7
                {0x00,0x00,0x1F,0x1F,0x10,0x17,0x17,0x14},	// 0xC8
                {0x00,0x00,0xFC,0xFC,0x04,0xF4,0xF4,0x14},	// 0xC9
                {0x14,0x14,0x17,0x17,0x10,0x17,0x17,0x14},	// 0xCA
                {0x14,0x14,0xF4,0xF4,0x04,0xF4,0xF4,0x14},	// 0xCB
                {0x00,0x00,0xFF,0xFF,0x00,0xF7,0xF7,0x14},	// 0xCC
                {0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},	// 0xCD
                {0x14,0x14,0xF7,0xF7,0x00,0xF7,0xF7,0x14},	// 0xCE
                {0x66,0x3C,0x3C,0x24,0x3C,0x3C,0x66,0x00},	// 0xCF
                {0x05,0x27,0x72,0x57,0x7D,0x38,0x00,0x00},	// 0xD0
                {0x49,0x7F,0x7F,0x49,0x63,0x7F,0x1C,0x00},	// 0xD1
                {0x46,0x7D,0x7D,0x55,0x55,0x46,0x00,0x00},	// 0xD2
                {0x45,0x7D,0x7C,0x54,0x55,0x45,0x00,0x00},	// 0xD3
                {0x44,0x7D,0x7F,0x56,0x54,0x44,0x00,0x00},	// 0xD4
                {0x0A,0x0E,0x08,0x00,0x00,0x00,0x00,0x00},	// 0xD5
                {0x00,0x44,0x7E,0x7F,0x45,0x00,0x00,0x00},	// 0xD6
                {0x02,0x45,0x7D,0x7D,0x45,0x02,0x00,0x00},	// 0xD7
                {0x01,0x45,0x7C,0x7C,0x45,0x01,0x00,0x00},	// 0xD8
                {0x10,0x10,0x10,0x1F,0x1F,0x00,0x00,0x00},	// 0xD9
                {0x00,0x00,0x00,0xF0,0xF0,0x10,0x10,0x10},	// 0xDA
                {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},	// 0xDB
                {0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0},	// 0xDC
                {0x00,0x00,0x00,0x77,0x77,0x00,0x00,0x00},	// 0xDD
                {0x00,0x45,0x7F,0x7E,0x44,0x00,0x00,0x00},	// 0xDE
                {0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F},	// 0xDF
                {0x38,0x7C,0x46,0x47,0x45,0x7C,0x38,0x00},	// 0xE0
                {0xFC,0xFE,0x2A,0x2A,0x3E,0x14,0x00,0x00},	// 0xE1
                {0x3A,0x7D,0x45,0x45,0x45,0x7D,0x3A,0x00},	// 0xE2
                {0x38,0x7C,0x45,0x47,0x46,0x7C,0x38,0x00},	// 0xE3
                {0x32,0x7B,0x49,0x4B,0x7A,0x33,0x01,0x00},	// 0xE4
                {0x3A,0x7F,0x45,0x47,0x46,0x7F,0x39,0x00},	// 0xE5
                {0x80,0xFE,0x7E,0x20,0x20,0x3E,0x1E,0x00},	// 0xE6
                {0x42,0x7E,0x7E,0x54,0x1C,0x08,0x00,0x00},	// 0xE7
                {0x41,0x7F,0x7F,0x55,0x14,0x1C,0x08,0x00},	// 0xE8
                {0x3C,0x7C,0x42,0x43,0x7D,0x3C,0x00,0x00},	// 0xE9
                {0x3A,0x79,0x41,0x41,0x79,0x3A,0x00,0x00},	// 0xEA
                {0x3C,0x7D,0x43,0x42,0x7C,0x3C,0x00,0x00},	// 0xEB
                {0xB8,0xB8,0xA2,0xA3,0xF9,0x78,0x00,0x00},	// 0xEC
                {0x0C,0x5C,0x72,0x73,0x5D,0x0C,0x00,0x00},	// 0xED
                {0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00},	// 0xEE
                {0x00,0x00,0x02,0x03,0x01,0x00,0x00,0x00},	// 0xEF
                {0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00},	// 0xF0
                {0x44,0x44,0x5F,0x5F,0x44,0x44,0x00,0x00},	// 0xF1
                {0x28,0x28,0x28,0x28,0x28,0x28,0x00,0x00},	// 0xF2
                {0x71,0x35,0x1F,0x4C,0x66,0x73,0xD9,0xF8},	// 0xF3
                {0x06,0x0F,0x09,0x7F,0x7F,0x01,0x7F,0x7F},	// 0xF4
                {0xDA,0xBF,0xA5,0xA5,0xFD,0x59,0x03,0x02},	// 0xF5
                {0x08,0x08,0x6B,0x6B,0x08,0x08,0x00,0x00},	// 0xF6
                {0x00,0x80,0xC0,0x40,0x00,0x00,0x00,0x00},	// 0xF7
                {0x00,0x06,0x0F,0x09,0x0F,0x06,0x00,0x00},	// 0xF8
                {0x02,0x02,0x00,0x00,0x02,0x02,0x00,0x00},	// 0xF9
                {0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x00},	// 0xFA
                {0x00,0x12,0x13,0x1F,0x1F,0x10,0x10,0x00},	// 0xFB
                {0x00,0x11,0x15,0x15,0x1F,0x1F,0x0A,0x00},	// 0xFC
                {0x00,0x19,0x1D,0x15,0x17,0x12,0x00,0x00},	// 0xFD
                {0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00},	// 0xFE
                {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} 	// 0xFF
             */

            //Definition of OLED Constants
            /// @macro_def [internal] value to set OLED into command mode
            #define LCD_COMMAND_MODE                0x80
            /// @macro_def [internal] value to set OLED into data mode
            #define LCD_DATA_MODE                   0x40
            /// @macro_def [internal] value to disable the display
            #define LCD_COMMAND_DISPLAY_OFF         0xAE
            /// @macro_def [internal] value to enable the display
            #define LCD_COMMAND_DISPLAY_ON          0xAF
            /// @macro_def [internal] value to set the background of the display to black
            #define LCD_COMMAND_BLACK_BACKGROUND    0xA6
            /// @macro_def [internal] value to set the background of the display to white
            #define LCD_COMMAND_WHITE_BACKGROUND    0xA7
            /// @macro_def [internal] value to change the brightness of the display
            #define LCD_COMMAND_SET_BRIGHTNESS      0x81
            /// @macro_def [internal] value to set the display into page addressing mode
            #define LCD_PAGE_ADDRESSING	            0x02
            /// @macro_def [internal] value to set the display into horizontal aaddressing mode
            #define LCD_HORIZONTAL_ADDRESSING       0x00
            //The regulator
            /// @macro_def [internal] value to enable the PUMP settings
            #define LCD_COMMAND_CHARGE_PUMP_SETTING	0x8d
            /// @macro_def [internal] value to set the PUMP to enabled
            #define LCD_COMMAND_CHARGE_PUMP_ENABLE 0x14

            #ifndef LCD_WIDTH
                /// @macro_def WIDTH of all displays
                #define LCD_WIDTH 128
            #endif
            #ifndef LCD_HEIGHT
                /// @macro_def HEIGHT of all Displays
                #define LCD_HEIGHT 64
            #endif
            /*!
                @struct LCD

                @author EagleoutIce

                @brief [I2C] [LCD] This is used to add support for OLED displays connected to the 'SoccerBoard'

                LCD refers to the connected OLED display

                @copyright This code is based on the offical library [https://github.com/deloarts/OLED_I2C_128x64_Monochrome_Library] if you wan't to use this library in any official purpose, send a message to deloarts. cheers!

                @warning the usage of the LCD will need many Space due to the fact that font is handled by arduino


                @pre to use this class:
                @code
                #include <Wire.h>
                #define EBOARD_I2C 0x1 //do you think this is obsolete ? tell me :D
                #define EBOARD_LCD 0x1
                @endcode

                [I2C] [LCD] You can use this class like this:
                @code
                #include <Wire.h>
                #define EBOARD_I2C 0x1
                #define EBOARD_LCD 0x1
                #include <SPI.h>
                #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"
                SoccerBoard board;
                LCD lcd(board);
                int main() {
                    board.sleep(2); // not needed (it's just funny :P)
                    lcd.clear();
                    lcd.print("Hallo Mama,\n Wie gehts'?");
                    lcd.print(2,2,"-- Gut");
                    lcd.print(3,0,42);
                }
                @endcode

                @note positions will only apply if both of them are smaller as the maximum declared with #LCD_HEIGHT and #LCD_WIDTH
                @note init() will be called on the first display access! [@ref su7]

            */
            struct LCD {
                /*!
                    @brief The constructor

                    @param soccerBoard the connected SoccerBoard object
                    @param id          the ID of the LCD display. Can be identified via pingI2C()
                 */
                LCD(SoccerBoard &soccerBoard, optVAL_t id=0x3C);
                /**
                    @brief changes the address of the LCD display talked to

                    @param newID the target ID of the LCD

                    @note this calls LCD::init() by default!

                    @return true if the transmission was successful
                    @return false if there was one of the following errors:
                        - buffer overflow
                        - NACK on address
                        - NACK on data
                        - unknown error
                */
                inline bool changeID(optVAL_t newID = 0x3C);
                /**
                    @brief clears the LCD

                    @return true if the transmission was successful
                    @return false if there was one of the following errors:
                        - buffer overflow
                        - NACK on address
                        - NACK on data
                        - unknown error
                */
                inline bool clear(void);
                /**
                    @brief prints a string to the display

                    @param data the string to print
                 */
                inline void print(const char* data);
                /**
                    @brief prints an integer to the display

                    @param data the integer to print
                 */
                inline void print(int data);
                /**
                    @brief prints a string to the display at a specific position

                    @param line the line to start at
                    @param col  the col  to start at
                    @param data the string to print
                 */
                inline void print(optVAL_t line, optVAL_t col, const char* data);
                /**
                    @brief prints an integer to the display at a specific position

                    @param data the integer to print [if you want to apply precision you'll have to do it manually there is no float write to save memory]
                    @param line the line to start at
                    @param col  the col  to start at
                 */
                inline void print(optVAL_t line, optVAL_t col, int data);
               /**
                    @brief enable the backlight

                    This is similar with:
                    @code
                    [LCD::]brightness(255);
                    @endcode
                 */
                inline void lightOn(void);
                /**
                    @brief disable the backlight

                    This is similar to:
                    @code
                    [LCD::]brightness(0);
                    @endcode
                 */
                inline void lightOff(void);
                /**
                    @brief clears the screen

                    @return true if the transmission was successful
                    @return false if there was one of the following errors:
                        - buffer overflow
                        - NACK on address
                        - NACK on data
                        - unknown error
                 */
                inline bool reset(void);

                //added features
                /**
                    @brief initializes the Display called by:
                        - LCD::LCD()
                        - LCD::changeID()

                    @return true if the transmission was successful
                    @return false if there was one of the following errors:
                        - buffer overflow
                        - NACK on address
                        - NACK on data
                        - unknown error
                 */
                inline bool init(void);
                /**
                    @brief draws a bitmap representet as an array of bytes

                    @param bitmap the array of bytes representing the bitmap to draw
                    @param posX the startPos abscissa
                    @param posY the startPos ordinate
                    @param hiX  the width of the bitmap
                    @param hiY  the height of the bitmap
                 */
                inline void drawBitmap(const unsigned char *bitmap, byte posX, byte posY, byte hiX, byte hiY);
                /**
                    @brief enable or disable the display

                    @param newMode the mode the Display should have now
                        - true: enabled
                        - false: disabled
                 */
                inline void changeMode(bool newMode = true);
                /**
                    @brief set the position of the cursor

                    @param posX the new position abscissa
                    @param posY the new position ordinate

                    @return true if the transmission was successful
                    @return false if there was one of the following errors:
                        - buffer overflow
                        - NACK on address
                        - NACK on data
                        - unknown error
                 */
                inline bool setCursor(byte posX = 0x0, byte posY = 0x0);
                /**
                    @brief changes the brightness of the display

                    @param val the new brightness of display

                    @return true if the transmission was successful
                    @return false if there was one of the following errors:
                        - buffer overflow
                        - NACK on address
                        - NACK on data
                        - unknown error
                 */
                inline bool changeBrightness (byte val = 0x64);
                /**
                    @brief changes the background of the display

                    @param newBackground the new background of display
                        - true: white
                        - false: black

                 */

                inline void changeBackground(bool newBackground = false);
                ///@brief ID of the Display
                optVAL_t ID;
                private:
                /**
                 * @brief the addressing mode (page/horizontal)
                 * @todo possbile Ads: scrollMode?; font? [size]; invert?
                 *
                 */
                ///@brief posX
                byte pX;
                ///@brief posY
                byte pY;
                ///@brief called_guard
                bool _cI;

                /**
                 * @brief this function will execute two cmd sends without starting and without ending the transmission
                 *
                 * @param o the first param
                 * @param t the second param
                 */
                inline void s2Cmd(optVAL_t o, optVAL_t t);
                /**
                 * @brief this function will execute one cmd send without starting and without ending the transmission
                 *
                 * @param o the param
                 */
                inline void s1Cmd(optVAL_t o);
                /**
                 * @brief this function will execute one dat send without starting and without ending the transmission
                 *
                 * @param o the param
                 */
                inline void s1Dat(optVAL_t o);

            };
            ///@cond
            LCD::LCD(SoccerBoard &soccerBoard, optVAL_t id) {
                this->_cI = false;
                this->ID = id;
                //this->init();
            }
            inline bool LCD::changeID(optVAL_t newID) {
                this->ID = newID;
                return this->init();
            }
            inline bool LCD::clear(void) {
              if(!this->_cI) this->init();
                for(byte i = 0; i < 8; i++){
                    //maybe *8
                    setCursor(0,i);

                    for (byte j = 0; j < 128; j++) {
                        this->s1Dat(0);
                    }
                }
                return setCursor(0,0);
            }
            void LCD::print(optVAL_t line, optVAL_t col, const char *data) {
                if(!this->_cI) this->init();
                byte i = 0x0;
                if(col < ((LCD_WIDTH-1)/8.0) && line < ((LCD_HEIGHT-1)/8.0)) {
                    setCursor(col,line);
                }
                while(data[i] && (pX*8) < LCD_WIDTH){
                    //Serial.print(data[i]); Serial.print(" ");
                    //Serial.print(i); Serial.print(" "); Serial.print(pX); Serial.print(" ");
                    //Serial.println(this->pY);
                    if(data[i] == '\n' || this->pX >= LCD_WIDTH) {
                        setCursor(0,(pY+1));
                    } else if (this->pY >= LCD_HEIGHT){
                        setCursor(0,0);
                    }
                    if(data[i] < 32 || data[i] > 127){ i++; continue;}
                    for (byte j = 0; j < 8; j++){
                        this->s1Dat(pgm_read_byte(&basicFont[data[i]-32][j]));
                    }
                    i++;this->pX++;
                }
            }
            void LCD::print(optVAL_t line, optVAL_t col, int data){
                char buffer[11] = "";
                itoa(data,buffer,10);
                this->print(line,col,buffer);
            }
            inline void LCD::lightOn(void) {
                this->changeBrightness(255);
            }
            inline void LCD::lightOff(void) {
                this->changeBrightness(0);
            }
            inline bool LCD::reset(void) {
                return this->clear();
            }
            inline void LCD::print(int data) {this->print(255,255,data);}
            inline void LCD::print(const char* data) {this->print(255,255,data);}
            inline bool LCD::init() {
                #ifdef HIGHSPEED
                    TWBR = 0xC;
                #endif
                    this->_cI = true;
                    this->s2Cmd(LCD_COMMAND_CHARGE_PUMP_SETTING,LCD_COMMAND_CHARGE_PUMP_ENABLE);
                    this->changeMode(false);
                    this->changeBackground(false);
                    this->changeBrightness(255);
                    this->s2Cmd(0x20,LCD_PAGE_ADDRESSING);
                    this->changeMode(true);

                    //this->print("eBoard \n written by \n EagleoutIce");
                    return this->clear();
            }

            inline void LCD::drawBitmap(const unsigned char *bitmap, byte posX, byte posY, byte hiX, byte hiY){
                if(!this->_cI) this->init();
                setCursor(posX,posY);
                byte col = 0x0;
                for(int i = 0x0; i < (hiX * 8 * hiY); i++){
                    this->s1Dat(pgm_read_byte(&bitmap[i]));
                    if(++col == (hiX * 8)) {
                        col = 0x0;
                        setCursor(posX,++posY);
                    }
                }
            }
            inline void LCD::changeMode(bool newMode) {
                if(!this->_cI) this->init();
                if(newMode) this->s1Cmd(LCD_COMMAND_DISPLAY_ON);
                else this->s1Cmd(LCD_COMMAND_DISPLAY_OFF);
            }
            inline bool LCD::setCursor(byte posX, byte posY) {
                if(!this->_cI) this->init();
                this->s2Cmd((0x00 + (8 *posX & 0x0F)),(0x10 + ((8 * posX >> 4) & 0x0F))); //lower and higher address
                Wire.beginTransmission(this->ID);
                Wire.write(LCD_COMMAND_MODE); Wire.write(0xB0 + posY); //page address
                this->pX = posX; this->pY = posY;
                return (Wire.endTransmission() == 0);
            }

            inline bool LCD::changeBrightness(byte val) {
                if(!this->_cI) this->init();
                this->s2Cmd(0x81,val); //brightness mode
                Wire.beginTransmission(this->ID);
                return (Wire.endTransmission() == 0);
            }
            inline void LCD::changeBackground(bool newBackground) {
                if(!this->_cI) this->init();
                if(newBackground) this->s1Cmd(LCD_COMMAND_WHITE_BACKGROUND);
                else this->s1Cmd(LCD_COMMAND_BLACK_BACKGROUND);
            }

            inline void LCD::s2Cmd(optVAL_t o, optVAL_t t){
                if(!this->_cI) this->init();
                this->s1Cmd(o); this->s1Cmd(t);
            }

            inline void LCD::s1Cmd(optVAL_t C) {
                if(!this->_cI) this->init();
                Wire.beginTransmission(this->ID);
                Wire.write(LCD_COMMAND_MODE); Wire.write(C);
                Wire.endTransmission();
            }
            inline void LCD::s1Dat(optVAL_t o){
                if(!this->_cI) this->init();
                Wire.beginTransmission(this->ID);
                Wire.write(LCD_DATA_MODE); Wire.write(o);
                Wire.endTransmission();
            }

            //@endcond
        #endif
    #endif
    /**
     * @defgroup i2cEx [ 🐼 ] I2C
     *
     */

    /**
        @addtogroup i2cEx
        @brief This tutorial shows you how to deal with the I²C extension!

        @note To use this:
        @code
        #include <Wire.h>
        #define EBOARD_I2C 0x1
        @endcode
        If you use the ARDUINO MEGA the I2C pins are not A4 (SDA) and A5 (SDL). They are seperate (20-SDA;21-SDL)!

        - It is possible to send Data via I2C with sendI2C() \n
        - It is possible to read Data via I2C with readI2C() \n
        - It is possible to scan for I2C addresses with pingI2C(); \n
        @section example Example
        An Example of how to scan for I2C addresses:
        @code
        #include <Wire.h>
        #define EBOARD_I2C 0x1
        #include <SPI.h>
        #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"

        int main() {
            optVAL_t test[3] = {0,0,0};
            pingI2C(test,3);
            Serial.println(test[0]);
            return 0;
        }
        @endcode
        Connected an PCF8591 this produces this output:
        @code
        72
        0 -- Exit Code.
        Program has finished. Reset to start again
        @endcode

        @note The size of the optVAL_t array can be as big as you want to... If its smaller than the amount of addresses found, the addresses will be lost.
    */

    /**
     * @defgroup blueEx [ 🐼 ] BLUETOOTH
     *
     */
    /**
        @addtogroup blueEx
        @brief This tutorial shows you how to deal with the Bluetooth extension!

        @note To use this on UNO:
        @code
        #include <SoftwareSerial.h>
        #define EBOARD_BLUETOOTH 0x1
        @endcode
        \n  If you don't reconfigure the TX and RX on MEGA:
        @code
        #define EBOARD_BLUETOOTH 0x1
        @endcode
        \n
        @note <b>Why using SoftwareSerial on UNO?</b> \n The 0 and 1 pins on the Arduino are the same used for communicate with your PC hence, ond every Upload the HC-05 would has to be unplugged. \n Furthermore Debugging would create a lot of problems ^^

        @section blCon How to use Bluetooth-Communication:

        @warning it is important to identify the layout of the HC-05 it is different from the one showed below the wiring may not apply [KEY is probably represented by a button]!

        @image html /home/eagleoutice/Dokumente/proj/_sia/bt.jpg
        @image latex /home/eagleoutice/Dokumente/proj/_sia/bt.jpg

        You can replace the 1kΩ- with a 1.1kΩ-Resistor

        @subsection suBL1 RB14Scan

        You are able to:
            + Get received values via RB14Scan::channel()
            + Get connection status via RB14Scan::raw()
            + Send values via RB14Scan::write()
    */

    /**
     * @defgroup shiftEx [ 🐼 ] SHIFT
     *
     */
    /**
        @addtogroup shiftEx
        @brief This tutorial shows you how to deal with the Shift extension!

        @note To use this:
        @code
        #define EBOARD_SHIFT_REGISTER 0x1
        @endcode
        @section pinExt Pin extensions

        It is possible to extend the amount of available pins via SN74HC595 Shift-Registers.
        Connect them like this:

        @image html /home/eagleoutice/Dokumente/proj/_sia/t.png
        @image latex /home/eagleoutice/Dokumente/proj/_sia/t.png

        @note it is possible to extend the amount of shiftregisters. This version of eBoard supports up to 32 (64) additional pins. \n But it is possible to connect even more!

        To assign this pins with the special values you can use the SoccerBoard::power() [SoccerBoard::powerOn(); SoccerBoard::powerOff()] Syntax with pinIDs >99 [100 => 0 etc.]
        This is an example-program:
        @code
        #define EBOARD_SHIFT_REGISTER 0x1
        #include <SPI.h>
        #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"

        SoccerBoard board;
        int main() {
            board.powerOn(100);
            return 0;
        }
        @endcode

        This will set the Output value of Pin 100 (Q0 on the first SN74HC595) to HIGH.

        @section hs Hardware specific

        - It is possible to set a Data of a single Pin with shiftSingle();
        - It is also possible to shift the modified #store_bits with shiftAll();

        #store_bits can be modified via bitSet()/bitClear() or long assignment (like = 1000);
    */
    /**
     * @defgroup lcdEx [ 🐼 ] OLED
     *
     */
    /**
        @addtogroup lcdEx
        @brief This tutorial shows you how to deal with the LCD extension!

        @note This is related to @ref i2cEx
        @note To use this:
        @code
        #include <Wire.h>
        #define EBOARD_I2C 0x1
        #define EBOARD_LCD 0x1
        @endcode

        The OLED 128x64 Monochrome Display is connected via I²C (operating: 5V):
        @verbatim
        Arduino UNO|MEGA       OLED
        SDA     (A4|20)    =>  SDA
        SCL     (A5|21)    =>  SCL
        5V      ( 5 V )    =>  VCC
        GND     ( GND )    =>  GND
        @endverbatim

        It is possible to print Text via LCD::print() and to draw Bitmaps with LCD::drawBitmap():

        @image html /home/eagleoutice/Dokumente/proj/_sia/lcd_pr.jpg
        @image latex /home/eagleoutice/Dokumente/proj/_sia/lcd_pr.jpg

        @note It is possible to connect multiple devices via I²C ! Just forward the SCL and SDA lines
    */

    /**
     * @defgroup portTu [ 🐼 ] UNO2MEGA
     *
     */
    /**
        @addtogroup portTu
        @brief This tutorial shows you how to 'port' code and setup from the Arduino UNO R3 to the Arduino MEGA R3

        @pre Layout of UNO R3 and MEGA R3:
            @image html /home/eagleoutice/Dokumente/proj/_sia/Layouts.svg
            @image latex /home/eagleoutice/Dokumente/proj/_sia/Layouts.svg

        @section sprt1 Software

        If you haven't changed any Pin-configuration there is no need to change anything with the code! :D
        \n If you use #EBOARD_BLUETOOTH (RB14Scan) this line is obsolete:
        @code
        #include <SoftwareSerial.h>
        @endcode

        Consider this:
        - use D22-D53 [D49] before using the additional pins [D100...]
        - every Pin from D2 to D13 is capable of PWM! \n it is possible to change the prescaler and therefore raise the PWM value for #PIN_MOTOR_SPE to the recommended 31 kHz [this shouldn't be done on UNO!!!!] \n If you use the default D5 pin the upgrade would work like this:
            @code
            //[...]
            int main() {
            TCCR3B &= ~7;
            TCCR3B |= 1;
            //[...]
            }
            @endcode
            Please keep in mind that this affect the pins D3 and D2 aswell!

        @section sprt2 Hardware

        There are some things you have to consider due to the fact that the MEGA has more pins :P \n Most shields can be applied directly ;)

        - the pins used for shield communication aren't D11 (D10) to D13! they are D51 (D50) to D53!! you shouldn't use them :/
        - I²C communication isn't handled by A4 (SDA) and A5 (SCL)! It works via the communication pins 20 (SDA) and 21 (SCL)
        - the MEGA has 4 hardware-serial ports! (3 (2, one is used for the basic RB14Scan communication by Default :D) of them for custom use)
        - you are able to use the full range of 16 Analog In pins!

    */

#if EBOARD_COPY_AND_PASTE > 0x0

        /// @brief [COPY&PASTE] Assures the existence of the "qfix-code-main-method"
        extern int eVirtual_main();
        /// @brief this is a guard

        /// @brief [COPY&PASTE] As we have an Arduino we need a setup function ;)
        void setup(void);

        ///@cond
        void setup(void) {
            //setup of RX and TX should be handled manually - in everyCase ^^
            setPin(PIN_MOTOR_DIR);
            setPin(PIN_MOTOR_SPE);
            #if EBOARD_DEBUG_MODE > 0x0
                Serial.begin(EBOARD_DEBUG_SPEED);
            #endif
            //this will initialize the interrupt handling!
            cli();
            TCCR1A = 0; TCCR1B = 0; //clear registers;
            OCR1A = EBOARD_PWM_SPE * 15624;
            TCCR1B |= (1 << WGM12); TCCR1B |= (1 << CS10); TCCR1B |= (1 << CS12);
            TIMSK1 |= (1 << OCIE1A);
            sei();
            #if EBOARD_BLUETOOTH > 0x0
                ///@warning Some modules have 9600 as default, some have 38400
                ///@todo ask for configure custom BAUD
                #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
                    Serial1.begin(38400);
                #else
                    _serial.begin(38400);
                #endif
                if(PIN_BLUETOOTH_STATE!=PIN_BLUETOOTH_RX) setPin(PIN_BLUETOOTH_STATE,INPUT);
            #endif
            #if EBOARD_I2C > 0x0
                Wire.begin();
            #endif
            #if EBOARD_SHIFT_REGISTER > 0x0
                pinMode(PIN_SHIFT_CLK,OUTPUT);
                pinMode(PIN_SHIFT_DAT,OUTPUT);
                pinMode(PIN_SHIFT_LAT,OUTPUT);
                shiftAll(); //set all to 0
            #endif
            #if EBOARD_USE_SPI > 0x0
                _servoHandler.begin(); //Setup SPI
            #endif

            #if EBOARD_DEBUG_MODE > 0x0
                Serial.print(eVirtual_main());
                Serial.println(" -- Exit Code. \n Program has finished. Reset to start again");
            #else
                eVirtual_main();
            #endif
            delay(200);
            cli(); //disable timers after running the program :D
            writePWM(0);
        }
        ///@endcond
        /// @brief [COPY&PASTE] As we have an Arduino we need a setup function ;)
        void loop(void);
        ///@cond
        void loop(void){
          //shall be empty
          }
        ///@endcond

#endif

#else
    #error This library is build for arduino-devices and should be used only in the Arduino IDE or with a similar linking process
#endif
#pragma GCC diagnostic pop


#endif
