///EagleoutIce 2018
///IF YOU SEE THIS THIS IS THE UNPROCESSED FILE! GO TO 'SOURCE CODE' IN THE DOCS
/**
 * @file eBoard.h
 * @todo 1. LCd support
 */
/**
 @mainpage eBoard 1.2e - shackle the Arduino!

 @note It was an explicit decision to pack everything needed in one headerfile - readability is granted by the doc
 @note This code was written for the Arduino UNO R3 used with the Smart Servo Shield and allows to copy-paste Code running on a qfixSoccerboard
 @note This code comes completely wihtout any warranty - no example was tested right now^^


 This Header file was created to port Codes running on the qfix SoccerBoard [DynamixelBoard etc...] directly onto the Arduino UNO R3 [with Smart Servo Shield].
 To use it you'll have to replace all qfix-related header-files [*.h] with the following:
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
 There are multiple macros you can manipulate the behaviour of this header:
 @note The constants will appear with their default values in codeSnippets -> be careful with assumptions ;)

 <b>General</b>

 - [IGNORE_SIZE]             : DEF: the size of this program will grow but the used variable-space will shrink...
 - #EBOARD_DEBUG_MODE        : 0x0: disable [DEBUG_MODE]
 - #EBOARD_DEBUG_SPEED       : if [DEBUG_MODE]: set Speed (9600...)
 - #EBOARD_CHECK_PINS        : 0x0: disable range-check for normal READ and WRITE
 - #EBOARD_CHECK_PINS_PWM    : 0x0: disable range-check for PWM-WRITE
 - #EBOARD_USE_SPI           : 0x0: disables internal SPI-handling
 - #EBOARD_USE_UTILITY       : 0x0: removes useless code-parts
 - #EBOARD_COPY_AND_PASTE    : 0x0: kills the spirit of this header ^^
 - #EBOARD_SPI_SERVO_MAX     : Sets the amount of the visible, connected AX-12
 - #EBOARD_I2C               : 0x1: enables I2C tools
 - #EBOARD_SHIFT_REGISTER    : 0x1: enables SHIFT_REGISTER
 - #EBOARD_BLUETOOTH         : 0x1: enables Bluetooth support
 - #EBOARD_PWM_SPE           : Sets the duty cycle for @ref su111
 - #EBOARD_CLAMP             : 0x0: disables clamp
 - #EBOARD_USE_RESET         : 0x0: disable software reset

 <b>Pins</b>
 - #PIN_BLUETOOTH_RX         : pinID(2) of RX-Pin   -- why? [@ref su3]
 - #PIN_BLUETOOTH_TX         : pinID(3) of TX-Pin   -- why? [@ref su3]
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

 @section s3 Examples

 - @ref i2c
 - @ref shift
 - @ref blue
*/

/**
 @page page1 About
 @brief Something about the Author :D - me ;P
 @author Florian Sihler - EagleoutIce
 @copyright EagleoutIce 2018
 @version 1.2e
 @date 7.2.2018

 @section m1 Motivation
 This header was created to port SoccerBoard-Code to the Arduino UNO R3 \n
 It was written in ~300 [v1.2e] minutes and documented by Doxygen 1.8.15. \n


 @section m2 General Information
 I am an 18-year old programmer and I am coding since i was a kid. \n
 @warning Any Errors or Bugs? florian.sihler@web.de



  @image html /home/eagleoutice/Dokumente/proj/_sia/pp.jpeg
  @image latex /home/eagleoutice/Dokumente/proj/_sia/pp.jpeg
*/

