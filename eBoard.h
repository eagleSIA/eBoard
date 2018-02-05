///EagleoutIce 2018
///IF YOU SEE THIS THIS IS THE UNPROCESSED FILE! GO TO 'SOURCE CODE' IN THE DOCS
/**
 * @file eBoard.h
 * @todo 1. include, if necessary, support for rb14scan
 * @todo 2. test position-ranges for smart-servo-shield control
 * @todo 3. clean code :D
 * @todo 4. bluetooth connection via I²C?
 */
/**
 @mainpage eBoard  - shackle the Arduino!

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

 While in development you shouldn't change any macro...
 If you change to release mode, write the following before all includings:
 @code
 #define EBOARD_DEBUG_MODE 0x0
 @endcode


 @section s1 Macros
 There are multiple macros you can manipulate the behaviour of this header:
 @note The constants will appear with their default values in codeSnippets -> be careful with assumptions ;)

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

 - #PIN_BLUETOOTH_RX         : pinID(0) of RX-Pin
 - #PIN_BLUETOOTH_TX         : pinID(1) of TX-Pin
 - #PIN_MOTOR_DIR            : pinID(4) for MotorControl [DIR]
 - #PIN_MOTOR_SPE            : pinID(5) for MotorControl [SPE]
 - #PIN_SHIFT_CLK            : pinID(6) of shift-Clock
 - #PIN_SHIFT_DAT            : pinID(7) of shift-Data
 - #PIN_SHIFT_LAT            : pinID(8) of shift-Latch

 @section s2 Smart Servo Shield
 @image html /home/eagleoutice/Dokumente/proj/_sia/sss.jpeg
 @image latex /home/eagleoutice/Dokumente/proj/_sia/sss.jpeg
 This is the smart-servo shield this code was written for its connected by SPI with the UNO R3

 @section s4 Philosphy
 On small projects I prefer the single-file header! \n Your able to 'manage the includings' via the preprocessor constants

 @section s3 Examples
 @todo fill with more examples^^

 - @ref i2c
 - @ref shift
*/

/**
 @page page1 About
 @author Florian Sihler - EagleoutIce
 @copyright EagleoutIce 2018
 @version 1.0d
 @date 4.2.2018

 @section m1 Motivation
 This header was created to port SoccerBoard-Code to the Arduino UNO R3 \n
 It was written ~250 minutes and documented by Doxygen 1.8.15. \n


 @section m2 General Information
 I am a 18-year old programmer and I am coding since i was a kid. \n
 @warning Any Errors or Bugs? florian.sihler@web.de



  @image html /home/eagleoutice/Dokumente/proj/_sia/pp.jpeg
  @image latex /home/eagleoutice/Dokumente/proj/_sia/pp.jpeg
*/

/**
  @page i2c I2C-Functionality
  @note To use this:
  @code
  #EBOARD_I2C 0x1
  @endcode
  It is possible to send Data via I2C with sendI2C() \n
  It is also possible to scan for I2C addresses with pingI2C();
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
  @note To use this:
  @code
  #EBOARD_SHIFT_REGISTER 0x1
  @endcode
  It is possible to set a Data of a single Pin with shiftSingle();
  It is also possible to shift the modified #store_bits with shiftAll();
  @section ex Example
  Connect the SN74HC595(s) like the following:
  @todo insert image of wiring

  No your able to run this code:
  @todo insert code

*/
//i am a guard... leave me alone :D
#ifndef EBOARD_HEADER_GUARD
#define EBOARD_HEADER_GUARD

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

/**
 * @note set this to 0x1 to enable the control for shiftregister
 * @note for the docs it will appear as a 0x1 but the default value is 0x0
 */
#ifndef EBOARD_SHIFT_REGISTER
  #define EBOARD_SHIFT_REGISTER 0x0
#else
  #define EBOARD_SHIFT_REGISTER 0x1
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
 * @note set this to 0x1 to enable internal I2C support
 * @note for the docs it will appear as a 0x1 but the default value is 0x0
 */
#ifndef EBOARD_I2C
  #define EBOARD_I2C 0x0 //disabled by default
#else
  #define EBOARD_I2C 0x1 //for the doc :D
#endif

/**
 * @note this is the RX-Pin reserved for bluetooth communictaion
 */
#ifndef PIN_BLUETOOTH_RX
  #define PIN_BLUETOOTH_RX 0x0
#endif

/**
 * @note this is the TX-Pin reserved for bluetooth communictaion
 */
#ifndef PIN_BLUETOOTH_TX
  #define PIN_BLUETOOTH_TX 0x1
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
    @code
    Error with: checkIdx in /home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h @222
             >>idx>0x1 && idx < 0xA
       This happens if an out of bounds exception
       has occured. Following pins shouldn't be used:
       D0&D1 : Used for Bluetooth communictaion
       D4&D5 : Used for main motor control
       D10-13: Used for smart-servo-shield
    @endcode
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
    assert(idx>0x1 && idx < 0xA); //changed pins? change me! (didn't want to use macros)
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
        optVAL_t count;
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
    @ @brief I prevent errors! if the pin is in the requested mode
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
    pinMode((idx!=0x3)?(idx+0x2):(idx), mode);
  }
  ///@endcond
