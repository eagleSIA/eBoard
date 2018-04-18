//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 18.04.2018 23:34:37

#ifndef EBOARD_HEADER_GUARD
     #define EBOARD_HEADER_GUARD
     #pragma GCC diagnostic push
     #pragma GCC diagnostic ignored "-Wall"
     #pragma GCC diagnostic ignored "-Wextra"
     #pragma pack(push)
     #pragma pack(16)
#define EBOARD_VERSION "3.1.15m"
#define EBOARD_VERSION_NBR 325
#define VALUE_TO_STRING(x) #x

    #ifdef DOC

    #define PREPROCESS_DEBUG 1
    #endif
#define VALUE(x) VALUE_TO_STRING(x)
#ifndef PREPROCESS_DEBUG
      #define PREPROCESS_DEBUG 0
     #endif

     #define PPERFORM_PRAGMA(str) _Pragma(#str)
     #if PREPROCESS_DEBUG == 1
      #define DEBUG_MSG(str) PPERFORM_PRAGMA(message ("" #str))
      #define MACRO_MSG(mac,str) PPERFORM_PRAGMA(message("You set " #mac " to " VALUE(mac) ": " #str))
     #else
      #define DEBUG_MSG(str) ;
      #define MACRO_MSG(mac,str) ;
     #endif