/**
  @page i2c I2C-Functionality
  @brief a tutorial for the I²C-Extension
  @todo examples and sections for all functions
  @note To use this:
  @code
  #define EBOARD_I2C 0x1
  @endcode

  - It is possible to send Data via I2C with sendI2C() \n
  - It is possible to read Data via I2C with readI2C() \n
  - It is possible to scan for I2C addresses with pingI2C(); \n
  @section Example
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
  @page shift SHIFT-Functionality
  @brief A tutorial for the Pin-Extension
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

  @section Hardware specific

  - It is possible to set a Data of a single Pin with shiftSingle();
  - It is also possible to shift the modified #store_bits with shiftAll();

  #store_bits can be modified via bitSet()/bitClear() or long assignment (like = 1000);


*/
/**
  @page blue BLUETOOTH-Connection
  @brief A tutorial for the Bluetooth-Extension
  @note To use this:
  @code
  #include <SoftwareSerial.h>
  #define EBOARD_BLUETOOTH 0x1
  @endcode

  @note Why using SoftwareSerial? \n     The 0 and 1 pins on the Arduino are the same used for communicate with your PC hence, ond every Upload the HC-05 would has to be unplugged. \n Furthermore Debugging would create a lot of problems ^^

  @section blCon How to use Bluetooth-Communication:
    @warning it is important to identify the layout of the HC-05 it is different from the one showed below the wiring may not apply [KEY is probably represented by a button]!

    @image html /home/eagleoutice/Dokumente/proj/_sia/bt.jpg
    @image latex /home/eagleoutice/Dokumente/proj/_sia/bt.jpg

    @warning mistakes were made ^^ - somethings wrong with the power connection....
    @todo don't be stupid^^

    You can replace the 1kΩ- with a 1.1kΩ-Resistor

  @todo fill bluetooth

*/

/**
  @page stats Statistics
  @brief Cuz everyone loves them :O
    @warning it's easy to misinterpret this statistics!
     \n eBoard is taking care of many things and only occupying a minimum of space! Most things you would have to write by yourselve otherwise (which may resulted in an even higher amount of used space!)


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
    @endcode


    @subsection ssu1 1.1 Empty program

    @note Used:
    @code
    [...]
    int main() {return 0;}
    @endcode

    Following results: \n
    [Version: 1.2a] \n
    [Dev]: 'Binäre Sketchgröße: 6.994 Bytes (von einem Maximum von 32.256 Bytes)' \n
    [Rel]: 'Binäre Sketchgröße: 3.264 Bytes (von einem Maximum von 32.256 Bytes)' \n

    [Stats for other releases will be evaluated asap]
*/
/**
  @page p5 Changelog
  @brief A short overview about the developing process
  @section ver1 Version 1 - Olivander

  @note this changelog is maintained by EagleoutIce

  @subsection su1 Version 1.0e - I ate the alpha-cookie :D [~130m]

   leaving the alpha-state :D [after 130 minutes :P]

   + Macros to enable full control over included content
   + Documantation
   + Todo list ._.
   - logfile support

  @subsection su2 Version 1.1b - Hello Slave [~70m]

    Added support for several external devices

    + Macros for devices
    + I²C support
    + S.C.H.I.E.L.D support
    + Shift-register support

  @subsection su3 Version 1.2e - On your command, master [~100m]

    Added support for remote control

    + Changed #PIN_BLUETOOTH_RX and #PIN_BLUETOOTH_TX to 2,3 for SoftwareSerial based on common problems
    + Rewritten ServoCds55
    + Tried to make code more compact :D
    + Optimized PWM support
    \n
    + Async Task execution
    + RB14Scan [No protocoll!]
    \n
    + ! #EBOARD_CHECK_PINS doesn't checks full range anymore ... should be fixed

  @subsection su4 Version 1.3g - Make this safe!
    [PRE]

    + Clamped Motorpositions
*/

//i am a guard... leave me alone :D
#ifndef EBOARD_HEADER_GUARD
#define EBOARD_HEADER_GUARD

#ifdef DOC
#define ARDUINO 200
/**
 * @note This will appear as 0x1 in the docs but the real default value is 0x0
 */
#define EBOARD_I2C 0x1
/**
 * @note This will appear as 0x1 in the docs but the real default value is 0x0
 */
#define EBOARD_SHIFT_REGISTER 0x1
/**
 * @note This will appear as 0x1 in the docs but the real default value is 0x0
 */
#define EBOARD_BLUETOOTH 0x1

#endif

#if defined(ARDUINO) //general platform-check

/**
 * @note This is used for copy_and_paste and renames the copied main-method
 */
#define main eVirtual_main //main has a different meaning^^

