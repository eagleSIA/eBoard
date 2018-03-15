///EagleoutIce 2018
///IF YOU SEE THIS THIS IS THE UNPROCESSED FILE! GO TO 'SOURCE CODE' IN THE DOCS
/**
 * @file eBoard.h
 */

 #pragma GCC diagnostic push
 #pragma GCC diagnostic ignored "-Wall"
 #pragma GCC diagnostic ignored "-Wextra"
 #pragma pack(push)
 #pragma pack(1) //only works on mega sad^^

/**
 @mainpage eBoard 3.0c - shackle the Arduino!

 @note It was an explicit decision to pack everything needed in one headerfile - readability is granted by the doc
 @note This code was written for the Arduino UNO R3 used with the Smart Servo Shield and allows to copy-paste Code running on a qfixSoccerboard

 @warning This code comes with absolutely <b>no</b> warranty


 @pre This Header file was created to port Codes running on the qfix SoccerBoard [DynamixelBoard etc...] directly onto the Arduino UNO R3 [with Smart Servo Shield].
     \n To use it you'll have to replace all qfix-related header-files [*.h] with the following:
     \n It is possible to add this header as library aswell: ArduinoIDE>Sketch>Include Library>Add .ZIP Library...
     @code
     //manual
     #include "/path/to/eBoard.h" //replace this :D
     //added as library
     #include <eBoard.h>
     @endcode

 If you wan't to use the I2C extensions you should have this two lines the beginning of your code:
 @code
 #define EBOARD_I2C 0x1
 @endcode

 While in development you shouldn't disable any macro...
 If you change to release mode, write (as a minimum) the following before all includings:
 @code
 #define EBOARD_DEBUG_MODE 0x0
 @endcode

 @todo write tutorial and brief introduction page

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
 - #EBOARD_NEO               : 0x1: enable support for Adafruit-NeoPixel-Devices
 \n\n<b> HUGE UPDATE: </b>
 - #EBOARD_GUESSPATH         : 0x0: disable automatic path_guess this will increase the program size [manual includings necessary]

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
 @image html sss.jpeg
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

 - @ref genExpl
 - @ref i2cEx
 - @ref shiftEx
 - @ref blueEx
 - @ref lcdEx
 - @ref portTu
*/
/**
 * @defgroup genExpl [ 🐼 ] GENERAL INTRODUCTION
 *
 */