DEBUG_MSG("If you do not want any preprocessing information from this eBoard-Header set PREPROCESS_DEBUG to 0");
     DEBUG_MSG("You are using eBoard-header v3.1m written by EagleoutIce");




















    //i am a guard... leave me alone :D
   #ifdef DOC
        DEBUG_MSG("Documentation macro SET => Full doc features enabled");
        #define ARDUINO 200

        #define EBOARD_I2C 0x1

        #define EBOARD_LCD 0x1

        #define EBOARD_SHIFT_REGISTER 0x1

        #define EBOARD_BLUETOOTH 0x1

        #define REPT_TASK

        #define __AVR_ATmega2560__

        #define __AVR_ATmega328P__

        #define EBOARD_NEO 0x1

        #define HIGHSPEED

        #define __AVR__
    #endif

    int sine8(uint8_t val){
      return int((__builtin_sin((val/128.0*PI))+1)*127.5+0.5);
    }

    int gamma8(uint8_t val){
      return int(pow((val)/255.0,2.6)*255.0+0.5);
    }
    #include <avr/pgmspace.h>

    namespace eagle_impl {}
    using namespace eagle_impl;
    #ifndef EBOARD_GUESSPATH
      DEBUG_MSG("You are using Guesspath! Necessary libraries for eBoard will be included automatically");

      #define EBOARD_GUESSPATH 0x1
    #else
      DEBUG_MSG("You are not using Guesspath! Necessary libraries for eBoard have to be included manually");
    #endif
    #if defined(ARDUINO) //general platform-check [No tab]

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
      DEBUG_MSG("Building for Arduino Mega with ATmega2560");

        #define PIN_MAX 0x32 //53 pins to address - 4 !!53 is SS
    #else
    DEBUG_MSG("Building for Arduino Uno or Nano with ATmega328P");
        #define PIN_MAX 0xA // 13 Pins to address - 4 !!10 is SS
    #endif
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #if EBOARD_I2C > 0x0 && EBOARD_GUESSPATH > 0x0
      DEBUG_MSG("You enabled I²C featurea");
      #ifndef twi_h
      #define twi_h
      #ifndef TwoWire_h //because it will be included ._.
      //#define ATMEGA8
      #include "source/eagle_twi.h"
      #endif
      #endif
      #ifndef TwoWire_h
      #include "source/eagle_TwoWire.h"
      #endif
      #else
      DEBUG_MSG("You disabled I²C");
      #endif

      #ifndef EBOARD_USE_SPI
          #define EBOARD_USE_SPI 0x1
      #endif
    #if EBOARD_USE_SPI > 0x0
      DEBUG_MSG("You enabled SPI");
      #ifndef _SPI_H_INCLUDED

      #define _SPI_H_INCLUDED
      #include <stdio.h>

      #define SPI_CLOCK_DIV4 0x00

      #define SPI_CLOCK_DIV16 0x01

      #define SPI_CLOCK_DIV64 0x02

      #define SPI_CLOCK_DIV128 0x03

      #define SPI_CLOCK_DIV2 0x04

      #define SPI_CLOCK_DIV8 0x05

      #define SPI_CLOCK_DIV32 0x06

      #define SPI_MODE0 0x00

      #define SPI_MODE1 0x04

      #define SPI_MODE2 0x08

      #define SPI_MODE3 0x0C

      #define SPI_MODE_MASK 0x0C

      #define SPI_CLOCK_MASK 0x03

      #define SPI_2XCLOCK_MASK 0x01
      namespace eagle_impl {

        struct SPIClass {

          inline static byte transfer(byte _data);

          inline static void attachInterrupt(void);

          inline static void detachInterrupt(void); // Default

          static void begin(void); // Default

          inline static void end(void);

          inline static void setBitOrder(uint8_t bitOrder);

          inline static void setDataMode(uint8_t mode);

          inline static void setClockDivider(uint8_t rate);
        };
      }

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

      SPIClass SPI;
      #endif
    #else
    DEBUG_MSG("You disabled SPI");
    #endif
    #if (EBOARD_I2C > 0x0) && (EBOARD_LCD > 0x0)
        #include <avr/pgmspace.h>
        DEBUG_MSG("You enabled LCD");
    #endif

    static bool STOP = false;

    #ifdef IGNORE_SIZE
      DEBUG_MSG("You defined IGNORE_SIZE: byte will be used");
        typedef byte optVAL_t;
    #else
    DEBUG_MSG("You did not define IGNORE_SIZE: int will be used");
        typedef int optVAL_t;
    #endif

    #ifndef EBOARD_DEBUG_MODE
        #define EBOARD_DEBUG_MODE 0x1
    #endif
    #if EBOARD_DEBUG_MODE > 0x0
    MACRO_MSG(EBOARD_DEBUG_MODE,"Serial feedback will be send to Computer");
    #else
    MACRO_MSG(EBOARD_DEBUG_MODE, "No Serial feedback!");
    #endif

    #ifndef EBOARD_NANO
      #define EBOARD_NANO 0x0
    #endif
    #if EBOARD_NANO > 0x0 || defined(DOC)
      #ifndef EBOARD_NANO_STEER

        #define EBOARD_NANO_STEER 12
      #endif
      #ifndef EBOARD_NANO_MAIN

        #define EBOARD_NANO_MAIN 13
      #endif
      MACRO_MSG(EBOARD_NANO,"Using Arduino NANO environment [e.g. remove SoccerBoard]");
      #if PREPROCESS_DEBUG > 0x1
        #pragma message("Using " VALUE(EBOARD_NANO_STEER) " as data pin for STEERING MOTOR")
        #pragma message("Using " VALUE(EBOARD_NANO_MAIN) " as data pin for MAIN (Driving) MOTOR")
      #endif
    #else
      MACRO_MSG(EBOARD_NANO,"Using Arduino UNO/MEGA environment");
    #endif

    #ifndef EBOARD_CHECK_PINS
        #define EBOARD_CHECK_PINS 0x1
    #endif
    #if EBOARD_CHECK_PINS > 0x0
      MACRO_MSG(EBOARD_CHECK_PINS,"Check for Pins enabled");
    #else
      MACRO_MSG(EBOARD_CHECK_PINS,"Check for Pins disabled");
    #endif
    #ifndef EBOARD_SHIFT_REGISTER

        #define EBOARD_SHIFT_REGISTER 0x0
    #endif
    #if EBOARD_SHIFT_REGISTER > 0x0
      MACRO_MSG(EBOARD_SHIFT_REGISTER,"Shiftregister enabled");
    #else
      MACRO_MSG(EBOARD_SHIFT_REGISTER,"Shiftregister disabled");
    #endif

    #ifndef EBOARD_CHECK_PINS_PWM
        #define EBOARD_CHECK_PINS_PWM 0x1
    #endif
    #if EBOARD_CHECK_PINS_PWM > 0x0
      MACRO_MSG(EBOARD_CHECK_PINS_PWM,"Check for PWM-Pins enabled");
    #else
      MACRO_MSG(EBOARD_CHECK_PINS_PWM,"Check for PWM-Pins disabled");
    #endif

    #ifndef EBOARD_DEBUG_SPEED
        #define EBOARD_DEBUG_SPEED 9600
    #endif
    #if PREPROCESS_DEBUG > 0x0
    #pragma message("Set Debugging speed to " VALUE(EBOARD_DEBUG_SPEED))
    #endif

    #ifndef EBOARD_SPI_SERVO_MAX
        #define EBOARD_SPI_SERVO_MAX 2
    #endif
    #if PREPROCESS_DEBUG > 0x0
    #pragma message("Set amount of used Servos to " VALUE(EBOARD_SPI_SERVO_MAX))
    #endif

    #ifndef EBOARD_USE_UTILITY
        #define EBOARD_USE_UTILITY 0x1
    #endif
    #if EBOARD_USE_UTILITY > 0x0
      MACRO_MSG(EBOARD_USE_UTILITY,"Utility features will be implemented");
    #else
      MACRO_MSG(EBOARD_USE_UTILITY,"Utility features will not be implemented");
    #endif

    #define EBOARD_COPY_AND_PASTE 0x1

    #ifndef EBOARD_PWM_SPE
        #define EBOARD_PWM_SPE 1
    #endif
    #if PREPROCESS_DEBUG > 0x0
    #pragma message("Set PWM interval to " VALUE(EBOARD_PWM_SPE) "s")
    #endif
    #ifndef EBOARD_I2C

        #define EBOARD_I2C 0x0 //disabled by default
    #endif
    #ifndef EBOARD_BLUETOOTH

        #define EBOARD_BLUETOOTH 0x0
    #endif
    #if EBOARD_BLUETOOTH > 0x0
      MACRO_MSG(EBOARD_BLUETOOTH,"Bluetooth controls enabled");
    #else
      MACRO_MSG(EBOARD_BLUETOOTH,"Bluetooth controls disabled");
    #endif

    #ifndef EBOARD_CLAMP
        #define EBOARD_CLAMP 0x1
    #endif
    #if EBOARD_CLAMP > 0x0
      MACRO_MSG(EBOARD_CLAMP,"Motor Range is set to [0;1023]");
    #else
      MACRO_MSG(EBOARD_CLAMP,"Motor Range is set to [-300;300]");
    #endif
    #ifndef EBOARD_NEO

      #define EBOARD_NEO 0x0
    #endif
    #if EBOARD_NEO > 0x0
      MACRO_MSG(EBOARD_NEO,"Adafruit Neo-Pixel support enabled");
    #else
      MACRO_MSG(EBOARD_NEO,"Adafruit Neo-Pixel support disabled");
    #endif

    #ifndef EBOARD_USE_RESET
        #define EBOARD_USE_RESET 0x1
    #endif
    #if EBOARD_USE_RESET > 0x0
        #include <avr/wdt.h>
        MACRO_MSG(EBOARD_USE_RESET,"Software-Reset is available" );
    #else
        MACRO_MSG(EBOARD_USE_RESET,"Software-Reset is not available" );
    #endif

    #ifndef PIN_BLUETOOTH_STATE
        #if defined(__AVR_ATmega2560__)
            #define PIN_BLUETOOTH_STATE 0x13 // 19
        #else
            #define PIN_BLUETOOTH_STATE 0x2
        #endif
    #endif

    #ifndef PIN_BLUETOOTH_RX
        #if defined(__AVR_ATmega2560__)
            #define PIN_BLUETOOTH_RX 0x13 // 19
        #else
            #define PIN_BLUETOOTH_RX 0x2
        #endif
    #endif

    #ifndef PIN_BLUETOOTH_TX
        #if defined(__AVR_ATmega2560__)
            #define PIN_BLUETOOTH_TX 0x12 // 18
        #else
            #define PIN_BLUETOOTH_TX 0x3
        #endif
    #endif

    #ifndef PIN_MOTOR_DIR
        #define PIN_MOTOR_DIR 0x4
    #endif

    #ifndef PIN_MOTOR_SPE
        #define PIN_MOTOR_SPE 0x5
    #endif

    #ifndef PIN_SHIFT_CLK
        #define PIN_SHIFT_CLK 0x6
    #endif

    #ifndef PIN_SHIFT_DAT
        #define PIN_SHIFT_DAT 0x7
    #endif

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
        #ifndef SoftwareSerial_h
         //again to resolve including errors we'll include the SoftwareSerial cpp file
         #define SoftwareSerial_h
          #include "source/eagle_SoftwareSerial.h"
        #endif
      #endif

        SoftwareSerial _serial(PIN_BLUETOOTH_RX,PIN_BLUETOOTH_TX);
    #endif
    #if EBOARD_DEBUG_MODE > 0x0

        #define __ASSERT_USE_STDERR
        #include "source/eagle_assert.h"
    #endif
    #include "source/eagle_checks.h"
    #if EBOARD_BLUETOOTH > 0x0
      #include "source/eagle_bluetooth.h"
    #endif
    #if EBOARD_SHIFT_REGISTER > 0x0
      #include "source/eagle_shiftExt.h"
    #endif
    #include "source/eagle_pinCtrl.h"
    #ifdef REPT_TASK
        extern void rept_task(void);
        DEBUG_MSG("You defined REPT_TASK: you have to define rept_task(void)!");
    #else
        DEBUG_MSG("You did not define REPT_TASK: rept_task(void) will not have any effect");
    #endif
    #if EBOARD_USE_SPI > 0x0 && (EBOARD_NANO == 0x0)
        #include "source/eagle_ServoCds55.h"

        ServoCds55 _servoHandler;
    #endif
    #if EBOARD_COPY_AND_PASTE > 0x0 && EBOARD_NANO == 0
        #include "source/eagle_soccerBoard.h"
        #include "source/eagle_I2CInOut.h"
        #include "source/eagle_AX12Servo.h"
        #include "source/eagle_DynamixelBoard.h"
       #endif
        #if EBOARD_BLUETOOTH > 0x0
          #include "source/eagle_RB14Scan.h"
    #endif