#if ARDUINO >= 100  //this could be only Arduino.h but this snippet is portable :D
  #include "Arduino.h"
  #else
    #include <wiring.h>
  #endif

#include <avr/io.h>
#include <avr/interrupt.h>


/**
 * @def if you define IGNORE_SIZE before including this file. The size of this program will grow but the used variable-space will shrink...
 */
#ifdef IGNORE_SIZE
  typedef byte optVAL_t;
#else
  typedef int optVAL_t;
#endif

/**
 * @note you should definitly set EBOARD_DEBUG_MODE to 0x0 when completed developing. This will shrink the size of the program :D
 */
#ifndef EBOARD_DEBUG_MODE
  #define EBOARD_DEBUG_MODE 0x1
#endif

/**
 * @note this is a copy and paste guard to check if the pins used are still in Bound... it was designed for digital pins and shouldnt be disabled
 */
#ifndef EBOARD_CHECK_PINS
  #define EBOARD_CHECK_PINS 0x1
#endif


#ifndef EBOARD_SHIFT_REGISTER
/**
 * @note set this to 0x1 to enable the control for shiftregister
 */
  #define EBOARD_SHIFT_REGISTER 0x0
#endif

/**
 * @note this should be disabled when reaching RELEASED-state. This will check if an PWM-controlled pin is really capable of HPWM ^^
 */
#ifndef EBOARD_CHECK_PINS_PWM
  #define EBOARD_CHECK_PINS_PWM 0x1
#endif
/**
 * @note this has to be enabled to use the shield
 */
#ifndef EBOARD_USE_SPI
  #define EBOARD_USE_SPI 0x1
#endif
/**
 * @note this sets the speed of the Serial connection.... you probably don't need to change this
 */
#ifndef EBOARD_DEBUG_SPEED
  #define EBOARD_DEBUG_SPEED 9600
#endif

/**
 * @note this sets the amount of connected servos to the shield
 */
#ifndef EBOARD_SPI_SERVO_MAX
#define EBOARD_SPI_SERVO_MAX 2
#endif

/**
 * @note this will remove multiple wrapper from compile-segment. Probably *won't* change program size
 */
#ifndef EBOARD_USE_UTILITY
  #define EBOARD_USE_UTILITY 0x1
#endif

/**
 * @note just don't disable it
 */
#ifndef EBOARD_COPY_AND_PASTE
  #define EBOARD_COPY_AND_PASTE 0x1
#endif

/**
 * @note duty cycle for async task execution... should be higher than 1
 */
#ifndef EBOARD_PWM_SPE
  #define EBOARD_PWM_SPE 2
#endif


#ifndef EBOARD_I2C
/**
 * @note set this to 0x1 to enable internal I²C support
 */
  #define EBOARD_I2C 0x0 //disabled by default
#endif


#ifndef EBOARD_BLUETOOTH
/**
 * @note set this to 0x1 to enable bluetooth support
 */
  #define EBOARD_BLUETOOTH 0x0
#endif
/**
 * @note set this to 0x0 to disable clamp
 */
#ifndef EBOARD_CLAMP
  #define EBOARD_CLAMP 0x1
#endif

/**
 * @note set this to 0x0 to disable software reset
 */
#ifndef EBOARD_USE_RESET
  #define EBOARD_USE_RESET 0x1
#endif

#if EBOARD_USE_RESET > 0x0
  #include <avr/wdt.h>
#endif

/**
 * @note this is the STATE PIN. If it is equal to the #PIN_BLUETOOTH_RX it won't be used!
 */
#ifndef PIN_BLUETOOTH_STATE
  #define PIN_BLUETOOTH_STATE 0x2
#endif

/**
 * @note this is the RX-Pin reserved for bluetooth communictaion
 */
#ifndef PIN_BLUETOOTH_RX
  #define PIN_BLUETOOTH_RX 0x2
#endif

/**
 * @note this is the TX-Pin reserved for bluetooth communictaion
 */
#ifndef PIN_BLUETOOTH_TX
  #define PIN_BLUETOOTH_TX 0x3
#endif

/**
 * @note this is the DiOut pin reserved to control the dir of the main motor
 */