#endif

#if EBOARD_I2C > 0x0
/**
    @brief Sends a buffer of bytes to a certain I2C-Device
    @note Using I2C won't block the analog pins!
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
  @brief Sends a byte to a certain I2C-Device
  @note Using I2C won't block the analog pins!
  @param ret an array of optVAL_t
  @param ret_len the length of the array
*/
inline void pingI2C(optVAL_t ret[], optVAL_t ret_len);
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
///@cond
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

//As long as it isn't needed there won't be a read function
/*inline byte readI2C(optVAL_t deviceID,optVAL_t rec_length,bool blocking=true,bool request=true);
inline byte readI2C(optVAL_t deviceID,optVAL_t rec_length,bool blocking,bool request) {
  char ret_buf[rec_length];
  optVAL_t rect = 0x0;
  if(request)
    Wire.requestFrom(deviceID,rec_length);

  while(Wire.available() || (blocking && rect < rec_length)){

  }
}*/


#endif


#if EBOARD_SHIFT_REGISTER > 0x0
long store_bits = 0L;

void shiftSingle(optVAL_t idx, bool val);
void shiftAll(void);
///@cond
void shiftSingle(optVAL_t idx, bool val) {
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

/*!
  @brief write a clamped pwm value to an output pin
  @warning if you spam this command to fast the motor will fail to sync and may crash there is no internal handling of this error
  @param idx  the index of the pin to use
  @param val  the pwm value [0-255] to use
 */
 inline void writePWM(optVAL_t idx, optVAL_t val);
 ///@cond
inline void writePWM(optVAL_t idx, optVAL_t val){
  #if EBOARD_CHECK_PINS_PWM > 0x0
  val = min(val,0xFF); val = max(0x0,val); //bind
  if(!(idx>0x0 && idx <0xA && countSetBits(idx) == 2))
  if(!checkPin(idx))
  #endif
  #if EBOARD_COPY_AND_PASTE > 0x0
  setPin(idx);
  #else
   pinMode(idx,OUTPUT);
   #endif
  analogWrite(idx,val);
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
      ServoCds55(int CS=10);
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
      void write(optVAL_t ID,optVAL_t Pos);
      /**
        @brief Sets the default speed of servos
        @param velocity the new speed value...
      */
      void setVelocity(optVAL_t velocity);
      /**
        @brief Sets the position limits for the servos
        @param posLimit the new positionLimit
        @warning the values are neither clamped nor masked!
        @todo check if a mask/clamp/filter is needed
      */
      void setPoslimit(optVAL_t posLimit);
      /**
        @brief make a servo rotating
        @param ID the target ID of the Servo
        @param velocity the speed the servo should have
        @warning this shouldnt be used... really
      */
      void rotate(optVAL_t ID,optVAL_t velocity);
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

    private:
      /// @brief stores the velocity value send with writePos()
      optVAL_t velocity_temp;
      /// @brief stores the posLimit value send with write()
      optVAL_t upperLimit_temp;
      /// @brief stores the ControlPin id
      optVAL_t cs;
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
        byte a = SPI.transfer (what);
        delayMicroseconds (23);
        return a;
      }

      inline void ServoCds55::setVelocity(optVAL_t velocity){this->velocity_temp = velocity;}
      inline void ServoCds55::setPoslimit(optVAL_t posLimit){this->upperLimit_temp =  posLimit;}

      void ServoCds55::write(optVAL_t ID,optVAL_t Pos){
        SetServoLimit(ID,this->upperLimit_temp);
        WritePos(ID,Pos);
      }

      void ServoCds55::rotate(optVAL_t ID,optVAL_t velocity){ //shouldnt use this... remove?
      SetServoLimit(ID,0x0);
      delay(102);
      SetMotormode(ID,velocity);
    }

    void ServoCds55::WritePos(optVAL_t ID,optVAL_t Pos){
      int PosB = (Pos>>0x8 & 0xff);//low
      int PosS = (Pos & 0xff);//high
      int velocityB = (this->velocity_temp>>0x8 & 0xff);
      int velocityS = (this->velocity_temp & 0xff);
      digitalWrite(this->cs, LOW);
      sendWait('p');  sendWait(ID);        sendWait(PosB);
      sendWait(PosS); sendWait(velocityB); sendWait(velocityS);
      sendWait('\t'); sendWait('\r');      sendWait('\n');
      digitalWrite(this->cs, HIGH);
      delay(10);
    }

    void ServoCds55::SetServoLimit(optVAL_t ID,optVAL_t upperLimit_tempT){
      int upperLimitB = (upperLimit_tempT>>0x8 & 0xff);
      int upperLimitS =  (upperLimit_tempT & 0xff);
      digitalWrite(this->cs, LOW);
      sendWait('s');         sendWait(ID);   sendWait(upperLimitB);
      sendWait(upperLimitS); sendWait('\t'); sendWait('\r');
      sendWait('\n');
      digitalWrite(this->cs, HIGH);
      delay(10);
    }

    void ServoCds55::SetMotormode(optVAL_t ID, optVAL_t velocity){
      int velocityB = (velocity>>0x8 & 0xff);
      int velocityS = (velocity & 0xff);
      digitalWrite(this->cs, LOW);
      sendWait('m');       sendWait(ID);   sendWait(velocityB);
      sendWait(velocityS); sendWait('\t'); sendWait('\r');
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
  inline optVAL_t  analogRead (optVAL_t id);


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
void SoccerBoard::reset(void) {};
void SoccerBoard::motor(int,int8_t) {}
void SoccerBoard::motorsOff(void) {}
#endif
void SoccerBoard::power(optVAL_t id, bool state) {writePin(id,state);}
void SoccerBoard::powerOn(optVAL_t id) {this->power(id,1);}
void SoccerBoard::powerOff(optVAL_t id) {this->power(id,0);}
void SoccerBoard::sleep(uint16_t t) {delay(1000*t);}
void SoccerBoard::msleep(uint16_t t) {delay(t);}
bool SoccerBoard::digital (optVAL_t id) {return readPin(id);}
optVAL_t  analogRead (optVAL_t id) {return readPin(id,0);}

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
  writePWM(PIN_MOTOR_SPE,(this->C));
}
///@endcond

///@cond
struct DynamixelBoard;
///@endcond


/*!
  @struct AX12Servo
  @brief [COPY&PASTE] This is the AX12Servo ghost struct :D
  @note any assignment to Port A won't has anny effect!

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
      @warning actually the pos isn't clamped etc => use carefully
    */
    void setPosition(optVAL_t pos, optVAL_t speed=0x96);
    /**
      @brief This saves the Servo Position

      Sets the values used by DynamixelBoard::action()
      @param pos the Position the Servo should go to
      @param speed the speed of the Servo
      @warning actually the pos isn't clamped etc => use carefully
    */
    inline void storePosition(optVAL_t pos, optVAL_t speed = 0x96);
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
    optVAL_t storedPos;
    /**
      @brief stores the Speed of the Servo DynamixelBoard::action()
      @note pls do me a favour and don't change them manually... use AX12Servo::storePosition()
    */
    optVAL_t storedSpe;

  //bool posMode; //we don't care wich mode we are in ^^
private:
  ///@brief stores the id of the AX12Servo obejct
  optVAL_t id;
  ///@brief stores the actual pos or move-to pos of the AX12Servo
  optVAL_t actPos;
  ///@brief stores the actual 'would use speed' of the AX12Servo
  optVAL_t actSpe;



}; //shield //set limits auto register for begin