#if EBOARD_I2C > 0x0
        #include "source/eagle_I2C.h"
        //Beginof LCD configuration
        #if EBOARD_LCD > 0x0
        #include "source/eagle_LCD.h"
        #endif
        #endif
        #if EBOARD_NEO > 0x0
          #include "source/eagle_NeoPixel.h"
        #endif
#if EBOARD_NANO > 0x0 || defined(DOC)
//offer more functions
  #if EBOARD_GUESSPATH > 0x0
    #include "source/eagle_Servo.h"
  #endif
#endif
#if EBOARD_COPY_AND_PASTE > 0x0
    void trig_rept_task() {
        if (_pwmValue!=_OpwmValue){
          analogWrite(PIN_MOTOR_SPE,_pwmValue);
          _OpwmValue = _pwmValue;
        }
          #ifdef REPT_TASK
              rept_task();
          #endif
      }
        #if EBOARD_NANO > 0x0
          Servo mainMotor,steerMotor;
        #endif
        int timer_count = 0;
        bool timer_ofl = false;
        ISR(TIMER2_OVF_vect) {
          timer_count++;
          if(timer_count >= EBOARD_PWM_SPE*1000 && !timer_ofl){
            timer_ofl = true;
            timer_count -= EBOARD_PWM_SPE*1000;
            trig_rept_task();
            timer_ofl = false;
          }
          TCNT2 =  256 - (int)((float)F_CPU * 0.001 / 64);
        }
        #include "source/eagle_setup.h"

        void loop(void);

        void loop(void){
          //shall be empty
          }

#endif
#if EBOARD_NANO > 0x0 || defined(DOC)
  #include "eagle_nanoMot.h"
#endif
#else
    #error This library is build for arduino-devices and should be used only in the Arduino IDE or with a similar linking process
#endif
#pragma GCC diagnostic pop
#pragma pack(pop)
#endif