#ifndef PIN_MOTOR_DIR
  #define PIN_MOTOR_DIR 0x4
#endif

/**
 * @note this is the DiOut FAST_PWM [~1kHz] pin reserved to control the dir of the main motor
 */
#ifndef PIN_MOTOR_SPE
  #define PIN_MOTOR_SPE 0x5
#endif



/**
 * @note this is the clock pin for the SN74HC595
 */
#ifndef PIN_SHIFT_CLK
  #define PIN_SHIFT_CLK 0x6
#endif

/**
 * @note this is the data pin for the SN74HC595
 */
#ifndef PIN_SHIFT_DAT
  #define PIN_SHIFT_DAT 0x7
#endif

/**
 * @note this is the latch pin for the SN74HC595
 */
#ifndef PIN_SHIFT_LAT
  #define PIN_SHIFT_LAT 0x8
#endif



//done by arduino
// if this has an effect... something went wrong :D
#ifndef HIGH
  #define HIGH 1
#endif
#ifndef LOW
  #define LOW 0
#endif

#if EBOARD_BLUETOOTH > 0x0
  SoftwareSerial _serial(PIN_BLUETOOTH_RX,PIN_BLUETOOTH_TX);
#endif

#if EBOARD_DEBUG_MODE > 0x0
  /**
   * @note [DEBUG_MODE] enables to use custom assert output
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
    Serial.print("Error with: ");
    Serial.print(__func);
    Serial.print(" in ");
    Serial.print(__file);
    Serial.print(" @");
    Serial.println(__lineno, DEC);
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
  @note if you're not using the Arduino UNO R3 you may have to change this check
  @param idx the index of the pin to check
  @return nothing, blocks on error
*/
inline void checkIdx(optVAL_t idx);
///@cond
inline void checkIdx(optVAL_t idx){
  #if EBOARD_DEBUG_MODE > 0x0
    assert(idx>=0x0 && idx < 0xA); //changed pins? change me! (didn't want to use macros)
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
    @brief I prevent errors! if the pin is in the requested mode
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
    if(mode==OUTPUT) {  //possible to read from OUTPUT digital ... won't do it
      pin_out |=  (1<<idx); // we won't use bit Operations
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
  @return the character read. Returns '.' on failure!
 */
  inline char readVal(void);
  /*!
  @brief [BLUETOOTH] checks if theres a lack of Data!
  @note if this happens you should consider to lower the sending or faster the receiving rate ;)
  @return the character read. Returns '.' on failure!
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
    return (_serial.overflow());
  }
  inline char readVal(void) {
    return ((_serial.available())?(_serial.read()):('.'));
  }
  template<typename T>
  inline void writeVal(const T& val){
    _serial.write(val);
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
  for (byte i = 1; i < 255; i++) /*ignore special*/ {
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
  @todo write a global BREAK To stop while loops
*/
inline void readI2C(optVAL_t deviceID, optVAL_t ret[], optVAL_t ret_len,bool blocking=true);
///@cond
inline void readI2C(optVAL_t deviceID,optVAL_t ret[] , optVAL_t ret_len,bool blocking) {
  for(optVAL_t rect = 0x0; (Wire.available() || (blocking && (rect < ret_len))); rect++)
    ret[rect] = Wire.read();
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
  for(optVAL_t c = 0; c<32; c++){
    digitalWrite(PIN_SHIFT_CLK,LOW);
    shiftOut(PIN_SHIFT_DAT,PIN_SHIFT_CLK,MSBFIRST,bitRead(store_bits,c));
  }
  digitalWrite(PIN_SHIFT_LAT,LOW);
}
///@endcond

#endif

///@note this is the current to-write PWM value
optVAL_t _pwmValue = 0x0;

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
    analogWrite(PIN_MOTOR_SPE,_pwmValue);
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
    return shiftSingle(idx,val);
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
  else if (idx<0||idx>5){ //use I2C? change => Wire
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
    @note If you want to do this manually use this class aswell
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
      ServoCds55(optVAL_t CS=10);
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
        @warning the values are neither clamped nor masked!
      */
      void setPoslimit(optVAL_t posLimit);
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
        delayMicroseconds (23);
        return this->tmp;
      }

      inline void ServoCds55::setVelocity(optVAL_t velocity){this->velocity_temp = velocity;}
      inline void ServoCds55::setPoslimit(optVAL_t posLimit){this->upperLimit_temp =  posLimit;}

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
      delay(10);
    }

    void ServoCds55::SetServoLimit(optVAL_t ID,optVAL_t upperLimit_tempT){
      digitalWrite(this->cs, LOW);
      sendWait('s');                       sendWait(ID);   sendWait((upperLimit_tempT>>0x8 & 0xff));
      sendWait((upperLimit_tempT & 0xff)); sendWait('\t'); sendWait('\r');
      sendWait('\n');
      digitalWrite(this->cs, HIGH);
      delay(10);
    }

    void ServoCds55::SetMotormode(optVAL_t ID, optVAL_t velocity){
      digitalWrite(this->cs, LOW);
      sendWait('m');               sendWait(ID);   sendWait((velocity>>0x8 & 0xff));
      sendWait((velocity & 0xff)); sendWait('\t'); sendWait('\r');
      sendWait('\n');
      digitalWrite(this->cs, HIGH);
      delay(10);
    }

    void ServoCds55::SetID(optVAL_t ID, optVAL_t newID){
      digitalWrite(this->cs, LOW);
      sendWait('i');  sendWait(ID);   sendWait(newID);
      sendWait('\t'); sendWait('\r'); sendWait('\n');
      digitalWrite(this->cs, HIGH);
      delay(10);
    }

    void ServoCds55::Reset(optVAL_t ID){
      digitalWrite(this->cs, LOW);
      sendWait('r');  sendWait(ID); sendWait('\t');
      sendWait('\r'); sendWait('\n');
      digitalWrite(this->cs, HIGH);
      delay(10);
    }
    ///@endcond
    ///@brief this is the "to_use" instance of ServoCds55
    ServoCds55 _servoHandler;
#endif
#if EBOARD_COPY_AND_PASTE > 0x0

/// @brief [COPY&PASTE] Assures the existence of the "qfix-code-main-method"
extern int eVirtual_main();

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
    _serial.begin(38400); ///@todo ask for configure custom BAUD
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
  pinMode(9,OUTPUT);
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
  //i shall be empty
}
///@endcond


/*!
  @struct SoccerBoard
  @author EagleoutIce
  @brief [COPY&PASTE] This is the SoccerBoard ghost struct :D
  @note Some calls like led-calls won't have any effect due to the hardware of the UNO

  [COPY&PASTE] You can use this class like this:
  @code
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
#if EBOARD_USE_UTILITY > 0x0 //won't shrink space... just speed things up
  /// @brief I prevent errors!
  inline void led(int,bool);
  ///  @brief I prevent errors!
  inline void ledOn(int);
  /// @brief I prevent errors!
  inline void ledOff(int);
  /// @brief I prevent errors!
  inline void ledsOff(void);
  /// @brief I prevent errors!
  inline void ledMeter(int);
  /// @brief I prevent errors!
  inline void /*bool*/ button(int);
  /// @brief I prevent errors!
  inline void waitForButton(int);
  /// @brief I prevent errors!
  inline void reset(void); /* use crash-reset? =>*/ /* wdt_enable(WDTO_15MS); while(1) {} */
  /// @brief I prevent errors!
  inline void motor(int,int8_t); //if shield_type known: change to address servos?
  /// @brief I prevent errors!
  inline void motorsOff(void);       //probably NOT => DynamixelBoard

#endif
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

  static inline void stop(void);
};
///@cond
     SoccerBoard::SoccerBoard(void) {}
