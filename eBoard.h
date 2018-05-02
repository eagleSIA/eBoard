//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 02.05.2018 21:53:42

#ifndef EBOARD_HEADER_GUARD
   #define EBOARD_HEADER_GUARD
	 #pragma GCC diagnostic push
	 #pragma GCC diagnostic ignored "-Wall"
	 #pragma GCC diagnostic ignored "-Wextra"
	 #pragma pack(push)
	 #pragma pack(16)
	 #include "source/eagle_PreprocessorControl.h"
	 
	 #define EBOARD_VERSION "3.1.25m"
	 
	 #define EBOARD_VERSION_NBR 335
  DEBUG_MSG("If you do not want any preprocessing information from this eBoard-Header set PREPROCESS_DEBUG to 0");
 //i am a guard... leave me alone :D
#if defined(ARDUINO) //general platform-check [No tab]
    #include <avr/pgmspace.h>
        namespace eagle_impl {}
    using namespace eagle_impl;
    #ifndef EBOARD_GUESSPATH
      DEBUG_MSG("You are using Guesspath! Necessary libraries for eBoard will be included automatically");
            #define EBOARD_GUESSPATH 0x1
    #else
      DEBUG_MSG("You are not using Guesspath! Necessary libraries for eBoard have to be included manually");
    #endif
        #define main eVirtual_main //main has a different meaning^^
   #if ARDUINO >= 100  //this could be only Arduino.h but this snippet is portable :D
        #include "Arduino.h"
    #else
        #include <wiring.h>
    #endif
   #if not ( defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328P__))
        #error "This library was build for ARDUINO UNO R3 Aand ARDUINO MEGA 2560!"
    #endif
		#include "source/eagle_Comfort.h"
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
      DEBUG_MSG("You enabled I²C features");
      #ifndef twi_h
        #define twi_h
        #ifndef TwoWire_h //because it will be included ._.
          //#define ATMEGA8
          #include "source/eagle_Twi.h"
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
   
    #ifdef EBOARD_HELPCAR
        DEBUG_MSG("You switched to helpcar and disabled SPI");
        #define EBOARD_USE_SPI 0x0
    #endif
    
    #if EBOARD_USE_SPI > 0x0
      DEBUG_MSG("You enabled SPI");
      #ifndef _SPI_H_INCLUDED
        
        #define _SPI_H_INCLUDED
        #include "source/eagle_SPI.h"
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
   #ifdef EBOARD_HELPCAR
      #ifndef EBOARD_HELPCAR_STEER
              #define EBOARD_HELPCAR_STEER 12
      #endif
      #ifndef EBOARD_HELPCAR_MAIN
              #define EBOARD_HELPCAR_MAIN 13
      #endif
      MACRO_MSG(EBOARD_NANO,"Using Arduino Helpcar environment [e.g. remove AX12Servo]");
      #if PREPROCESS_DEBUG > 0x1
        #pragma message("Using " VALUE(EBOARD_HELPCAR_STEER) " as data pin for STEERING MOTOR")
        #pragma message("Using " VALUE(EBOARD_HELPCAR_MAIN) " as data pin for MAIN (Driving) MOTOR")
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
    #ifdef EBOARD_HELPCAR
        //offer more functions
        #if EBOARD_GUESSPATH > 0x0
            #include "source/eagle_Servo.h"
            Servo mainMotor,steerMotor;
        #endif
    #endif
    #if EBOARD_DEBUG_MODE > 0x0
                #define __ASSERT_USE_STDERR
        #include "source/eagle_Assert.h"
    #endif
    #include "source/eagle_Checks.h"
    #if EBOARD_BLUETOOTH > 0x0
      #include "source/eagle_Bluetooth.h"
    #endif
   #if EBOARD_SHIFT_REGISTER > 0x0
      #include "source/eagle_ShiftExt.h"
    #endif
   #include "source/eagle_PinCtrl.h"
   #ifdef REPT_TASK
        extern void rept_task(void);
//         DEBUG_MSG("You defined REPT_TASK: you have to define rept_task(void)!");
    #else
        DEBUG_MSG("You did not define REPT_TASK: rept_task(void) will not have any effect");
    #endif
   #if EBOARD_USE_SPI > 0x0 && (EBOARD_NANO == 0x0)
        #include "source/eagle_ServoCds55.h"
       
        ServoCds55 _servoHandler;
    #endif
   #if EBOARD_COPY_AND_PASTE > 0x0 && EBOARD_NANO == 0
        #include "source/eagle_SoccerBoard.h"
        #include "source/eagle_I2CInOut.h"
        #ifndef EBOARD_HELPCAR
            #include "source/eagle_AX12Servo.h"
            #include "source/eagle_DynamixelBoard.h"
        #endif
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
 #if EBOARD_COPY_AND_PASTE > 0x0
        #include "source/eagle_ReptTask.h"
        #include "source/eagle_Setup.h"
        
        void loop(void);
        
        void loop(void){
          //shall be empty
          }
        
  #endif
  #if defined(EBOARD_HELPCAR)
  #include "source/eagle_HelpMot.h"
  #endif
#else
  #error This library is build for arduino-devices and should be used only in the Arduino IDE or with a similar linking process
#endif
#pragma GCC diagnostic pop
#pragma pack(pop)
#endif