/**
 @page about_page About
 @brief Something about the Author :D - me ;P
 @author Florian Sihler - EagleoutIce
 @copyright EagleoutIce 2018
 @version 2.3h
 @date 7.2.2018

 @section m1 Motivation
 This header was created to port SoccerBoard-Code to the Arduino UNO R3 [or MEGA R3]\n
 It was written in a funny amount of time (@ref changelog_page) and documented by Doxygen 1.8.15. \n


 @section m2 General Information
 I am an 18-year old programmer and I am coding since i was a kid. \n
 @bug 🐉 Any Errors or Bugs? florian.sihler@web.de



  @image html pp.jpeg

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
    #define EBOARD_I2C 0x1
    #define EBOARD_SHIFT_REGISTER 0x1
    #define EBOARD_BLUETOOTH 0x1
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
    #define EBOARD_BLUETOOTH 0x1
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
    #define EBOARD_I2C 0x1
    #define EBOARD_LCD 0x1
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
  @page changelog_page Changelog
  @brief A short overview about the developing process
  @section ver1 Version 1 - Ollivander 🐁

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

    @subsection su7 Version 2.2b 🐏 - Optimize it [52m]

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


    @subsection su8 Version 2.3h 🐦 - Addition to the family [120m]

    Fixed several wrong numbers [ref BoardVersions]
    It is no obsolete to write includings like
    @code
    #include <WIRE.h>
    @endcode
    eBoard will search and or implement the needed functions itself (controlled with #EBOARD_GUESSPATH)
    \n this behaviour was implemented to shrink programsize and keep functionalities like Wire available to the user

    <b>Added</b>
      - support for the NANO
      - Documentation for the implemented classes and functions (SoftwareSerial, Wire)
      - flexibal pin_out and pin_in size based on arduino
      - arduino adafruit lightstrip support (via NeoPixel)

    <b>Fixes</b>

    - SoccerBoard::analog() range check (swapped ranges)
    - several over/under-flow errors fixed

    @section ver3 Version 3 - Morpheus 🐉

    @subsection su10 Version 3.0c 🐝 - Final touch

    Written many docs and fixed many features

      <b>Added</b>

      - Documentation for all implemented features
      - This code is now a vaild ArduinoIDE library
        \n &nbsp; => <b> including Syntax highlighting </b>

      <b>Changed</b>

        - floating point support for #EBOARD_PWM_SPE
        - cleaned code

      <b>Fixes</b>

      - Path problems => all libs are hardcoded into this doc
      - Removed RB14Scan from eagle_impl

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
         * @macro_def This constant won't be defined by default :D \n This enables you to make use of the async features
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
         * @macro_def This will appear as 0x1 in the docs but the real default value is 0x0
         */
        #define EBOARD_NEO 0x1

        /**
         * @macro_def This isn't defined by default. If you define it the LCD will be addressed with 400kHz. This will only work if every connected device supports 400kHz I²C!
         *
         * @warning Don't do if you don't know!
         */
        #define HIGHSPEED
        /// @brief ignore me ;)
        #define __AVR__
    #endif

    #include <avr/pgmspace.h>
    /**
     * @namespace eagle_impl
     * @brief this namespace contains all the <b>Don't use manually</b> classes ;)
     */
    namespace eagle_impl {}
    using namespace eagle_impl;
    #ifndef EBOARD_GUESSPATH
      /**
       * @macro_def If this is set to 0x1 the library will guess the paths of included libraries based on your operating system
       */
      #define EBOARD_GUESSPATH 0x1
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

    #if EBOARD_I2C > 0x0 && EBOARD_GUESSPATH > 0x0
      ///@cond
      #define twi_h

    #include <inttypes.h>

    //#define ATMEGA8

    #ifndef TWI_FREQ
    #define TWI_FREQ 100000L
    #endif

    #ifndef TWI_BUFFER_LENGTH
    #define TWI_BUFFER_LENGTH 32
    #endif

    #define TWI_READY 0
    #define TWI_MRX   1
    #define TWI_MTX   2
    #define TWI_SRX   3
    #define TWI_STX   4

    #include <math.h>
    #include <stdlib.h>
    #include <inttypes.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <compat/twi.h>

    #ifndef cbi
    #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
    #endif

    #ifndef sbi
    #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
    #endif

    #include "pins_arduino.h"

    static volatile uint8_t twi_state;
    static volatile uint8_t twi_slarw;
    static volatile uint8_t twi_sendStop;
    static volatile uint8_t twi_inRepStart;

    static void (*twi_onSlaveTransmit)(void);
    static void (*twi_onSlaveReceive)(uint8_t*, int);

    static uint8_t twi_masterBuffer[TWI_BUFFER_LENGTH];
    static volatile uint8_t twi_masterBufferIndex;
    static volatile uint8_t twi_masterBufferLength;

    static uint8_t twi_txBuffer[TWI_BUFFER_LENGTH];
    static volatile uint8_t twi_txBufferIndex;
    static volatile uint8_t twi_txBufferLength;

    static uint8_t twi_rxBuffer[TWI_BUFFER_LENGTH];
    static volatile uint8_t twi_rxBufferIndex;

    static volatile uint8_t twi_error;

      void twi_init(void) {
        twi_state = TWI_READY;
        twi_sendStop = true;
        twi_inRepStart = false;

        digitalWrite(SDA, 1);
        digitalWrite(SCL, 1);

        cbi(TWSR, TWPS0);
        cbi(TWSR, TWPS1);
        TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;

        TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
      }

      inline void twi_setAddress(uint8_t address) {
        TWAR = address << 1;
      }

      uint8_t twi_readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop) {
        uint8_t i;

        if(TWI_BUFFER_LENGTH < length) return 0;

        while(TWI_READY != twi_state) continue;

        twi_state = TWI_MRX;
        twi_sendStop = sendStop;

        twi_error = 0xFF;

        twi_masterBufferIndex = 0;
        twi_masterBufferLength = length-1;
        twi_slarw = TW_READ;
        twi_slarw |= address << 1;

        if (true == twi_inRepStart) {
          twi_inRepStart = false;
          TWDR = twi_slarw;
          TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);	// enable INTs, but not START
        }
        else
          TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);

        while(TWI_MRX == twi_state) continue;

        if (twi_masterBufferIndex < length)
          length = twi_masterBufferIndex;

        for(i = 0; i < length; ++i) data[i] = twi_masterBuffer[i];

        return length;
      }

      uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop) {
        uint8_t i;

        if(TWI_BUFFER_LENGTH < length) return 1;

        while(TWI_READY != twi_state) continue;

        twi_state = TWI_MTX;
        twi_sendStop = sendStop;
        twi_error = 0xFF;

        twi_masterBufferIndex = 0;
        twi_masterBufferLength = length;

        for(i = 0; i < length; ++i) twi_masterBuffer[i] = data[i];

        twi_slarw = TW_WRITE;
        twi_slarw |= address << 1;

        if (true == twi_inRepStart) {
          twi_inRepStart = false;
          TWDR = twi_slarw;
          TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);	// enable INTs, but not START
        }
        else
          TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTA);	// enable INTs

        while(wait && (TWI_MTX == twi_state)) continue;

        if (twi_error == 0xFF) return 0;
        else if (twi_error == TW_MT_SLA_NACK) return 2;
        else if (twi_error == TW_MT_DATA_NACK) return 3;
        else return 4;
      }

      uint8_t twi_transmit(const uint8_t* data, uint8_t length) {
        uint8_t i;

        if(TWI_BUFFER_LENGTH < length) return 1;

        if(TWI_STX != twi_state) return 2;

        twi_txBufferLength = length;
        for(i = 0; i < length; ++i) twi_txBuffer[i] = data[i];

        return 0;
      }

      void twi_attachSlaveRxEvent( void (*function)(uint8_t*, int) ) {
        twi_onSlaveReceive = function;
      }

      void twi_attachSlaveTxEvent( void (*function)(void) ) {
        twi_onSlaveTransmit = function;
      }

      void twi_reply(uint8_t ack) {
        if(ack){
          TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
        }else{
      	  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT);
        }
      }


      void twi_stop(void) {
        TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

        while(TWCR & _BV(TWSTO)) continue;

        twi_state = TWI_READY;
      }

      void twi_releaseBus(void){
        TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);
        twi_state = TWI_READY;
      }

      ISR(TWI_vect) {
        switch(TW_STATUS){
          case TW_START:
          case TW_REP_START:
            TWDR = twi_slarw;
            twi_reply(1);
            break;

          case TW_MT_SLA_ACK:
          case TW_MT_DATA_ACK:
            if(twi_masterBufferIndex < twi_masterBufferLength){
              TWDR = twi_masterBuffer[twi_masterBufferIndex++];
              twi_reply(1);
            }else{
            	if (twi_sendStop) twi_stop();
            	else {
            	  twi_inRepStart = true;
            	  TWCR = _BV(TWINT) | _BV(TWSTA)| _BV(TWEN) ;
            	  twi_state = TWI_READY;
            	}
            }
            break;
          case TW_MT_SLA_NACK:
            twi_error = TW_MT_SLA_NACK;
            twi_stop();
            break;
          case TW_MT_DATA_NACK:
            twi_error = TW_MT_DATA_NACK;
            twi_stop();
            break;
          case TW_MT_ARB_LOST:
            twi_error = TW_MT_ARB_LOST;
            twi_releaseBus();
            break;
          case TW_MR_DATA_ACK:
            twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
          case TW_MR_SLA_ACK:
            if(twi_masterBufferIndex < twi_masterBufferLength) twi_reply(1);
            else twi_reply(0);
            break;
          case TW_MR_DATA_NACK:
            twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
          	if (twi_sendStop) twi_stop();
          	else {
          	  twi_inRepStart = true;
          	  TWCR = _BV(TWINT) | _BV(TWSTA)| _BV(TWEN) ;
          	  twi_state = TWI_READY;
          	}
        	break;
          case TW_MR_SLA_NACK:
            twi_stop();
            break;
          case TW_SR_SLA_ACK:
          case TW_SR_GCALL_ACK:
          case TW_SR_ARB_LOST_SLA_ACK:
          case TW_SR_ARB_LOST_GCALL_ACK:
            twi_state = TWI_SRX;
            twi_rxBufferIndex = 0;
            twi_reply(1);
            break;
          case TW_SR_DATA_ACK:
          case TW_SR_GCALL_DATA_ACK:
            if(twi_rxBufferIndex < TWI_BUFFER_LENGTH){
              twi_rxBuffer[twi_rxBufferIndex++] = TWDR;
              twi_reply(1);
            } else twi_reply(0);

            break;
          case TW_SR_STOP:
            if(twi_rxBufferIndex < TWI_BUFFER_LENGTH) twi_rxBuffer[twi_rxBufferIndex] = '\0';
            twi_stop();
            twi_onSlaveReceive(twi_rxBuffer, twi_rxBufferIndex);
            twi_rxBufferIndex = 0;
            twi_releaseBus();
            break;
          case TW_SR_DATA_NACK:
          case TW_SR_GCALL_DATA_NACK:
            twi_reply(0);
            break;
          case TW_ST_SLA_ACK:
          case TW_ST_ARB_LOST_SLA_ACK:
            twi_state = TWI_STX;
            twi_txBufferIndex = 0;
            twi_txBufferLength = 0;
            twi_onSlaveTransmit();
            if(0 == twi_txBufferLength){
              twi_txBufferLength = 1;
              twi_txBuffer[0] = 0x00;
            }
          case TW_ST_DATA_ACK:
            TWDR = twi_txBuffer[twi_txBufferIndex++];
            if(twi_txBufferIndex < twi_txBufferLength) twi_reply(1);
            else twi_reply(0);
            break;
          case TW_ST_DATA_NACK:
          case TW_ST_LAST_DATA:
            twi_reply(1);
            twi_state = TWI_READY;
            break;

          case TW_NO_INFO:
            break;
          case TW_BUS_ERROR:
            twi_error = TW_BUS_ERROR;
            twi_stop();
            break;
        }
      }
      ///@endcond
      #include <inttypes.h>
      #include "Stream.h"

      #define BUFFER_LENGTH 32
      namespace eagle_impl {
      /*!
            @class TwoWire

            @authors Nicholas Zambetti for Arduino
            @authors [mod] Todd Krein


            @brief This is used to avoid path resolving issues and defines the common known Arduino Wire-Interface
            \n &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <b>Don't use manually</b>


            @copyright 2006 GNU Lesser General Public License 2.1 as published by the Free Software Foundation

            @note this code was documented and modified by EagleoutIce in 2018 for custom use!

        */
        class TwoWire : public Stream {
          private:
            ///@brief this defines the rxBuffer used to enable delayed read
            static uint8_t rxBuffer[];
            ///@brief this defines the rxBuffer Index - current position in rxBuffer array
            static uint8_t rxBufferIndex;
            ///@brief this defines the length of rxBuffer
            static uint8_t rxBufferLength;

            ///@brief this defines the txAddress the transmitting Dta
            static uint8_t txAddress;
            ///@brief this defines the txBuffer used to enable delayed read
            static uint8_t txBuffer[];
            ///@brief this defines the txBuffer Index - current position in txBuffer array
            static uint8_t txBufferIndex;
            ///@brief this defines the length of txBuffer
            static uint8_t txBufferLength;

            ///@brief 'boolean' value. Set to 1 if transmitting => in master write mode
            static uint8_t transmitting;
            ///@brief twi slave [Tx]transmitting-event user def handler
            static void (*user_onRequest)(void);
            /**
             * @brief twi slave [Rx]receive-event user def handler
             * @param numBytes amount of received bytes stored in rxBuffer
             */
            static void (*user_onReceive)(int numBytes);
            ///@brief twi slave [Tx]transmitting-event handler
            static void onRequestService(void);
            /**
             * @brief twi slave [Rx]receive-event handler
             * @param inBytes array of receive Bytes
             * @param numBytes length of inBytes array
             */
            static void onReceiveService(uint8_t* inBytes, int numBytes);

          public:
            ///@brief The constructor of the TwoWire class
            TwoWire();
            ///@brief begin the TwoWire communcation without any data set
            void begin();
            /**
             * @brief begin the TwoWire communication with a special address
             * @param address the address the TwoWire Interface should use
             */
            void begin(uint8_t address);
            /**
             * @brief begin the TwoWire communication with a special address
             * @param address the address the TwoWire Interface should use
             * @note this will cast the address to an uint8_t type and call the same TwoWire::begin()
             */
            inline void begin(int address);
            /**
             * @brief this will start a new transmission to a specific address => master mode
             * @param address the address to talk to
             */
            void beginTransmission(uint8_t address);
            /**
             * @brief this will start a new transmission to a specific address => master mode
             * @param address the address to talk to
             * @note this will cast the address to an uint8_t type and call the same TwoWire::beginTransmission()
             */
            inline void beginTransmission(int address);
            /**
             * @brief this will end the transmission and send the STOP-sequence
             * @returns The following unsigned values:
             *  - 0 in case of success
             *  - 1 if data was too long for transmit buffer
             *  - 2 if received a NACK on transmit of address
             *  - 3 if received a NACK on transmit of data
             *  - 4 if an 'other'/unknown error occured
             * @note this will call TwoWire::endTransmission() with 'true' as param internally
             */
            inline uint8_t endTransmission(void);
            /**
             * @brief this will end the transmission and send the STOP-sequence dependent on sendStop
             * @param sendStop set this to true (0x1) if STOP should be send. \n Some devices will behave oddly if you set this to false (0x0)!
             * @returns The following unsigned values:
             *  - 0 in case of success
             *  - 1 if data was too long for transmit buffer
             *  - 2 if received a NACK on transmit of address
             *  - 3 if received a NACK on transmit of data
             *  - 4 if an 'other'/unknown error occured
             */
            uint8_t endTransmission(uint8_t sendStop);
            /**
             * @brief this will read a specific <i> quantity </i> of bytes from a specific <i> address </i>
             * @param address the address to read from
             * @param quantity the amount if bytes to read
             * @return the amount of read bytes
             * @note this will call the 3*uint8_t (sendStop = true) variant of TwoWire::requestFrom() internally
             */
            inline uint8_t requestFrom(uint8_t address, uint8_t quantity);
            /**
             * @brief this will read a specific <i> quantity </i> of bytes from a specific <i> address </i>
             * @param address the address to read from
             * @param quantity the amount if bytes to read
             * @param sendStop set this to true (0x1) if STOP should be send. \n Some devices will behave oddly if you set this to false (0x0)!
             * @return the amount of read bytes
             */
            uint8_t requestFrom(uint8_t address , uint8_t quantity, uint8_t sendStop);
            /**
             * @brief this will read a specific <i> quantity </i> of bytes from a specific <i> address </i>
             * @param address the address to read from
             * @param quantity the amount if bytes to read
             * @return the amount of read bytes
             * @note this will call the 3*uint8_t (sendStop = true) variant of TwoWire::requestFrom() internally
             */
            inline uint8_t requestFrom(int address, int quantity);
            /**
             * @brief this will read a specific <i> quantity </i> of bytes from a specific <i> address </i>
             * @param address the address to read from
             * @param quantity the amount if bytes to read
             * @param sendStop set this to true (0x1) if STOP should be send. \n Some devices will behave oddly if you set this to false (0x0)!
             * @return the amount of read bytes
             * @note this will call the 3*uint8_t (sendStop = true) variant of TwoWire::requestFrom() internally
             */
            inline uint8_t requestFrom(int address, int quantity, int sendStop);
            /**
             * @brief this will write a single unsigned 8-bit value to address
             * @note this has to be called <b> after </b> TwoWire::beginTransmission() [or in slave tx event callback]
             * @param data the data that should be send if in master-mode it will be stored in buffer!
             * @returns
             *  - 0 in case of an overflow
             *  - 1 when everything worked fine ;)
             */
            virtual size_t write(uint8_t data);
            /**
             * @brief this will write an array of unsigned 8-bit values to address
             * @note this has to be called <b> after </b> TwoWire::beginTransmission() [or in slave tx event callback]
             * @param data the data array that should be send if in master-mode it will be stored in buffer!
             * @param quantity the length of the array
             * @returns the quantity sent
             */
            virtual size_t write(const uint8_t *data, size_t quantity);
            /**
             * @brief this will return the amount of rxBuffer left
             * @returns (rxBufferLength-rxBufferIndex)
             */
            virtual int available(void);
            /**
             * @brief this will read a single byte from rxBuffer and increment the Index
             * @note this has to be called <b> after </b> TwoWire::requestFrom() [or in slave rx event callback]
             * @returns the read value (-1 if failed)
             */
            virtual int read(void);
            /**
             * @brief this will read a single byte from rxBuffer without increment the Index
             * @note this has to be called <b> after </b> TwoWire::requestFrom() [or in slave rx event callback]
             * @returns the read value (-1 if failed)
             */
            virtual int peek(void);
            /// @brief as this isn't implemented in the offical Wire library, this does <i> nothing </i> xD
        	  virtual void flush(void);
            /**
             * @brief this will set the user_onReceive method
             * @param function the function to link
             *
             * For further uses see TwoWire::user_onReceive()
             */
            void onReceive( void (*function)(int) );
            /**
             * @brief this will set the user_onRequest method
             * @param function the function to link
             *
             * For further uses see TwoWire::user_onRequest()
             */
            void onRequest( void (*function)(void) );

            /* Removed due to: not needed
              inline size_t write(unsigned long n) { return write((uint8_t)n); }
              inline size_t write(long n) { return write((uint8_t)n); }
              inline size_t write(unsigned int n) { return write((uint8_t)n); }
              inline size_t write(int n) { return write((uint8_t)n); }
            */
            using Print::write;
        };
        }
        extern "C" {
          #include <stdlib.h>
          #include <string.h>
          #include <inttypes.h>
          //#include "twi.h"
        }

        ///@cond
        uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
        uint8_t TwoWire::rxBufferIndex = 0;
        uint8_t TwoWire::rxBufferLength = 0;

        uint8_t TwoWire::txAddress = 0;
        uint8_t TwoWire::txBuffer[BUFFER_LENGTH];
        uint8_t TwoWire::txBufferIndex = 0;
        uint8_t TwoWire::txBufferLength = 0;

        uint8_t TwoWire::transmitting = 0;
        void (*TwoWire::user_onRequest)(void);
        void (*TwoWire::user_onReceive)(int);

        TwoWire::TwoWire() {}

        void TwoWire::begin(void) {
          rxBufferIndex = 0;
          rxBufferLength = 0;

          txBufferIndex = 0;
          txBufferLength = 0;

          twi_init();
        }

        void TwoWire::begin(uint8_t address) {
          twi_setAddress(address);
          twi_attachSlaveTxEvent(onRequestService);
          twi_attachSlaveRxEvent(onReceiveService);
          begin();
        }

        void TwoWire::begin(int address) {
          begin((uint8_t)address);
        }

        uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
          if(quantity > BUFFER_LENGTH){
            quantity = BUFFER_LENGTH;
          }
          uint8_t read = twi_readFrom(address, rxBuffer, quantity, sendStop);
          rxBufferIndex = 0;
          rxBufferLength = read;

          return read;
        }

        uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
          return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
        }

        uint8_t TwoWire::requestFrom(int address, int quantity) {
          return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
        }

        uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {
          return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
        }

        void TwoWire::beginTransmission(uint8_t address) {
          transmitting = 1;
          txAddress = address;
          txBufferIndex = 0;
          txBufferLength = 0;
        }

        void TwoWire::beginTransmission(int address) {
          beginTransmission((uint8_t)address);
        }

        uint8_t TwoWire::endTransmission(uint8_t sendStop) {
          int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, sendStop);
          txBufferIndex = 0;
          txBufferLength = 0;
          transmitting = 0;
          return ret;
        }

        uint8_t TwoWire::endTransmission(void){
          return endTransmission(true);
        }

        size_t TwoWire::write(uint8_t data) {
          if(transmitting) {
            if(txBufferLength >= BUFFER_LENGTH) {
              setWriteError();
              return 0;
            }
            txBuffer[txBufferIndex] = data;
            ++txBufferIndex;
            txBufferLength = txBufferIndex;
          }else{
            twi_transmit(&data, 1);
          }
          return 1;
        }

        size_t TwoWire::write(const uint8_t *data, size_t quantity) {
          if(transmitting){
            for(size_t i = 0; i < quantity; ++i) {
              write(data[i]);
            }
          }else{
            twi_transmit(data, quantity);
          }
          return quantity;
        }

        int TwoWire::available(void) {
          return rxBufferLength - rxBufferIndex;
        }

        int TwoWire::read(void) {
          int value = -1;

          if(rxBufferIndex < rxBufferLength) {
            value = rxBuffer[rxBufferIndex];
            ++rxBufferIndex;
          }

          return value;
        }

        int TwoWire::peek(void) {
          int value = -1;

          if(rxBufferIndex < rxBufferLength) {
            value = rxBuffer[rxBufferIndex];
          }

          return value;
        }

        void TwoWire::flush(void) {
          // XXX: to be implemented.
        }

        void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes) {
          if(!user_onReceive){
            return;
          }

          if(rxBufferIndex < rxBufferLength) {
            return;
          }

          for(uint8_t i = 0; i < numBytes; ++i) {
            rxBuffer[i] = inBytes[i];
          }
          rxBufferIndex = 0;
          rxBufferLength = numBytes;
          user_onReceive(numBytes);
        }

        void TwoWire::onRequestService(void) {
          if(!user_onRequest) {
            return;
          }

          txBufferIndex = 0;
          txBufferLength = 0;
          user_onRequest();
        }

        void TwoWire::onReceive( void (*function)(int) ) {
          user_onReceive = function;
        }

        void TwoWire::onRequest( void (*function)(void) ) {
          user_onRequest = function;
        }

        ///@endcond

      ///@brief this is the well-known Arduino Wire Interface, just a little bit 'modified' ;P
      TwoWire Wire = TwoWire();

      #endif
      /**
       * @macro_def this has to be enabled to use the shield
       */
      #ifndef EBOARD_USE_SPI
          #define EBOARD_USE_SPI 0x1
      #endif
    #if EBOARD_USE_SPI > 0x0
      /// @macro_def the header macro to assure that there is a SPIClass available
      #define _SPI_H_INCLUDED

      #include <stdio.h>
      /// @macro_def this will set the clock devider to 4
      #define SPI_CLOCK_DIV4 0x00
      /// @macro_def this will set the clock devider to 16
      #define SPI_CLOCK_DIV16 0x01
      /// @macro_def this will set the clock devider to 64
      #define SPI_CLOCK_DIV64 0x02
      /// @macro_def this will set the clock devider to 128
      #define SPI_CLOCK_DIV128 0x03
      /// @macro_def this will set the clock devider to 2
      #define SPI_CLOCK_DIV2 0x04
      /// @macro_def this will set the clock devider to 8
      #define SPI_CLOCK_DIV8 0x05
      /// @macro_def this will set the clock devider to 32
      #define SPI_CLOCK_DIV32 0x06

      /// @macro_def this will set the mode to 0
      #define SPI_MODE0 0x00
      /// @macro_def this will set the mode to 1
      #define SPI_MODE1 0x04
      /// @macro_def this will set the mode to 2
      #define SPI_MODE2 0x08
      /// @macro_def this will set the mode to 3
      #define SPI_MODE3 0x0C

      /// @macro_def the mode mask to apply correct mode
      #define SPI_MODE_MASK 0x0C
      /// @macro_def the clock mask to apply the correct devider
      #define SPI_CLOCK_MASK 0x03
      /// @macro_def the scaled clock mask to apply the correct devider
      #define SPI_2XCLOCK_MASK 0x01
      namespace eagle_impl {
      /*!
          @struct eagle_impl::SPIClass

          @author Christian Maglie

          @copyright 2006 GNU Lesser General Public License 2.1 as published by the Free Software Foundation

          @brief [SPI] This is used to avoid path resolving issues and defines the common known Arduino SPI interface
          \n &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <b>Don't use manually</b>

          @note for meanings of dividers and modes etc... look here: https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus
          @note this code was documented and modified by EagleoutIce in 2018 for custom use!
      */
        struct SPIClass {
          /**
           * @brief this will send a single bite via the SPI connection
           * @param _data the byte to send
           * @return the received byte
           */
          inline static byte transfer(byte _data);
          /**
           * @brief enables the interrupt feature
           */
          inline static void attachInterrupt(void);
          /**
           * @brief disables the interrupt feature
           */
          inline static void detachInterrupt(void); // Default
          /**
           * @brief this will setup everything for SPI connection
           */
          static void begin(void); // Default
          /**
           * @brief this will end the SPI connection
           */
          inline static void end(void);
          /**
           * @brief this will set the BitOrder
           * @param bitOrder LSBFIRST or MSBFIRST
           */
          inline static void setBitOrder(uint8_t bitOrder);
          /**
           * @brief this will set the Data transfer mode
           * @param mode the mode -- shouldn't be changed
           */
          inline static void setDataMode(uint8_t mode);
          /**
           * @brief this will change the clock devider the
           * @param rate the rate the connection is running on -- shouldn't be changed
           */
          inline static void setClockDivider(uint8_t rate);
        };
      }
      ///@cond
      byte SPIClass::transfer(byte _data) {
        SPDR = _data;
        while (!(SPSR & _BV(SPIF)));
        return SPDR;
      }

      void SPIClass::attachInterrupt() { SPCR |=  _BV(SPIE);}

      void SPIClass::detachInterrupt() { SPCR &= ~_BV(SPIE);}

      void SPIClass::begin() {
        digitalWrite(SS, HIGH);
        pinMode(SS, OUTPUT); //doesn't block common use as_ OUTPUT!
        SPCR |= _BV(MSTR);
        SPCR |= _BV(SPE);
        pinMode(SCK, OUTPUT);
        pinMode(MOSI, OUTPUT);
      }

      void SPIClass::end() {SPCR &= ~_BV(SPE);}

      void SPIClass::setBitOrder(uint8_t bitOrder) {
        if(bitOrder == LSBFIRST) SPCR |= _BV(DORD);
        else SPCR &= ~(_BV(DORD));
      }

      void SPIClass::setDataMode(uint8_t mode) { SPCR = (SPCR & ~SPI_MODE_MASK) | mode; }

      void SPIClass::setClockDivider(uint8_t rate) {
        SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
        SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((rate >> 2) & SPI_2XCLOCK_MASK);
      }
      ///@endcond

      SPIClass SPI;

    #endif
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
     * @macro_def this will disable soccerBoard class DynamixelBoard etc!
     */
    #ifndef EBOARD_NANO
      #define EBOARD_NANO 0x0
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


    #ifndef EBOARD_NEO
      /**
       * @macro_def set this to 0x1 to enable bluetooth support
       */
      #define EBOARD_NEO 0x0
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
     * @macro_def this is the RX-Pin reserved for bluetooth communication
     */
    #ifndef PIN_BLUETOOTH_RX
        #if defined(__AVR_ATmega2560__)
            #define PIN_BLUETOOTH_RX 0x13 // 19
        #else
            #define PIN_BLUETOOTH_RX 0x2
        #endif
    #endif

    /**
     * @macro_def this is the TX-Pin reserved for bluetooth communication
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
      #if EBOARD_GUESSPATH > 0x0
         //again to resolve including errors we'll include the SoftwareSerial cpp file

         #define _SS_MAX_RX_BUFF 64 // RX buffer size
         #ifndef GCC_VERSION
            #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
         #endif
         namespace eagle_impl {
         /*!
               @class SoftwareSerial

               This class was known as NewSoftSerial and renamend to SoftwareSerial for consistent naming

               @authors arduiniana (core)
               @authors ladyada
               @authors Mikel Hart
               @authors Paul Stoffregen
               @authors Garrett Mace
               @authors Brett Hagman

               @brief This is used to avoid path resolving issues and defines the common known Arduino SoftwareSerial interface only enabled on UNO and NANO (specific, ATmega328P based-plattforms)
               \n &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <b>Don't use manually</b>


               @copyright 2006 GNU Lesser General Public License 2.1 as published by the Free Software Foundation

               @note this code was documented and modified by EagleoutIce in 2018 for custom use! [Kept _DEBUG functionality]

          */
         class SoftwareSerial : public Stream {
         private:
           ///@brief the id of the receive pin
           uint8_t _receivePin;
           ///@brief the pin mask to directly read from register (Rx)
           uint8_t _receiveBitMask;
           ///@brief the register the reveice pin is located on
           volatile uint8_t *_receivePortRegister;
           ///@brief the pin mask to address the tx pin
           uint8_t _transmitBitMask;
           ///@brief the register the reveice pin is located on
           volatile uint8_t *_transmitPortRegister;

           ///@brief the rx center delay
           uint16_t _rx_delay_centering;
           ///@brief the rx startbit delay
           uint16_t _rx_delay_intrabit;
           ///@brief the rx stopbit dely
           uint16_t _rx_delay_stopbit;
           ///@brief the (generic) tx delay
           uint16_t _tx_delay;

           ///@brief determining if an _buffer_overflow occured
           uint16_t _buffer_overflow:1;
           ///@brief determining if all pin reads etc whould be inverted (e.g. no pullup on rx);
           uint16_t _inverse_logic:1;
           ///@brief the buffer for rxBuffer
           static char _receive_buffer[_SS_MAX_RX_BUFF];
           ///@brief size of rxBuffer
           static volatile uint8_t _receive_buffer_tail;
           ///@brief current location in rxBuffer
           static volatile uint8_t _receive_buffer_head;
           ///@brief the active SoftwareSerial object to operate on
           static SoftwareSerial *active_object;

           ///@brief private receive routine called each time interrupt handler gets triggered
           void recv(void);
           /**
            * @brief simple routine to read the rxPin by registers
            * @returns the (bool) value on current pin
            */
           inline uint8_t rx_pin_read(void);
           /**
            * @brief writes a bool value on the txPin by registers
            * @param pin_state the state the pin should be assigned to
            */
           inline void tx_pin_write(uint8_t pin_state);
           /**
            * @brief sets a specific pin to be 'the chosen one' as a txPin
            * @param transmitPin the Pin-Id of the pin to setup
            */
           void setTX(uint8_t transmitPin);
           /**
            * @brief sets a specific pin to be 'the chosen one' as a rxPin
            * @param receivePin the Pin-Id of the pin to setup
            */
           void setRX(uint8_t receivePin);
           /**
            * @brief apply a specific delay to achieve higher precision
            * @param delay the desired delay
            */
           static inline void tunedDelay(uint16_t delay);

         public:
           // public methods
           /**
            * @brief the constructor for the SoftwareSerial object
            * @param receivePin the destined rx Pin
            * @param transmitPin the destined tx Pin
            * @param inverse_logic true if you wan't to have no pullups and inverted com logic
            */
           SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
           /**
            * @brief the destructor of the SoftwareSerial object
            *
            * This calls SoftwareSerial::end() internal and assures a sufficent termination
            */
           ~SoftwareSerial(void);
           /**
            * @brief the start function to setup delay_values etc.
            * @param speed the communcation should work at \n possible values: \n
            *  - &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 300 (baud)
            *  - &nbsp; &nbsp; &nbsp; &nbsp; 1200 (baud)
            *  - &nbsp; &nbsp; &nbsp; &nbsp; 2400 (baud)
            *  - &nbsp; &nbsp; &nbsp; &nbsp; 4800 (baud)
            *  - &nbsp; &nbsp; &nbsp; &nbsp; 9600 (baud) [common]
            *  - &nbsp; &nbsp; &nbsp; 14400 (baud)
            *  - &nbsp; &nbsp; &nbsp; 19200 (baud)
            *  - &nbsp; &nbsp; &nbsp; 28800 (baud)
            *  - &nbsp; &nbsp; &nbsp; 38400 (baud)
            *  - &nbsp; &nbsp; &nbsp; 57600 (baud)
            *  - &nbsp; &nbsp; 115200 (baud)
            */
           void begin(long speed);
           /**
            * @brief sets the SoftwareSerial object to be the listening one gaining control over the buffers etc.
            * @returns true if it replaces another object (can be no object)
            */
           bool listen(void);
           /// @brief ends communcation on the rx pin
           inline void end(void);
           /**
            * @brief checks if this object is the listening object
            * @returns true if the object is the listening object
            */
           inline bool isListening(void);
           /**
            * @brief returns the current overflow flag and disables it
            * @return the current overflow flag
            */
           inline bool overflow(void);
           /**
            * @brief reads the actual pointed rxBuffer element without dropping it
            * @returns the read value (-1 if fails)
            */
           int peek(void);
           /**
            * @brief writes a specific value to the tx register
            * @param byte the byte to write
            * @returns 0 if there's an error with the delay
            * @returns 1 if the writing was successful
            */
           virtual size_t write(uint8_t byte);
           /**
            * @brief reads the actual pointed rxBuffer top element
            * @returns the read value (-1 if fails)
            */
           virtual int read(void);
           /**
            * @brief checks if there is data to read available
            * @returns 0 if there's no Data available or the device isn't listening
            */
           virtual int available(void);
           /**
            * @brief resets the position in buffer and the buffer itself if the object is listening
            */
           virtual void flush(void);
           //used to save codespace
           using Print::write;
           ///@brief used to handle interrupts on active listening object
           static inline void handle_interrupt(void);
         };
       }
         ///@cond

         bool SoftwareSerial::isListening(void) {
            return this == active_object;
         }

         bool SoftwareSerial::overflow(void) {
            bool ret = _buffer_overflow;
            _buffer_overflow = false;
            return ret;
         }
         /* was a workaround for arduino 0012 but not needed
          #undef int
          #undef char
          #undef long
          #undef byte
          #undef float
          #undef abs
          #undef round
         */
         #if EBOARD_DEBUG_MODE > 0x0
          #define _DEBUG 0
          #define _DEBUG_PIN1 11
          #define _DEBUG_PIN2 13
         #endif
         typedef struct _DELAY_TABLE {
           long baud;
           unsigned short rx_delay_centering;
           unsigned short rx_delay_intrabit;
           unsigned short rx_delay_stopbit;
           unsigned short tx_delay;
         } DELAY_TABLE;

         #if F_CPU == 16000000

         static const DELAY_TABLE PROGMEM table[] = {
           //  baud    rxcenter   rxintra    rxstop    tx
           { 115200,   1,         17,        17,       12,    },
           { 57600,    10,        37,        37,       33,    },
           { 38400,    25,        57,        57,       54,    },
           { 31250,    31,        70,        70,       68,    },
           { 28800,    34,        77,        77,       74,    },
           { 19200,    54,        117,       117,      114,   },
           { 14400,    74,        156,       156,      153,   },
           { 9600,     114,       236,       236,      233,   },
           { 4800,     233,       474,       474,      471,   },
           { 2400,     471,       950,       950,      947,   },
           { 1200,     947,       1902,      1902,     1899,  },
           { 600,      1902,      3804,      3804,     3800,  },
           { 300,      3804,      7617,      7617,     7614,  },
         };

         const int XMIT_START_ADJUSTMENT = 5;

         #elif F_CPU == 8000000

         static const DELAY_TABLE table[] PROGMEM = {
           //  baud    rxcenter    rxintra    rxstop  tx
           { 115200,   1,          5,         5,      3,      },
           { 57600,    1,          15,        15,     13,     },
           { 38400,    2,          25,        26,     23,     },
           { 31250,    7,          32,        33,     29,     },
           { 28800,    11,         35,        35,     32,     },
           { 19200,    20,         55,        55,     52,     },
           { 14400,    30,         75,        75,     72,     },
           { 9600,     50,         114,       114,    112,    },
           { 4800,     110,        233,       233,    230,    },
           { 2400,     229,        472,       472,    469,    },
           { 1200,     467,        948,       948,    945,    },
           { 600,      948,        1895,      1895,   1890,   },
           { 300,      1895,       3805,      3805,   3802,   },
         };

         const int XMIT_START_ADJUSTMENT = 4;

         #elif F_CPU == 20000000

         static const DELAY_TABLE PROGMEM table[] = {
           //  baud    rxcenter    rxintra    rxstop  tx
           { 115200,   3,          21,        21,     18,     },
           { 57600,    20,         43,        43,     41,     },
           { 38400,    37,         73,        73,     70,     },
           { 31250,    45,         89,        89,     88,     },
           { 28800,    46,         98,        98,     95,     },
           { 19200,    71,         148,       148,    145,    },
           { 14400,    96,         197,       197,    194,    },
           { 9600,     146,        297,       297,    294,    },
           { 4800,     296,        595,       595,    592,    },
           { 2400,     592,        1189,      1189,   1186,   },
           { 1200,     1187,       2379,      2379,   2376,   },
           { 600,      2379,       4759,      4759,   4755,   },
           { 300,      4759,       9523,      9523,   9520,   },
         };

         const int XMIT_START_ADJUSTMENT = 6;

         #else
          #error This version of SoftwareSerial supports only 20, 16 and 8MHz processors
         #endif

         SoftwareSerial *SoftwareSerial::active_object = 0;
         char SoftwareSerial::_receive_buffer[_SS_MAX_RX_BUFF];
         volatile uint8_t SoftwareSerial::_receive_buffer_tail = 0;
         volatile uint8_t SoftwareSerial::_receive_buffer_head = 0;
         #if EBOARD_DEBUG_MODE > 0x0
           inline void DebugPulse(uint8_t pin, uint8_t count) {
           #if _DEBUG
             volatile uint8_t *pport = portOutputRegister(digitalPinToPort(pin));

             uint8_t val = *pport;
             while (count--)
             {
               *pport = val | digitalPinToBitMask(pin);
               *pport = val;
             }
           #endif
           }
         #endif
         inline void SoftwareSerial::tunedDelay(uint16_t delay) {
           uint8_t tmp=0;

           asm volatile("sbiw    %0, 0x01 \n\t"
             "ldi %1, 0xFF \n\t"
             "cpi %A0, 0xFF \n\t"
             "cpc %B0, %1 \n\t"
             "brne .-10 \n\t"
             : "+r" (delay), "+a" (tmp)
             : "0" (delay)
             );
         }

         bool SoftwareSerial::listen() {
           if (active_object != this)
           {
             _buffer_overflow = false;
             uint8_t oldSREG = SREG;
             cli();
             _receive_buffer_head = _receive_buffer_tail = 0;
             active_object = this;
             SREG = oldSREG;
             return true;
           }

           return false;
         }

         void SoftwareSerial::recv() {

           #if GCC_VERSION < 40302
             asm volatile(
               "push r18 \n\t"
               "push r19 \n\t"
               "push r20 \n\t"
               "push r21 \n\t"
               "push r22 \n\t"
               "push r23 \n\t"
               "push r26 \n\t"
               "push r27 \n\t"
               ::);
           #endif

           uint8_t d = 0;

           if (_inverse_logic ? rx_pin_read() : !rx_pin_read()) {
             // Wait approximately 1/2 of a bit width to "center" the sample
             tunedDelay(_rx_delay_centering);
             #if EBOARD_DEBUG_MODE > 0x0
              DebugPulse(_DEBUG_PIN2, 1);
             #endif
             // Read each of the 8 bits
             for (uint8_t i=0x1; i; i <<= 1)
             {
               tunedDelay(_rx_delay_intrabit);
               #if EBOARD_DEBUG_MODE > 0x0
                DebugPulse(_DEBUG_PIN2, 1);
               #endif
               uint8_t noti = ~i;
               if (rx_pin_read())
                 d |= i;
               else
                 d &= noti;
             }

             // skip the stop bit
             tunedDelay(_rx_delay_stopbit);
             #if EBOARD_DEBUG_MODE > 0x0
              DebugPulse(_DEBUG_PIN2, 1);
             #endif
             if (_inverse_logic)
               d = ~d;

             if ((_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF != _receive_buffer_head) {
               _receive_buffer[_receive_buffer_tail] = d; // save new byte
               _receive_buffer_tail = (_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF;
             }
             else {
               #if EBOARD_DEBUG_MODE > 0x0
                #if _DEBUG // for scope: pulse pin as overflow indictator
                  DebugPulse(_DEBUG_PIN1, 1);
                #endif
               #endif
               _buffer_overflow = true;
             }
           }

         #if GCC_VERSION < 40302
           asm volatile(
             "pop r27 \n\t"
             "pop r26 \n\t"
             "pop r23 \n\t"
             "pop r22 \n\t"
             "pop r21 \n\t"
             "pop r20 \n\t"
             "pop r19 \n\t"
             "pop r18 \n\t"
             ::);
         #endif
         }

         void SoftwareSerial::tx_pin_write(uint8_t pin_state) {
           if (pin_state == LOW)
             *_transmitPortRegister &= ~_transmitBitMask;
           else
             *_transmitPortRegister |= _transmitBitMask;
         }

         uint8_t SoftwareSerial::rx_pin_read() {
           return *_receivePortRegister & _receiveBitMask;
         }

         inline void SoftwareSerial::handle_interrupt() {
           if (active_object) {
             active_object->recv();
           }
         }

         #if defined(PCINT0_vect)
           ISR(PCINT0_vect) {
             SoftwareSerial::handle_interrupt();
           }
         #endif

         #if defined(PCINT1_vect)
           ISR(PCINT1_vect) {
             SoftwareSerial::handle_interrupt();
           }
         #endif

         #if defined(PCINT2_vect)
           ISR(PCINT2_vect) {
             SoftwareSerial::handle_interrupt();
           }
         #endif

         #if defined(PCINT3_vect)
           ISR(PCINT3_vect) {
             SoftwareSerial::handle_interrupt();
           }
         #endif

         SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */) :
           _rx_delay_centering(0),
           _rx_delay_intrabit(0),
           _rx_delay_stopbit(0),
           _tx_delay(0),
           _buffer_overflow(false),
           _inverse_logic(inverse_logic) {
           setTX(transmitPin);
           setRX(receivePin);
         }

         SoftwareSerial::~SoftwareSerial() {
           end();
         }

         void SoftwareSerial::setTX(uint8_t tx) {
           pinMode(tx, OUTPUT);
           digitalWrite(tx, HIGH);
           _transmitBitMask = digitalPinToBitMask(tx);
           uint8_t port = digitalPinToPort(tx);
           _transmitPortRegister = portOutputRegister(port);
         }

         void SoftwareSerial::setRX(uint8_t rx) {
           pinMode(rx, INPUT);
           if (!_inverse_logic)
             digitalWrite(rx, HIGH);
           _receivePin = rx;
           _receiveBitMask = digitalPinToBitMask(rx);
           uint8_t port = digitalPinToPort(rx);
           _receivePortRegister = portInputRegister(port);
         }

         void SoftwareSerial::begin(long speed) {
           _rx_delay_centering = _rx_delay_intrabit = _rx_delay_stopbit = _tx_delay = 0;

           for (unsigned i=0; i<sizeof(table)/sizeof(table[0]); ++i) {
             long baud = pgm_read_dword(&table[i].baud);
             if (baud == speed) {
               _rx_delay_centering = pgm_read_word(&table[i].rx_delay_centering);
               _rx_delay_intrabit = pgm_read_word(&table[i].rx_delay_intrabit);
               _rx_delay_stopbit = pgm_read_word(&table[i].rx_delay_stopbit);
               _tx_delay = pgm_read_word(&table[i].tx_delay);
               break;
             }
           }

           if (_rx_delay_stopbit) {
             if (digitalPinToPCICR(_receivePin)) {
               *digitalPinToPCICR(_receivePin) |= _BV(digitalPinToPCICRbit(_receivePin));
               *digitalPinToPCMSK(_receivePin) |= _BV(digitalPinToPCMSKbit(_receivePin));
             }
             tunedDelay(_tx_delay);
           }

         #if _DEBUG
           pinMode(_DEBUG_PIN1, OUTPUT);
           pinMode(_DEBUG_PIN2, OUTPUT);
         #endif

           listen();
         }

         void SoftwareSerial::end() {
           if (digitalPinToPCMSK(_receivePin))
             *digitalPinToPCMSK(_receivePin) &= ~_BV(digitalPinToPCMSKbit(_receivePin));
         }


         int SoftwareSerial::read() {
           if (!isListening())
             return -1;

           if (_receive_buffer_head == _receive_buffer_tail)
             return -1;

           uint8_t d = _receive_buffer[_receive_buffer_head]; // grab next byte
           _receive_buffer_head = (_receive_buffer_head + 1) % _SS_MAX_RX_BUFF;
           return d;
         }

         int SoftwareSerial::available() {
           if (!isListening())
             return 0;

           return (_receive_buffer_tail + _SS_MAX_RX_BUFF - _receive_buffer_head) % _SS_MAX_RX_BUFF;
         }

         size_t SoftwareSerial::write(uint8_t b) {
           if (_tx_delay == 0) {
             setWriteError();
             return 0;
           }

           uint8_t oldSREG = SREG;
           cli();

           tx_pin_write(_inverse_logic ? HIGH : LOW);
           tunedDelay(_tx_delay + XMIT_START_ADJUSTMENT);

           if (_inverse_logic) {
             for (byte mask = 0x01; mask; mask <<= 1) {
               if (b & mask)
                 tx_pin_write(LOW);
               else
                 tx_pin_write(HIGH);

               tunedDelay(_tx_delay);
             }

             tx_pin_write(LOW);
           }
           else {
             for (byte mask = 0x01; mask; mask <<= 1) {
               if (b & mask)
                 tx_pin_write(HIGH);
               else
                 tx_pin_write(LOW);
               tunedDelay(_tx_delay);
             }

             tx_pin_write(HIGH);
           }

           SREG = oldSREG;
           tunedDelay(_tx_delay);

           return 1;
         }

         void SoftwareSerial::flush() {
           if (!isListening())
             return;

           uint8_t oldSREG = SREG;
           cli();
           _receive_buffer_head = _receive_buffer_tail = 0;
           SREG = oldSREG;
         }

         int SoftwareSerial::peek() {
           if (!isListening())
             return -1;

           if (_receive_buffer_head == _receive_buffer_tail)
             return -1;

           return _receive_buffer[_receive_buffer_head];
         }
        ///@endcond
      #endif
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
             D2&D3 : Used for Bluetooth communication
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
                Serial.println(" : Used for Bluetooth communication");
                Serial.print("   D");Serial.print(PIN_MOTOR_DIR);Serial.print("&");
                Serial.print("D");Serial.print(PIN_MOTOR_SPE);
                Serial.println(" : Used for main motor control");
                #if EBOARD_USE_SPI > 0x0
                    Serial.print("   D10-13");
                    Serial.println(": Used for smart-servo-shield");
                #endif
            } else if (strcmp(__func,"readPin")==0){
                Serial.println("You've tried to access an analogPin that isn't present on the board you're currently working on!");
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
                @note [COPY&PASTE] [CHECK_PINS] bool set of already declared OUTPUT pins [16 bits on UNO and NANO 64 on MEGA]

                @note it is possible to read from portDE... but this isn't that much bigger -- maybe a todo
            */
            #if defined(__AVR_ATmega328P__) && not defined(__AVR_ATmega2560__)
              uint16_t pin_out = 0x0;
            #elif defined(__AVR_ATmega2560__)
              uint64_t pin_out = 0x0;
            #endif
            /*!
                @note [COPY&PASTE] [CHECK_PINS] bool set of already declared INPUT pins [16 bits on UNO and NANO 64 on MEGA]
            */
            #if defined(__AVR_ATmega328P__) && not defined(__AVR_ATmega2560__)
              uint16_t pin_in = 0x0;
            #elif defined(__AVR_ATmega2560__)
              uint64_t pin_in = 0x0;
            #endif
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
        @note if SHIFT_REGISTER is enabled you can assign the additional outputs 0-based from 100

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
                else if (idx<0||idx>0xF){ //use I2C? change => Wire
            #else
                else if (idx<0||idx>0x7){ //use I2C? change => Wire
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

    #if EBOARD_USE_SPI > 0x0 && (EBOARD_NANO == 0x0)
      namespace eagle_impl {
        /*!
            @struct ServoCds55

            @author EagleoutIce

            @brief [SPI] This is used to communicate with the smart servo shield
            \n &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <b>Don't use manually</b>

            @warning [COPY&PASTE] use SoccerBoard, DynamixelBoard and I2CInOut !
            @warning this code is for internal use only and shouldnt be used otherwise

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
                @brief sends data.
                @note This is used internally and shouldnt be used!

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
        }
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

    #if EBOARD_COPY_AND_PASTE > 0x0 && EBOARD_NANO == 0
        /*!
            @struct SoccerBoard

            @author EagleoutIce

            @brief [COPY&PASTE] This is the SoccerBoard ghost struct :D

            @note Some calls like led-calls won't have any effect due to the hardware of the UNO \n But they will work on the MEGA!

            [COPY&PASTE] You can use this class like this:
            @code
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
            #endif
            /**
             * @brief As requested this is the ultimate shortcut ;)
             * @param id set to
             *    - 0 it will access the main Motor (accessed with I2CInOut otherwise)
             *    - 1 it will try to access the Servo with the lower ID
             *    - 2 it will try to access the Servo with the higher ID
             * @param val the value you wan't to send
             *    - if id = 0  : val has to be from -255 to 255. Dir will be decided by >0|<0
             *    - if id = 1|2: val has to be from 0 to 1023
             */
            inline void motor(uint8_t id,int16_t val);
            /// @brief As requested this is the shortcut to disable the main motor
            inline void motorsOff(void);
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
        #endif

        void SoccerBoard::motor(uint8_t id,int16_t val) {
          if(id==0&&(val>-256 && val < 256)) {setPin(PIN_MOTOR_DIR,val<0); writePWM(abs(val));}
          else if(id>0&&id<3&&(val>-0 && val < 1024)) {_servoHandler.write((id-1),(val *600/1023 - 300));}
        }
        void SoccerBoard::motorsOff(void) {writePWM(0);}

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
            #define EBOARD_I2C 0x1
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
        #endif
        #if EBOARD_BLUETOOTH > 0x0
            /*!
                @struct RB14Scan

                @author EagleoutIce

                @brief [COPY&PASTE] [BLUETOOTH] This is the RB14Scan ghost struct :D

                @pre to use this class on UNO:
                @code
                #define EBOARD_BLUETOOTH   0x1
                @endcode
                \n \n  If you don't reconfigure the TX and RX on MEGA:
                @code
                #define EBOARD_BLUETOOTH 0x1
                @endcode

                [COPY&PASTE] [BLUETOOTH] You can use this class like this on UNO:
                @code
                #define EBOARD_BLUETOOTH   0x1
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

        /**
            @page source_page The source code

            @brief Welcome to the matrix (:

            @includelineno /eagleoutice/projects/github/eBoard/eBoard.h
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
                #define EBOARD_I2C 0x1 //do you think this is obsolete ? tell me :D
                #define EBOARD_LCD 0x1
                @endcode

                [I2C] [LCD] You can use this class like this:
                @code
                #define EBOARD_I2C 0x1
                #define EBOARD_LCD 0x1
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
                #if EBOARD_NANO == 0
                /*!
                    @brief The constructor

                    @param soccerBoard the connected SoccerBoard object
                    @param id          the ID of the LCD display. Can be identified via pingI2C()

                    @note if #EBOARD_NANO is set to 0x1 this will only take one argument [the id]
                 */
                LCD(SoccerBoard &soccerBoard, optVAL_t id=0x3C);
                #else
                LCD(optVAL_t id=0x3C);
                #endif
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
            #if EBOARD_NANO == 0x0
            LCD::LCD(SoccerBoard &soccerBoard, optVAL_t id) {
                this->_cI = false;
                this->ID = id;
                //this->init();
            }
            #else
            LCD::LCD( optVAL_t id) {
                this->_cI = false;
                this->ID = id;
                //this->init();
            }
            #endif
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

        #if EBOARD_NEO > 0x0
        // Codesection based on official NeoPixel library
        // RGB NeoPixel permutations; white and red offsets are always same
        // Offset:         W          R          G          B
        ///@macro_def Defines the amount of needed permutation when com. in RGB-Mode
        #define EBOARD_NEO_RGB  ((0 << 6) | (0 << 4) | (1 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in RBG-Mode
        #define EBOARD_NEO_RBG  ((0 << 6) | (0 << 4) | (2 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in GRB-Mode
        #define EBOARD_NEO_GRB  ((1 << 6) | (1 << 4) | (0 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in GBR-Mode
        #define EBOARD_NEO_GBR  ((2 << 6) | (2 << 4) | (0 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in BRG-Mode
        #define EBOARD_NEO_BRG  ((1 << 6) | (1 << 4) | (2 << 2) | (0))
        ///@macro_def Defines the amount of needed permutation when com. in BGR-Mode
        #define EBOARD_NEO_BGR  ((2 << 6) | (2 << 4) | (1 << 2) | (0))

        // RGBW NeoPixel permutations; all 4 offsets are distinct
        // Offset:         W          R          G          B
        ///@macro_def Defines the amount of needed permutation when com. in WRGB-Mode
        #define EBOARD_NEO_WRGB ((0 << 6) | (1 << 4) | (2 << 2) | (3))
        ///@macro_def Defines the amount of needed permutation when com. in WRBG-Mode
        #define EBOARD_NEO_WRBG ((0 << 6) | (1 << 4) | (3 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in WGRB-Mode
        #define EBOARD_NEO_WGRB ((0 << 6) | (2 << 4) | (1 << 2) | (3))
        ///@macro_def Defines the amount of needed permutation when com. in WGBR-Mode
        #define EBOARD_NEO_WGBR ((0 << 6) | (3 << 4) | (1 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in WBRG-Mode
        #define EBOARD_NEO_WBRG ((0 << 6) | (2 << 4) | (3 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in WBGR-Mode
        #define EBOARD_NEO_WBGR ((0 << 6) | (3 << 4) | (2 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in RWGB-Mode
        #define EBOARD_NEO_RWGB ((1 << 6) | (0 << 4) | (2 << 2) | (3))
        ///@macro_def Defines the amount of needed permutation when com. in RWBG-Mode
        #define EBOARD_NEO_RWBG ((1 << 6) | (0 << 4) | (3 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in RGWB-Mode
        #define EBOARD_NEO_RGWB ((2 << 6) | (0 << 4) | (1 << 2) | (3))
        ///@macro_def Defines the amount of needed permutation when com. in RGBW-Mode
        #define EBOARD_NEO_RGBW ((3 << 6) | (0 << 4) | (1 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in RBWG-Mode
        #define EBOARD_NEO_RBWG ((2 << 6) | (0 << 4) | (3 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in RBGW-Mode
        #define EBOARD_NEO_RBGW ((3 << 6) | (0 << 4) | (2 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in GWRB-Mode
        #define EBOARD_NEO_GWRB ((1 << 6) | (2 << 4) | (0 << 2) | (3))
        ///@macro_def Defines the amount of needed permutation when com. in GWBR-Mode
        #define EBOARD_NEO_GWBR ((1 << 6) | (3 << 4) | (0 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in GRWB-Mode
        #define EBOARD_NEO_GRWB ((2 << 6) | (1 << 4) | (0 << 2) | (3))
        ///@macro_def Defines the amount of needed permutation when com. in GRBW-Mode
        #define EBOARD_NEO_GRBW ((3 << 6) | (1 << 4) | (0 << 2) | (2))
        ///@macro_def Defines the amount of needed permutation when com. in GBWR-Mode
        #define EBOARD_NEO_GBWR ((2 << 6) | (3 << 4) | (0 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in GBRW-Mode
        #define EBOARD_NEO_GBRW ((3 << 6) | (2 << 4) | (0 << 2) | (1))
        ///@macro_def Defines the amount of needed permutation when com. in BWRG-Mode
        #define EBOARD_NEO_BWRG ((1 << 6) | (2 << 4) | (3 << 2) | (0))
        ///@macro_def Defines the amount of needed permutation when com. in BWGR-Mode
        #define EBOARD_NEO_BWGR ((1 << 6) | (3 << 4) | (2 << 2) | (0))
        ///@macro_def Defines the amount of needed permutation when com. in BRWG-Mode
        #define EBOARD_NEO_BRWG ((2 << 6) | (1 << 4) | (3 << 2) | (0))
        ///@macro_def Defines the amount of needed permutation when com. in BRGW-Mode
        #define EBOARD_NEO_BRGW ((3 << 6) | (1 << 4) | (2 << 2) | (0))
        ///@macro_def Defines the amount of needed permutation when com. in BGWR-Mode
        #define EBOARD_NEO_BGWR ((2 << 6) | (3 << 4) | (1 << 2) | (0))
        ///@macro_def Defines the amount of needed permutation when com. in BGRW-Mode
        #define EBOARD_NEO_BGRW ((3 << 6) | (2 << 4) | (1 << 2) | (0))


        ///@macro_def Defines the value to enable 800Khz communication Mode
        #define EBOARD_NEO_800KHZ 0x0000
        ///@macro_def Defines the value to enable 400Khz communication Mode
        #define EBOARD_NEO_400KHZ 0x0100

        // uint16_t can be uint8_t in 800Khz mode ^^
        /*!
            @struct NeoPixel

            @author Adafruit

            @brief [NEO] this allows you to access Adafruit LED-stripes

            @note this code was documented and modified by EagleoutIce in 2018 for custom use!

            @pre to use this class:
            @code
            #define EBOARD_NEO 0x1
            @endcode

            [NEO] You can use this class like this:
            @code
            #define EBOARD_NEO 0x1
            #include "/home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h"
            NeoPixel nPixel = NeoPixel(5);
            int main() {
                nPixel.setPixelColor(3,NeoPixel::Color(0,255,0));
                nPixel.show();
            }
            @endcode


        */
        struct NeoPixel{
          /**
           * @brief this is the default constructor that should be used whenever the amount of leds etc... connected is known at compile time (most cases)
           *
           * @param n the amount of LEDs connected to the pin
           * @param p the (data) pin connected to the arduino
           * @param t the type of com the NeoPixel should be talked to
           */
          NeoPixel(uint16_t n, uint8_t p = 6, uint16_t t =  EBOARD_NEO_RGB + EBOARD_NEO_800KHZ);
          /**
           * @brief the empty constructor
           * @note this has to be called manually then:
           *  - NeoPixel::updateType()
           *  - NeoPixel::updateLength()
           *  - NeoPixel::setPin()
           */
          NeoPixel(void);
          /// @brief the destructor [calling free on pixel and freeing input pin]
          ~NeoPixel(void);
          /**
           * @brief this has to be called to start the communcation (you should call NeoPixel::setPin() before)
           */
          void begin(void);
          /**
           * @brief this will reveal the setPixels [via NeoPixel::setPixelColor() etc...]
           */
          void show(void);
          /**
           * @brief sets pin for communication
           * @param p the (data) pin connected to the arduino
           */
          void setPin(uint8_t p);
          /**
           * @brief sets the rgb color of a specific pixel
           * @param n the index of the pixel (starting at 0)
           * @param r the red color [can be different dependent on NeoPixel::updateType()]
           * @param g the green color [can be different dependent on NeoPixel::updateType()]
           * @param b the blue color [can be different dependent on NeoPixel::updateType()]
           */
          void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
          /**
           * @brief sets the rgbw color of a specific pixel
           * @param n the index of the pixel (starting at 0)
           * @param r the red color [can be different dependent on NeoPixel::updateType()]
           * @param g the green color [can be different dependent on NeoPixel::updateType()]
           * @param b the blue color [can be different dependent on NeoPixel::updateType()]
           * @param w the 'white' color [can be different dependent on NeoPixel::updateType()]
           */
          void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
          /**
           * @brief sets the rgbw color of a specific pixel
           * @param n the index of the pixel (starting at 0)
           * @param c the NeoPixel::Color() you want
           */
          void setPixelColor(uint16_t n, uint32_t c);
          /**
           * @brief changes the brightness for all further acceses via NeoPixel::setPixelColor()
           * @param val the brightness-value
           */
          void setBrightness(uint8_t val);
          /**
           * @brief this will reset all set pixels [won't call NeoPixel::show()]
           */
          void clear(void);
          /**
           * @brief this changes the length of the connected LED stripe
           * @param n the new length
           */
          void updateLength(uint16_t n);
          /**
           * @brief this changes the type of communication between arduino and LED stripe
           * @param t the new type [constant starting with EBOARD_NEO]
           */
          void updateType(uint16_t t);
          /**
           * @brief this will give you access to the pixels
           * @returns the pixels 'set'
           */
          inline uint8_t *getPixels(void) const;
          /**
           * @brief returns the current set brightness
           * @returns the brightness set via NeoPixel::setBrightness()
           */
          inline uint8_t getBrightness(void) const;
          /**
           * @brief acces to the sine-8-bit table ;D
           * @param x the x-value in sin(x)
           * @returns the corresponding y-value
           */
          uint8_t sine8(uint8_t x) const;
          /**
           * @brief acces to the gamma-correction-8-bit table ;D
           * @param x the correction index
           * @returns the corresponding gamma correction
           */
          uint8_t gamma8(uint8_t x) const;
          /**
           * @brief this will return the set data pin
           * @returns the dataPin set via NeoPixel::setPin()
           */
          inline int8_t getPin(void);
          /**
           * @brief returns the size of the LED stripe
           * @returns the size set via NeoPixel::updateLength()
           */
          inline uint16_t numPixels(void) const;
          /**
           * @brief returns a color value that can be used with NeoPixel::setPixelColor()
           * @param r the red color [can be different dependent on NeoPixel::updateType()]
           * @param g the green color [can be different dependent on NeoPixel::updateType()]
           * @param b the blue color [can be different dependent on NeoPixel::updateType()]
           */
          static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
          /**
           * @brief returns a color value that can be used with NeoPixel::setPixelColor()
           * @param r the red color [can be different dependent on NeoPixel::updateType()]
           * @param g the green color [can be different dependent on NeoPixel::updateType()]
           * @param b the blue color [can be different dependent on NeoPixel::updateType()]
           * @param w the 'white' color [can be different dependent on NeoPixel::updateType()]
           */
          static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
          /**
           * @brief returns the color of a specific pixel
           * @returns the color value
           */
          uint32_t getPixelColor(uint16_t n) const;
          /**
           * @brief this will determine if the next show is available [last show finished]
           * @returns true if it is possible
           */
          inline bool canShow(void);
        protected:
          /// @brief determines the speed the communcation is working on
          bool is800kHz;
          /// @brief true if NeoPixel::begin has been called
          bool begun;
          /// @brief stores the amount of LEDs
          uint16_t numLEDs; //maybe shorten with PrepConst 'extendetLED'?
          /// @brief stores the byte size [pixels] used internally
          uint16_t numBytes;
          /**
           * @brief stores the pin
           *  -1 if the pin wasn't set
           */
          int8_t pin;
          /// @brief stores the brightness
          uint8_t brightness;
          /// @brief stores the pixels
          uint8_t *pixels;
          /// @brief stores the red color offset
          uint8_t rOffset;
          /// @brief stores the green color offset
          uint8_t gOffset;
          /// @brief stores the blue color offset
          uint8_t bOffset;
          /// @brief stores the white color offset
          uint8_t wOffset;
          /// @brief stores the last call time of show for NeoPixel::canShow()
          uint32_t endTime; //used for diff calc
          #ifdef __AVR__ //not needed (rem?)
            /// @brief the used port register
            volatile uint8_t *port;// Output PORT register
            /// @brief the used pinMask
            uint8_t pinMask;       // Output PORT bitmask
          #endif

        };

        ///@cond


        NeoPixel::NeoPixel(uint16_t n, uint8_t p, uint16_t t) :
          begun(false), brightness(0), pixels(NULL), endTime(0) {
          updateType(t);
          updateLength(n);
          setPin(p);
        }

        inline bool NeoPixel::canShow(void) { return (micros() - endTime) >= 300L; }

        NeoPixel::NeoPixel() :
          is800KHz(true),
          begun(false), numLEDs(0), numBytes(0), pin(-1), brightness(0), pixels(NULL),
          rOffset(1), gOffset(0), bOffset(2), wOffset(1), endTime(0)
        {}

        NeoPixel::~NeoPixel() {
          if(pixels)   free(pixels);
          if(pin >= 0) pinMode(pin, INPUT);
        }

        void NeoPixel::begin(void) {
          if(pin >= 0) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
          }
          begun = true;

        }

        void NeoPixel::updateLength(uint16_t n) {
          if(pixels) free(pixels);
          numBytes = n * ((wOffset == rOffset) ? 3 : 4);
          if((pixels = (uint8_t *)malloc(numBytes))) {
            memset(pixels, 0, numBytes);
            numLEDs = n;
          } else {
            numLEDs = numBytes = 0;
          }
        }

        void NeoPixel::updateType(uint16_t t) {
          boolean oldThreeBytesPerPixel = (wOffset == rOffset); // false if RGBW

          wOffset = (t >> 6) & 0b11;
          rOffset = (t >> 4) & 0b11;
          gOffset = (t >> 2) & 0b11;
          bOffset =  t       & 0b11;
          is800KHz = (t < 256);      // 400 KHz flag is 1<<8

          if(pixels) {
            boolean newThreeBytesPerPixel = (wOffset == rOffset);
            if(newThreeBytesPerPixel != oldThreeBytesPerPixel) updateLength(numLEDs);
          }
        }

        #if defined(ESP8266)
          // ESP8266 show() is external to enforce ICACHE_RAM_ATTR execution
          extern "C" void ICACHE_RAM_ATTR espShow(
            uint8_t pin, uint8_t *pixels, uint32_t numBytes, uint8_t type);
        #elif defined(ESP32)
          extern "C" void espShow(
            uint8_t pin, uint8_t *pixels, uint32_t numBytes, uint8_t type);
        #endif

        void NeoPixel::show(void) {
          if(!pixels) return;
          while(!canShow()); //maybe timeout ?
          noInterrupts(); // Need 100% focus on instruction timing

        #ifdef __AVR__
          volatile uint16_t
            i   = numBytes;
          volatile uint8_t
           *ptr = pixels,
            b   = *ptr++,
            hi,
            lo;

        #if (F_CPU >= 7400000UL) && (F_CPU <= 9500000UL)

          if(is800KHz) {
            volatile uint8_t n1, n2 = 0;

        #if defined(PORTD)
         #if defined(PORTB) || defined(PORTC) || defined(PORTF)
            if(port == &PORTD) {
         #endif

              hi = PORTD |  pinMask;
              lo = PORTD & ~pinMask;
              n1 = lo;
              if(b & 0x80) n1 = hi;

              asm volatile(
               "headD:"                   "\n\t" // Clk  Pseudocode
                // Bit 7:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
                "rjmp .+0"                "\n\t" // 2    nop nop
                "sbrc %[byte] , 6"        "\n\t" // 1-2  if(b & 0x40)
                 "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "rjmp .+0"                "\n\t" // 2    nop nop
                // Bit 6:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
                "rjmp .+0"                "\n\t" // 2    nop nop
                "sbrc %[byte] , 5"        "\n\t" // 1-2  if(b & 0x20)
                 "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "rjmp .+0"                "\n\t" // 2    nop nop
                // Bit 5:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
                "rjmp .+0"                "\n\t" // 2    nop nop
                "sbrc %[byte] , 4"        "\n\t" // 1-2  if(b & 0x10)
                 "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "rjmp .+0"                "\n\t" // 2    nop nop
                // Bit 4:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
                "rjmp .+0"                "\n\t" // 2    nop nop
                "sbrc %[byte] , 3"        "\n\t" // 1-2  if(b & 0x08)
                 "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "rjmp .+0"                "\n\t" // 2    nop nop
                // Bit 3:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
                "rjmp .+0"                "\n\t" // 2    nop nop
                "sbrc %[byte] , 2"        "\n\t" // 1-2  if(b & 0x04)
                 "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "rjmp .+0"                "\n\t" // 2    nop nop
                // Bit 2:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
                "rjmp .+0"                "\n\t" // 2    nop nop
                "sbrc %[byte] , 1"        "\n\t" // 1-2  if(b & 0x02)
                 "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "rjmp .+0"                "\n\t" // 2    nop nop
                // Bit 1:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
                "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
                "rjmp .+0"                "\n\t" // 2    nop nop
                "sbrc %[byte] , 0"        "\n\t" // 1-2  if(b & 0x01)
                 "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "sbiw %[count], 1"        "\n\t" // 2    i-- (don't act on Z flag yet)
                // Bit 0:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
                "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
                "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
                "ld   %[byte] , %a[ptr]+" "\n\t" // 2    b = *ptr++
                "sbrc %[byte] , 7"        "\n\t" // 1-2  if(b & 0x80)
                 "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
                "brne headD"              "\n"   // 2    while(i) (Z flag set above)
              : [byte]  "+r" (b),
                [n1]    "+r" (n1),
                [n2]    "+r" (n2),
                [count] "+w" (i)
              : [port]   "I" (_SFR_IO_ADDR(PORTD)),
                [ptr]    "e" (ptr),
                [hi]     "r" (hi),
                [lo]     "r" (lo));

         #if defined(PORTB) || defined(PORTC) || defined(PORTF)
            } else
         #endif
        #endif
        #if defined(PORTB)
         #if defined(PORTD) || defined(PORTC) || defined(PORTF)
            if(port == &PORTB) {
         #endif // defined(PORTD/C/F)
              hi = PORTB |  pinMask;
              lo = PORTB & ~pinMask;
              n1 = lo;
              if(b & 0x80) n1 = hi;

              asm volatile(
               "headB:"                   "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 6"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 5"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 4"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 3"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 2"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 1"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 0"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "sbiw %[count], 1"        "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "ld   %[byte] , %a[ptr]+" "\n\t"
                "sbrc %[byte] , 7"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "brne headB"              "\n"
              : [byte] "+r" (b), [n1] "+r" (n1), [n2] "+r" (n2), [count] "+w" (i)
              : [port] "I" (_SFR_IO_ADDR(PORTB)), [ptr] "e" (ptr), [hi] "r" (hi),
                [lo] "r" (lo));

         #if defined(PORTD) || defined(PORTC) || defined(PORTF)
            }
         #endif
         #if defined(PORTC) || defined(PORTF)
            else
         #endif
        #endif

        #if defined(PORTC)
         #if defined(PORTD) || defined(PORTB) || defined(PORTF)
            if(port == &PORTC) {
         #endif

              hi = PORTC |  pinMask;
              lo = PORTC & ~pinMask;
              n1 = lo;
              if(b & 0x80) n1 = hi;

              asm volatile(
               "headC:"                   "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 6"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 5"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 4"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 3"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 2"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 1"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 0"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "sbiw %[count], 1"        "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "ld   %[byte] , %a[ptr]+" "\n\t"
                "sbrc %[byte] , 7"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "brne headC"              "\n"
              : [byte] "+r" (b), [n1] "+r" (n1), [n2] "+r" (n2), [count] "+w" (i)
              : [port] "I" (_SFR_IO_ADDR(PORTC)), [ptr] "e" (ptr), [hi] "r" (hi),
                [lo] "r" (lo));

         #if defined(PORTD) || defined(PORTB) || defined(PORTF)
            }
         #endif
         #if defined(PORTF)
            else
         #endif
        #endif

        #if defined(PORTF)
         #if defined(PORTD) || defined(PORTB) || defined(PORTC)
            if(port == &PORTF) {
         #endif // defined(PORTD/B/C)

              hi = PORTF |  pinMask;
              lo = PORTF & ~pinMask;
              n1 = lo;
              if(b & 0x80) n1 = hi;

              asm volatile(
               "headF:"                   "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 6"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 5"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 4"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 3"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 2"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 1"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n2]   , %[lo]"    "\n\t"
                "out  %[port] , %[n1]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "sbrc %[byte] , 0"        "\n\t"
                 "mov %[n2]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "sbiw %[count], 1"        "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "mov  %[n1]   , %[lo]"    "\n\t"
                "out  %[port] , %[n2]"    "\n\t"
                "ld   %[byte] , %a[ptr]+" "\n\t"
                "sbrc %[byte] , 7"        "\n\t"
                 "mov %[n1]   , %[hi]"    "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "brne headF"              "\n"
              : [byte] "+r" (b), [n1] "+r" (n1), [n2] "+r" (n2), [count] "+w" (i)
              : [port] "I" (_SFR_IO_ADDR(PORTF)), [ptr] "e" (ptr), [hi] "r" (hi),
                [lo] "r" (lo));

         #if defined(PORTD) || defined(PORTB) || defined(PORTC)
            }
         #endif // defined(PORTD/B/C)
        #endif // defined(PORTF)
          } else {

            volatile uint8_t next, bit;

            hi   = *port |  pinMask;
            lo   = *port & ~pinMask;
            next = lo;
            bit  = 8;

            asm volatile(
             "head20:"                  "\n\t" // Clk  Pseudocode    (T =  0)
              "st   %a[port], %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
              "sbrc %[byte] , 7"        "\n\t" // 1-2  if(b & 128)
               "mov  %[next], %[hi]"    "\n\t" // 0-1   next = hi    (T =  4)
              "st   %a[port], %[next]"  "\n\t" // 2    PORT = next   (T =  6)
              "mov  %[next] , %[lo]"    "\n\t" // 1    next = lo     (T =  7)
              "dec  %[bit]"             "\n\t" // 1    bit--         (T =  8)
              "breq nextbyte20"         "\n\t" // 1-2  if(bit == 0)
              "rol  %[byte]"            "\n\t" // 1    b <<= 1       (T = 10)
              "st   %a[port], %[lo]"    "\n\t" // 2    PORT = lo     (T = 12)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 14)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 16)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 18)
              "rjmp head20"             "\n\t" // 2    -> head20 (next bit out)
             "nextbyte20:"              "\n\t" //                    (T = 10)
              "st   %a[port], %[lo]"    "\n\t" // 2    PORT = lo     (T = 12)
              "nop"                     "\n\t" // 1    nop           (T = 13)
              "ldi  %[bit]  , 8"        "\n\t" // 1    bit = 8       (T = 14)
              "ld   %[byte] , %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 16)
              "sbiw %[count], 1"        "\n\t" // 2    i--           (T = 18)
              "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
              : [port]  "+e" (port),
                [byte]  "+r" (b),
                [bit]   "+r" (bit),
                [next]  "+r" (next),
                [count] "+w" (i)
              : [hi]    "r" (hi),
                [lo]    "r" (lo),
                [ptr]   "e" (ptr));
          }
        #elif (F_CPU >= 11100000UL) && (F_CPU <= 14300000UL)
          if(is800KHz) {
            volatile uint8_t next;

            // PORTD OUTPUT ----------------------------------------------------

        #if defined(PORTD)
         #if defined(PORTB) || defined(PORTC) || defined(PORTF)
            if(port == &PORTD) {
         #endif

              hi   = PORTD |  pinMask;
              lo   = PORTD & ~pinMask;
              next = lo;
              if(b & 0x80) next = hi;
              asm volatile(
               "headD:"                   "\n\t" //        (T =  0)
                "out   %[port], %[hi]"    "\n\t" //        (T =  1)
                "rcall bitTimeD"          "\n\t" // Bit 7  (T = 15)
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeD"          "\n\t" // Bit 6
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeD"          "\n\t" // Bit 5
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeD"          "\n\t" // Bit 4
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeD"          "\n\t" // Bit 3
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeD"          "\n\t" // Bit 2
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeD"          "\n\t" // Bit 1
                // Bit 0:
                "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi    (T =  1)
                "rjmp .+0"                "\n\t" // 2    nop nop      (T =  3)
                "ld   %[byte] , %a[ptr]+" "\n\t" // 2    b = *ptr++   (T =  5)
                "out  %[port] , %[next]"  "\n\t" // 1    PORT = next  (T =  6)
                "mov  %[next] , %[lo]"    "\n\t" // 1    next = lo    (T =  7)
                "sbrc %[byte] , 7"        "\n\t" // 1-2  if(b & 0x80) (T =  8)
                 "mov %[next] , %[hi]"    "\n\t" // 0-1    next = hi  (T =  9)
                "nop"                     "\n\t" // 1                 (T = 10)
                "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo    (T = 11)
                "sbiw %[count], 1"        "\n\t" // 2    i--          (T = 13)
                "brne headD"              "\n\t" // 2    if(i != 0) -> (next byte)
                 "rjmp doneD"             "\n\t"
                "bitTimeD:"               "\n\t" //      nop nop nop     (T =  4)
                 "out  %[port], %[next]"  "\n\t" // 1    PORT = next     (T =  5)
                 "mov  %[next], %[lo]"    "\n\t" // 1    next = lo       (T =  6)
                 "rol  %[byte]"           "\n\t" // 1    b <<= 1         (T =  7)
                 "sbrc %[byte], 7"        "\n\t" // 1-2  if(b & 0x80)    (T =  8)
                  "mov %[next], %[hi]"    "\n\t" // 0-1   next = hi      (T =  9)
                 "nop"                    "\n\t" // 1                    (T = 10)
                 "out  %[port], %[lo]"    "\n\t" // 1    PORT = lo       (T = 11)
                 "ret"                    "\n\t" // 4    nop nop nop nop (T = 15)
                 "doneD:"                 "\n"
                : [byte]  "+r" (b),
                  [next]  "+r" (next),
                  [count] "+w" (i)
                : [port]   "I" (_SFR_IO_ADDR(PORTD)),
                  [ptr]    "e" (ptr),
                  [hi]     "r" (hi),
                  [lo]     "r" (lo));

         #if defined(PORTB) || defined(PORTC) || defined(PORTF)
            } else
         #endif
        #endif

        #if defined(PORTB)
         #if defined(PORTD) || defined(PORTC) || defined(PORTF)
            if(port == &PORTB) {
         #endif

              hi   = PORTB |  pinMask;
              lo   = PORTB & ~pinMask;
              next = lo;
              if(b & 0x80) next = hi;

              asm volatile(
               "headB:"                   "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeB"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeB"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeB"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeB"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeB"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeB"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeB"          "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "ld   %[byte] , %a[ptr]+" "\n\t"
                "out  %[port] , %[next]"  "\n\t"
                "mov  %[next] , %[lo]"    "\n\t"
                "sbrc %[byte] , 7"        "\n\t"
                 "mov %[next] , %[hi]"    "\n\t"
                "nop"                     "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "sbiw %[count], 1"        "\n\t"
                "brne headB"              "\n\t"
                 "rjmp doneB"             "\n\t"
                "bitTimeB:"               "\n\t"
                 "out  %[port], %[next]"  "\n\t"
                 "mov  %[next], %[lo]"    "\n\t"
                 "rol  %[byte]"           "\n\t"
                 "sbrc %[byte], 7"        "\n\t"
                  "mov %[next], %[hi]"    "\n\t"
                 "nop"                    "\n\t"
                 "out  %[port], %[lo]"    "\n\t"
                 "ret"                    "\n\t"
                 "doneB:"                 "\n"
                : [byte] "+r" (b), [next] "+r" (next), [count] "+w" (i)
                : [port] "I" (_SFR_IO_ADDR(PORTB)), [ptr] "e" (ptr), [hi] "r" (hi),
                  [lo] "r" (lo));

         #if defined(PORTD) || defined(PORTC) || defined(PORTF)
            }
         #endif
         #if defined(PORTC) || defined(PORTF)
            else
         #endif
        #endif

        #if defined(PORTC)
         #if defined(PORTD) || defined(PORTB) || defined(PORTF)
            if(port == &PORTC) {
         #endif

              hi   = PORTC |  pinMask;
              lo   = PORTC & ~pinMask;
              next = lo;
              if(b & 0x80) next = hi;

              asm volatile(
               "headC:"                   "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "ld   %[byte] , %a[ptr]+" "\n\t"
                "out  %[port] , %[next]"  "\n\t"
                "mov  %[next] , %[lo]"    "\n\t"
                "sbrc %[byte] , 7"        "\n\t"
                 "mov %[next] , %[hi]"    "\n\t"
                "nop"                     "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "sbiw %[count], 1"        "\n\t"
                "brne headC"              "\n\t"
                 "rjmp doneC"             "\n\t"
                "bitTimeC:"               "\n\t"
                 "out  %[port], %[next]"  "\n\t"
                 "mov  %[next], %[lo]"    "\n\t"
                 "rol  %[byte]"           "\n\t"
                 "sbrc %[byte], 7"        "\n\t"
                  "mov %[next], %[hi]"    "\n\t"
                 "nop"                    "\n\t"
                 "out  %[port], %[lo]"    "\n\t"
                 "ret"                    "\n\t"
                 "doneC:"                 "\n"
                : [byte] "+r" (b), [next] "+r" (next), [count] "+w" (i)
                : [port] "I" (_SFR_IO_ADDR(PORTC)), [ptr] "e" (ptr), [hi] "r" (hi),
                  [lo] "r" (lo));

         #if defined(PORTD) || defined(PORTB) || defined(PORTF)
            }
         #endif
         #if defined(PORTF)
            else
         #endif
        #endif

        #if defined(PORTF)
         #if defined(PORTD) || defined(PORTB) || defined(PORTC)
            if(port == &PORTF) {
         #endif

              hi   = PORTF |  pinMask;
              lo   = PORTF & ~pinMask;
              next = lo;
              if(b & 0x80) next = hi;

              asm volatile(
               "headF:"                   "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out   %[port], %[hi]"    "\n\t"
                "rcall bitTimeC"          "\n\t"
                "out  %[port] , %[hi]"    "\n\t"
                "rjmp .+0"                "\n\t"
                "ld   %[byte] , %a[ptr]+" "\n\t"
                "out  %[port] , %[next]"  "\n\t"
                "mov  %[next] , %[lo]"    "\n\t"
                "sbrc %[byte] , 7"        "\n\t"
                 "mov %[next] , %[hi]"    "\n\t"
                "nop"                     "\n\t"
                "out  %[port] , %[lo]"    "\n\t"
                "sbiw %[count], 1"        "\n\t"
                "brne headF"              "\n\t"
                 "rjmp doneC"             "\n\t"
                "bitTimeC:"               "\n\t"
                 "out  %[port], %[next]"  "\n\t"
                 "mov  %[next], %[lo]"    "\n\t"
                 "rol  %[byte]"           "\n\t"
                 "sbrc %[byte], 7"        "\n\t"
                  "mov %[next], %[hi]"    "\n\t"
                 "nop"                    "\n\t"
                 "out  %[port], %[lo]"    "\n\t"
                 "ret"                    "\n\t"
                 "doneC:"                 "\n"
                : [byte] "+r" (b), [next] "+r" (next), [count] "+w" (i)
                : [port] "I" (_SFR_IO_ADDR(PORTF)), [ptr] "e" (ptr), [hi] "r" (hi),
                  [lo] "r" (lo));

         #if defined(PORTD) || defined(PORTB) || defined(PORTC)
            }
         #endif
        #endif
          } else {
            volatile uint8_t next, bit;

            hi   = *port |  pinMask;
            lo   = *port & ~pinMask;
            next = lo;
            bit  = 8;

            asm volatile(
             "head30:"                  "\n\t" // Clk  Pseudocode    (T =  0)
              "st   %a[port], %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
              "sbrc %[byte] , 7"        "\n\t" // 1-2  if(b & 128)
               "mov  %[next], %[hi]"    "\n\t" // 0-1   next = hi    (T =  4)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T =  6)
              "st   %a[port], %[next]"  "\n\t" // 2    PORT = next   (T =  8)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 10)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 12)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 14)
              "nop"                     "\n\t" // 1    nop           (T = 15)
              "st   %a[port], %[lo]"    "\n\t" // 2    PORT = lo     (T = 17)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 19)
              "dec  %[bit]"             "\n\t" // 1    bit--         (T = 20)
              "breq nextbyte30"         "\n\t" // 1-2  if(bit == 0)
              "rol  %[byte]"            "\n\t" // 1    b <<= 1       (T = 22)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 24)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 26)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 28)
              "rjmp head30"             "\n\t" // 2    -> head30 (next bit out)
             "nextbyte30:"              "\n\t" //                    (T = 22)
              "nop"                     "\n\t" // 1    nop           (T = 23)
              "ldi  %[bit]  , 8"        "\n\t" // 1    bit = 8       (T = 24)
              "ld   %[byte] , %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 26)
              "sbiw %[count], 1"        "\n\t" // 2    i--           (T = 28)
              "brne head30"             "\n"   // 1-2  if(i != 0) -> (next byte)
              : [port]  "+e" (port),
                [byte]  "+r" (b),
                [bit]   "+r" (bit),
                [next]  "+r" (next),
                [count] "+w" (i)
              : [hi]     "r" (hi),
                [lo]     "r" (lo),
                [ptr]    "e" (ptr));
          }
        #elif (F_CPU >= 15400000UL) && (F_CPU <= 19000000L)
          if(is800KHz) {
            volatile uint8_t next, bit;

            hi   = *port |  pinMask;
            lo   = *port & ~pinMask;
            next = lo;
            bit  = 8;

            asm volatile(
             "head20:"                   "\n\t" // Clk  Pseudocode    (T =  0)
              "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
              "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
               "mov  %[next], %[hi]"     "\n\t" // 0-1   next = hi    (T =  4)
              "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
              "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
              "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
              "breq nextbyte20"          "\n\t" // 1-2  if(bit == 0) (from dec above)
              "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
              "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
              "nop"                      "\n\t" // 1    nop           (T = 13)
              "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
              "nop"                      "\n\t" // 1    nop           (T = 16)
              "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
              "rjmp head20"              "\n\t" // 2    -> head20 (next bit out)
             "nextbyte20:"               "\n\t" //                    (T = 10)
              "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
              "ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
              "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
              "nop"                      "\n\t" // 1    nop           (T = 16)
              "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
               "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
              : [port]  "+e" (port),
                [byte]  "+r" (b),
                [bit]   "+r" (bit),
                [next]  "+r" (next),
                [count] "+w" (i)
              : [ptr]    "e" (ptr),
                [hi]     "r" (hi),
                [lo]     "r" (lo));
          } else {

            volatile uint8_t next, bit;

            hi   = *port |  pinMask;
            lo   = *port & ~pinMask;
            next = lo;
            bit  = 8;

            asm volatile(
             "head40:"                  "\n\t" // Clk  Pseudocode    (T =  0)
              "st   %a[port], %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
              "sbrc %[byte] , 7"        "\n\t" // 1-2  if(b & 128)
               "mov  %[next] , %[hi]"   "\n\t" // 0-1   next = hi    (T =  4)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T =  6)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T =  8)
              "st   %a[port], %[next]"  "\n\t" // 2    PORT = next   (T = 10)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 12)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 14)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 16)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 18)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 20)
              "st   %a[port], %[lo]"    "\n\t" // 2    PORT = lo     (T = 22)
              "nop"                     "\n\t" // 1    nop           (T = 23)
              "mov  %[next] , %[lo]"    "\n\t" // 1    next = lo     (T = 24)
              "dec  %[bit]"             "\n\t" // 1    bit--         (T = 25)
              "breq nextbyte40"         "\n\t" // 1-2  if(bit == 0)
              "rol  %[byte]"            "\n\t" // 1    b <<= 1       (T = 27)
              "nop"                     "\n\t" // 1    nop           (T = 28)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 30)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 32)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 34)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 36)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 38)
              "rjmp head40"             "\n\t" // 2    -> head40 (next bit out)
             "nextbyte40:"              "\n\t" //                    (T = 27)
              "ldi  %[bit]  , 8"        "\n\t" // 1    bit = 8       (T = 28)
              "ld   %[byte] , %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 30)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 32)
              "st   %a[port], %[lo]"    "\n\t" // 2    PORT = lo     (T = 34)
              "rjmp .+0"                "\n\t" // 2    nop nop       (T = 36)
              "sbiw %[count], 1"        "\n\t" // 2    i--           (T = 38)
              "brne head40"             "\n"   // 1-2  if(i != 0) -> (next byte)
              : [port]  "+e" (port),
                [byte]  "+r" (b),
                [bit]   "+r" (bit),
                [next]  "+r" (next),
                [count] "+w" (i)
              : [ptr]    "e" (ptr),
                [hi]     "r" (hi),
                [lo]     "r" (lo));
          }
        #else
         #error "CPU SPEED NOT SUPPORTED"
        #endif
        #elif defined(__arm__)


        #if defined(TEENSYDUINO) && defined(KINETISK) // Teensy 3.0, 3.1, 3.2, 3.5, 3.6
        #define CYCLES_800_T0H  (F_CPU / 4000000)
        #define CYCLES_800_T1H  (F_CPU / 1250000)
        #define CYCLES_800      (F_CPU /  800000)
        #define CYCLES_400_T0H  (F_CPU / 2000000)
        #define CYCLES_400_T1H  (F_CPU /  833333)
        #define CYCLES_400      (F_CPU /  400000)

          uint8_t          *p   = pixels,
                           *end = p + numBytes, pix, mask;
          volatile uint8_t *set = portSetRegister(pin),
                           *clr = portClearRegister(pin);
          uint32_t          cyc;

          ARM_DEMCR    |= ARM_DEMCR_TRCENA;
          ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;

          if(is800KHz) {
            cyc = ARM_DWT_CYCCNT + CYCLES_800;
            while(p < end) {
              pix = *p++;
              for(mask = 0x80; mask; mask >>= 1) {
                while(ARM_DWT_CYCCNT - cyc < CYCLES_800);
                cyc  = ARM_DWT_CYCCNT;
                *set = 1;
                if(pix & mask) {
                  while(ARM_DWT_CYCCNT - cyc < CYCLES_800_T1H);
                } else {
                  while(ARM_DWT_CYCCNT - cyc < CYCLES_800_T0H);
                }
                *clr = 1;
              }
            }
            while(ARM_DWT_CYCCNT - cyc < CYCLES_800);
          } else {
            cyc = ARM_DWT_CYCCNT + CYCLES_400;
            while(p < end) {
              pix = *p++;
              for(mask = 0x80; mask; mask >>= 1) {
                while(ARM_DWT_CYCCNT - cyc < CYCLES_400);
                cyc  = ARM_DWT_CYCCNT;
                *set = 1;
                if(pix & mask) {
                  while(ARM_DWT_CYCCNT - cyc < CYCLES_400_T1H);
                } else {
                  while(ARM_DWT_CYCCNT - cyc < CYCLES_400_T0H);
                }
                *clr = 1;
              }
            }
            while(ARM_DWT_CYCCNT - cyc < CYCLES_400);
          }
        #else
          #error "Sorry, only 48 MHz is supported, please set Tools > CPU Speed to 48 MHz"
        #endif
        #elif defined(ESP8266) || defined(ESP32)

          espShow(pin, pixels, numBytes, is800KHz);

        #elif defined(__ARDUINO_ARC__)

        // Arduino 101  -----------------------------------------------------------

        #define NOPx7 { __builtin_arc_nop(); \
          __builtin_arc_nop(); __builtin_arc_nop(); \
          __builtin_arc_nop(); __builtin_arc_nop(); \
          __builtin_arc_nop(); __builtin_arc_nop(); }

          PinDescription *pindesc = &g_APinDescription[pin];
          register uint32_t loop = 8 * numBytes; // one loop to handle all bytes and all bits
          register uint8_t *p = pixels;
          register uint32_t currByte = (uint32_t) (*p);
          register uint32_t currBit = 0x80 & currByte;
          register uint32_t bitCounter = 0;
          register uint32_t first = 1;

          if (pindesc->ulGPIOType == SS_GPIO) {
            register uint32_t reg = pindesc->ulGPIOBase + SS_GPIO_SWPORTA_DR;
            uint32_t reg_val = __builtin_arc_lr((volatile uint32_t)reg);
            register uint32_t reg_bit_high = reg_val | (1 << pindesc->ulGPIOId);
            register uint32_t reg_bit_low  = reg_val & ~(1 << pindesc->ulGPIOId);

            loop += 1;
            while(loop--) {
              if(!first) {
                currByte <<= 1;
                bitCounter++;
              }

              // 1 is >550ns high and >450ns low; 0 is 200..500ns high and >450ns low
              __builtin_arc_sr(first ? reg_bit_low : reg_bit_high, (volatile uint32_t)reg);
              if(currBit) { // ~400ns HIGH (740ns overall)
                NOPx7
                NOPx7
              }
              // ~340ns HIGH
              NOPx7
             __builtin_arc_nop();

              // 820ns LOW; per spec, max allowed low here is 5000ns */
              __builtin_arc_sr(reg_bit_low, (volatile uint32_t)reg);
              NOPx7
              NOPx7

              if(bitCounter >= 8) {
                bitCounter = 0;
                currByte = (uint32_t) (*++p);
              }

              currBit = 0x80 & currByte;
              first = 0;
            }
          } else if(pindesc->ulGPIOType == SOC_GPIO) {
            register uint32_t reg = pindesc->ulGPIOBase + SOC_GPIO_SWPORTA_DR;
            uint32_t reg_val = MMIO_REG_VAL(reg);
            register uint32_t reg_bit_high = reg_val | (1 << pindesc->ulGPIOId);
            register uint32_t reg_bit_low  = reg_val & ~(1 << pindesc->ulGPIOId);

            loop += 1; // include first, special iteration
            while(loop--) {
              if(!first) {
                currByte <<= 1;
                bitCounter++;
              }
              MMIO_REG_VAL(reg) = first ? reg_bit_low : reg_bit_high;
              if(currBit) { // ~430ns HIGH (740ns overall)
                NOPx7
                NOPx7
                __builtin_arc_nop();
              }
              // ~310ns HIGH
              NOPx7

              // 850ns LOW; per spec, max allowed low here is 5000ns */
              MMIO_REG_VAL(reg) = reg_bit_low;
              NOPx7
              NOPx7

              if(bitCounter >= 8) {
                bitCounter = 0;
                currByte = (uint32_t) (*++p);
              }

              currBit = 0x80 & currByte;
              first = 0;
            }
          }

        #else
        #error Architecture not supported
        #endif

        #ifndef NRF52
          interrupts();
        #endif

          endTime = micros();
        }

        void NeoPixel::setPin(uint8_t p) {
          if(begun && (pin >= 0)) pinMode(pin, INPUT);
            pin = p;
            if(begun) {
              pinMode(p, OUTPUT);
              digitalWrite(p, LOW);
            }
        #ifdef __AVR__
            port    = portOutputRegister(digitalPinToPort(p));
            pinMask = digitalPinToBitMask(p);
        #endif
        }

        void NeoPixel::setPixelColor(
         uint16_t n, uint8_t r, uint8_t g, uint8_t b) {

          if(n < numLEDs) {
            if(brightness) { // See notes in setBrightness()
              r = (r * brightness) >> 8;
              g = (g * brightness) >> 8;
              b = (b * brightness) >> 8;
            }
            uint8_t *p;
            if(wOffset == rOffset) {
              p = &pixels[n * 3];
            } else {
              p = &pixels[n * 4];
              p[wOffset] = 0;
            }
            p[rOffset] = r;
            p[gOffset] = g;
            p[bOffset] = b;
          }
        }

        void NeoPixel::setPixelColor(
         uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {

          if(n < numLEDs) {
            if(brightness) {
              r = (r * brightness) >> 8;
              g = (g * brightness) >> 8;
              b = (b * brightness) >> 8;
              w = (w * brightness) >> 8;
            }
            uint8_t *p;
            if(wOffset == rOffset) {
              p = &pixels[n * 3];
            } else {
              p = &pixels[n * 4];
              p[wOffset] = w;
            }
            p[rOffset] = r;
            p[gOffset] = g;
            p[bOffset] = b;
          }
        }

        void NeoPixel::setPixelColor(uint16_t n, uint32_t c) {
          if(n < numLEDs) {
            uint8_t *p,
              r = (uint8_t)(c >> 16),
              g = (uint8_t)(c >>  8),
              b = (uint8_t)c;
            if(brightness) {
              r = (r * brightness) >> 8;
              g = (g * brightness) >> 8;
              b = (b * brightness) >> 8;
            }
            if(wOffset == rOffset) {
              p = &pixels[n * 3];
            } else {
              p = &pixels[n * 4];
              uint8_t w = (uint8_t)(c >> 24);
              p[wOffset] = brightness ? ((w * brightness) >> 8) : w;
            }
            p[rOffset] = r;
            p[gOffset] = g;
            p[bOffset] = b;
          }
        }

        uint32_t NeoPixel::Color(uint8_t r, uint8_t g, uint8_t b) {
          return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
        }

        uint32_t NeoPixel::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
          return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
        }

        uint32_t NeoPixel::getPixelColor(uint16_t n) const {
          if(n >= numLEDs) return 0;

          uint8_t *p;

          if(wOffset == rOffset) {
            p = &pixels[n * 3];
            if(brightness) {

              return (((uint32_t)(p[rOffset] << 8) / brightness) << 16) |
                     (((uint32_t)(p[gOffset] << 8) / brightness) <<  8) |
                     ( (uint32_t)(p[bOffset] << 8) / brightness       );
            } else {
              return ((uint32_t)p[rOffset] << 16) |
                     ((uint32_t)p[gOffset] <<  8) |
                      (uint32_t)p[bOffset];
            }
          } else {
            p = &pixels[n * 4];
            if(brightness) {
              return (((uint32_t)(p[wOffset] << 8) / brightness) << 24) |
                     (((uint32_t)(p[rOffset] << 8) / brightness) << 16) |
                     (((uint32_t)(p[gOffset] << 8) / brightness) <<  8) |
                     ( (uint32_t)(p[bOffset] << 8) / brightness       );
            } else {
              return ((uint32_t)p[wOffset] << 24) |
                     ((uint32_t)p[rOffset] << 16) |
                     ((uint32_t)p[gOffset] <<  8) |
                      (uint32_t)p[bOffset];
            }
          }
        }


        uint8_t *NeoPixel::getPixels(void) const {
          return pixels;
        }

        uint16_t NeoPixel::numPixels(void) const {
          return numLEDs;
        }

        void NeoPixel::setBrightness(uint8_t b) {

          uint8_t newBrightness = b + 1;
          if(newBrightness != brightness) {
            uint8_t  c,
                    *ptr           = pixels,
                     oldBrightness = brightness - 1;
            uint16_t scale;
            if(oldBrightness == 0) scale = 0; // Avoid /0
            else if(b == 255) scale = 65535 / oldBrightness;
            else scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
            for(uint16_t i=0; i<numBytes; i++) {
              c      = *ptr;
              *ptr++ = (c * scale) >> 8;
            }
            brightness = newBrightness;
          }
        }

        uint8_t NeoPixel::getBrightness(void) const {
          return brightness - 1;
        }

        void NeoPixel::clear() {
          memset(pixels, 0, numBytes);
        }

        static const uint8_t PROGMEM _sineTable[256] = {
          128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,
          176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,
          218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,
          245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,
          255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,
          245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,
          218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,
          176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,
          128,124,121,118,115,112,109,106,103,100, 97, 93, 90, 88, 85, 82,
           79, 76, 73, 70, 67, 65, 62, 59, 57, 54, 52, 49, 47, 44, 42, 40,
           37, 35, 33, 31, 29, 27, 25, 23, 21, 20, 18, 17, 15, 14, 12, 11,
           10,  9,  7,  6,  5,  5,  4,  3,  2,  2,  1,  1,  1,  0,  0,  0,
            0,  0,  0,  0,  1,  1,  1,  2,  2,  3,  4,  5,  5,  6,  7,  9,
           10, 11, 12, 14, 15, 17, 18, 20, 21, 23, 25, 27, 29, 31, 33, 35,
           37, 40, 42, 44, 47, 49, 52, 54, 57, 59, 62, 65, 67, 70, 73, 76,
           79, 82, 85, 88, 90, 93, 97,100,103,106,109,112,115,118,121,124};

        static const uint8_t PROGMEM _gammaTable[256] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,
            1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,
            3,  3,  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  7,
            7,  7,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11, 11, 11, 12, 12,
           13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20,
           20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 29,
           30, 31, 31, 32, 33, 34, 34, 35, 36, 37, 38, 38, 39, 40, 41, 42,
           42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
           58, 59, 60, 61, 62, 63, 64, 65, 66, 68, 69, 70, 71, 72, 73, 75,
           76, 77, 78, 80, 81, 82, 84, 85, 86, 88, 89, 90, 92, 93, 94, 96,
           97, 99,100,102,103,105,106,108,109,111,112,114,115,117,119,120,
          122,124,125,127,129,130,132,134,136,137,139,141,143,145,146,148,
          150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,
          182,184,186,188,191,193,195,197,199,202,204,206,209,211,213,215,
          218,220,223,225,227,230,232,235,237,240,242,245,247,250,252,255};

        uint8_t NeoPixel::sine8(uint8_t x) const {
          return pgm_read_byte(&_sineTable[x]); // 0-255 in, 0-255 out
        }

        uint8_t NeoPixel::gamma8(uint8_t x) const {
          return pgm_read_byte(&_gammaTable[x]); // 0-255 in, 0-255 out
        }

        ///@endcond
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
        #define EBOARD_I2C 0x1
        @endcode
        If you use the ARDUINO MEGA the I2C pins are not A4 (SDA) and A5 (SDL). They are seperate (20-SDA;21-SDL)!

        - It is possible to send Data via I2C with sendI2C() \n
        - It is possible to read Data via I2C with readI2C() \n
        - It is possible to scan for I2C addresses with pingI2C(); \n
        @section example Example
        An Example of how to scan for I2C addresses:
        @code
        #define EBOARD_I2C 0x1
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

        @image html bt.jpg

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

        @image html t.png

        @note it is possible to extend the amount of shiftregisters. This version of eBoard supports up to 32 (64) additional pins. \n But it is possible to connect even more!

        To assign this pins with the special values you can use the SoccerBoard::power() [SoccerBoard::powerOn(); SoccerBoard::powerOff()] Syntax with pinIDs >99 [100 => 0 etc.]
        This is an example-program:
        @code
        #define EBOARD_SHIFT_REGISTER 0x1
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

        @image html lcd_pr.jpg

        @note It is possible to connect multiple devices via I²C ! Just forward the SCL and SDA lines
    */

    /**
        @addtogroup genExpl
        @brief This tutorial is a brief introduction on how to use this headerfile

        @section gen General

        @subsection genH1 Hardware

        This header is compatible with:
            - Arduino UNO
            - Arduino NANO (with ATmega328P)
            - Arduino MEGA (with ATmega2560)

        Several functionalities like AX12Servo need special hardware:
        - AX12Servo and DynamixelBoard work with the Smart Servo Shield
        - RB14Scan works with the HC-05 Bluetooth module
        - LCD works with the OLED 128x64 Display
        - I2CInOut works with any PWM driven motor (ctrl)
        - NeoPixel works with the Adafruit LED-stripes \n

          @image html hardware.png

        @subsection genH2 Software

        This headerfile was created to enable the port of qfixSoccerBoard code to the Arduino platform.
        Therefore there are a few changes when coding for the arduino:
          - there is no setup() and loop() inside your ino file! \n
            you have to use int main() which is called inside of the arduino 'setup'
          - you don't have to do include Wire SPI and SoftwareSerial(Uno) manually! \n
            They are coded into the header

        This is an example code (doing nothing but compile :D)
        @code
        #include "/eagleoutice/projects/github/eBoard/docs/eBoard.h"
        SoccerBoard board;
        int main() {
          //cool stuff in here ;D
          return 0;
        }
        @endcode
    */

    /**
     * @defgroup portTu [ 🐼 ] UNO2MEGA
     *
     */
    /**
        @addtogroup portTu
        @brief This tutorial shows you how to 'port' code and setup from the Arduino UNO R3 to the Arduino MEGA R3

        @pre Layout of UNO R3 and MEGA R3:
            @image html Layouts.svg

        @section sprt1 Software

        If you haven't changed any Pin-configuration there is no need to change anything with the code! :D

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
            #if EBOARD_USE_SPI > 0x0 && (EBOARD_NANO == 0)
                _servoHandler.begin(); //Setup SPI
            #endif

            #if EBOARD_DEBUG_MODE > 0x0
                Serial.print(eVirtual_main());
                Serial.println(" -- Exit Code. \n Program has finished. Reset to start again");
            #else
                eVirtual_main();
            #endif
            if (STOP) {} //prevent unused error
            delay(200);
            cli(); //disable timers after running the program :D
            writePWM(0);analogWrite(PIN_MOTOR_SPE,0);
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
#pragma pack(pop)

#endif