#if EBOARD_USE_UTILITY > 0x0
void SoccerBoard::led(int, bool) {}
void SoccerBoard::ledOn(int) {}
void SoccerBoard::ledOff(int) {}
void SoccerBoard::ledsOff(void) {}
void SoccerBoard::ledMeter(int) {}
void SoccerBoard::button(int) {}
void SoccerBoard::waitForButton(int) {}
void SoccerBoard::motor(int,int8_t) {}
void SoccerBoard::motorsOff(void) {}
#endif


static inline void SoccerBoard::stop(void){
  
}

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
/// @brief I2CInOut servant
#define DIGITAL_IN            0x0
/// @brief I2CInOut servant
#define DIGITAL_IN_INV        0x1
/// @brief I2CInOut servant
#define DIGITAL_IN_PULLUP     0x2
/// @brief I2CInOut servant
#define DIGITAL_IN_PULLUP_INV 0x3
/// @brief I2CInOut servant
#define DIGITAL_OUT           0x4
/// @brief I2CInOut servant
#define DIGITAL_OUT_INV       0x5
/// @brief I2CInOut servant
#define DIGITAL_OUT_LOW       0x6
/// @brief I2CInOut servant
#define DIGITAL_OUT_HIGH      0x7
/// @brief I2CInOut servant
#define ANALOG_IN_8_BIT       0x8
/// @brief I2CInOut servant
#define ANALOG_IN_10_BIT      0x9
/// @brief I2CInOut servant
#define ANALOG_IN_MEAN_8_BIT  0xA
/// @brief I2CInOut servant
#define ANALOG_IN_MEAN_10_BIT 0xB
/// @brief I2CInOut servant
#define COUNTER_8_BIT         0xC
/// @brief I2CInOut servant
#define COUNTER_16_BIT        0xD
/// @brief I2CInOut servant
#define COUNTER_RISE_8_BIT    0xE
/// @brief I2CInOut servant
#define COUNTER_RISE_16_BIT   0xF
/// @brief I2CInOut servant
#define PWM_SLOW              0x8
/// @brief I2CInOut servant
#define PWM_FAST              0x9
/// @brief I2CInOut servant
#define FREQ_LOW              0xA
/// @brief I2CInOut servant
#define FREQ_HIGH             0xB
/// @brief I2CInOut servant
#define COUNTER_B_DIR         0xC
/// @brief I2CInOut servant
#define COUNTER_B_DIR_PULLUP  0xD
/// @brief I2CInOut servant
#define COUNTER_MEAN_8_BIT    0xE
/// @brief I2CInOut servant
#define COUNTER_MEAN_16_BIT   0xF