///@cond
AX12Servo::AX12Servo(void) {}
#if EBOARD_USE_UTILITY > 0x0
void AX12Servo::setID(optVAL_t newID) {this->id = newID;}
void AX12Servo::changeMotorID(optVAL_t newID) {this->id = newID;} //this should change the hardwareaddress...
                                                                //IF needed: _servoHandler.setID(this->id, newID);
void AX12Servo::setPositionMode(void)  {}
void AX12Servo::setSpeedMode(void) {}
void AX12Servo::setSpeed(optVAL_t) {} //i won't use the rotate functions...
void AX12Servo::ledOff(void) {} //noone needs the AX12-Servo LED
void AX12Servo::ledOn(void) {} //really.... noone ^^
void AX12Servo::setTorque(uint16_t) {} //which damn register? xD
#endif

void AX12Servo::setPosition(optVAL_t pos, optVAL_t speed) {
    //TODO apply position_filter (maybe ((pos-511.5)/511.5) * 300 )
    if(speed != actSpe){ _servoHandler.setVelocity(speed); this->actSpe=speed;}
    _servoHandler.write(this->id,pos);
    this->actPos=pos; this->storedPos=pos; this->storedSpe = speed;
  }
void AX12Servo::storePosition(optVAL_t pos, optVAL_t speed){
    this->storedPos=pos;this->storedSpe=speed;
  }

optVAL_t AX12Servo::getPosition(void) {
    return this->actPos; //when moving... false value;
  }
bool AX12Servo::isMoving(void) {return false;} //we don't know^^

///@endcond

/*!
  @struct DynamixelBoard
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

/**
 @page page2 The source code
 @includelineno /home/eagleoutice/Dokumente/proj/_sia/src/eBoard.h
*/

#endif

#else
  #error This library is build for arduino-devices and should be used only in the Arduino IDE
#endif

#endif