/*!
  @struct I2CInOut
  @author EagleoutIce
  @brief [COPY&PASTE] This is the I2CInOut ghost struct :D
  @note any assignment to Port A won't has anny effect!

  [COPY&PASTE] You can use this class like this:
  @code
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
  ///  @brief I prevent errors!
  inline void read(void);
  ///  @brief I prevent errors!
  inline void changeAddress(optVAL_t);
  ///  @brief I prevent errors!
  inline void changeModes(optVAL_t,optVAL_t,optVAL_t);
#endif
  /**
  @brief this will write values stored in B and C
  @note 404 'A' not found :D
  */
  inline void write(void);
private:
  ///@brief storing value for A-pin (I prevent errors!)
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
  DynamixelBoard servoBoard(board);
  AX12Servo Links(servoBoard,1);
  AX12Servo Rechts(servoBoard,2);

  int main() {
    Links.setPosition(50);
    Rechts.setPosition(10);
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
  AX12Servo(DynamixelBoard dBoard, optVAL_t servoID); //if borders => setPoslimit
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
      @brief I prevent errors!
      @note as there is no rotationMode there is nothing this does
    */
    inline void setSpeed(optVAL_t);
    ///@brief Noone needs the AX-12 Servo LED^^
    ///@todo maybe enable support (?)
    inline void ledOff(void);
    ///@brief Noone needs the AX-12 Servo LED^^
    inline void ledOn(void);
    ///@brief I prevent errors!
    inline void setTorque(uint16_t);
  #endif

    /**
      @brief This moves the Servo to the new position

      This will overwrite storedPos and storedSpeed!
      @param pos the Position the Servo should go to
      @param speed the speed of the Servo
    */
    void setPosition(uint16_t pos, uint16_t speed=0x96);
    /**
      @brief This saves the Servo Position

      Sets the values used by DynamixelBoard::action()
      @param pos the Position the Servo should go to
      @param speed the speed of the Servo
    */
    inline void storePosition(uint16_t pos, uint16_t speed = 0x96);
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
    uint16_t storedPos;
    /**
      @brief stores the Speed of the Servo DynamixelBoard::action()
      @note pls do me a favour and don't change them manually... use AX12Servo::storePosition()
    */
    uint16_t storedSpe;

  //bool posMode; //we don't care wich mode we are in ^^
private:
  ///@brief stores the id of the AX12Servo obejct
  optVAL_t id;
  ///@brief stores the actual pos or move-to pos of the AX12Servo
  uint16_t actPos;
  ///@brief stores the actual 'would use speed' of the AX12Servo
  uint16_t actSpe;



}; //shield //set limits auto register for begin

///@cond
AX12Servo::AX12Servo(void) {}
#if EBOARD_USE_UTILITY > 0x0
void AX12Servo::setID(optVAL_t newID) {this->id = newID;_servoHandler.SetServoLimit(this->id,_servoHandler.upperLimit_temp);
}
void AX12Servo::changeMotorID(optVAL_t newID) {this->id = newID;} //this should change the hardwareaddress...
 //IF needed: _servoHandler.setID(this->id, newID);
void AX12Servo::setPositionMode(void)  {}
void AX12Servo::setSpeedMode(void) {}
void AX12Servo::setSpeed(optVAL_t) {} //i won't use the rotate functions...
void AX12Servo::ledOff(void) {} //noone needs the AX12-Servo LED
void AX12Servo::ledOn(void) {} //really.... noone ^^
void AX12Servo::setTorque(uint16_t) {} //which damn register? xD
#endif

void AX12Servo::setPosition(uint16_t pos, uint16_t speed) {
  #if EBOARD_CLAMP > 0x0
    speed = speed*600/1023 - 300;
    pos   = pos  *600/1023 - 300;
  #endif
    if(speed != actSpe){ _servoHandler.setVelocity(speed); this->actSpe=speed;}
    _servoHandler.write(this->id,pos);
    this->actPos=pos; this->storedPos=pos; this->storedSpe = speed;
  }
void AX12Servo::storePosition(uint16_t pos, uint16_t speed){
  #if EBOARD_CLAMP > 0x0
    speed = speed*600/1023 - 300;
    pos   = pos  *600/1023 - 300;
  #endif
    this->storedPos=pos;this->storedSpe=speed;
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
  DynamixelBoard servoBoard(board);
  AX12Servo Links(servoBoard,1);
  AX12Servo Rechts(servoBoard,2);

  int main() {
    Links.storePosition(50);
    Rechts.storePosition(10);
    servoBoard.action();
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
  ///@brief I prevent errors!
  inline void changeId(optVAL_t);
  ///@brief I prevent errors!
  inline void changeMotorID(optVAL_t);
  ///@brief I prevent errors!
  inline void ledOn(optVAL_t);
  ///@brief I prevent errors!
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
  for(optVAL_t i = 0; i < EBOARD_SPI_SERVO_MAX; i++ ){
    if(this->connected[i] != NULL)
      (*connected[i]).setPosition((*connected[i]).storedPos,(*connected[i]).storedSpe);
  }
}


AX12Servo::AX12Servo(DynamixelBoard dBoard, optVAL_t servoID): id(servoID) {
  #if EBOARD_DEBUG_MODE > 0x0
    assert(servoID<EBOARD_SPI_SERVO_MAX);
  #endif
  this->actSpe=0x96;
  dBoard.connected[servoID] = this;
}
///@endcond

#if EBOARD_BLUETOOTH > 0x0

/*!
  @struct RB14Scan
  @author EagleoutIce
  @brief [COPY&PASTE] [BLUETOOTH] This is the RB14Scan ghost struct :D
  @todo add error explaining and problem resolving page
  [COPY&PASTE] [BLUETOOTH] You can use this class like this:
  @code
  RB14Scan remote;

  int main() {
    int x = remote.channel(0); //stores value, if available in 'x'
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
      @brief this will write a constant string literal to the output
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




#else
  #error This library is build for arduino-devices and should be used only in the Arduino IDE
#endif

#endif
