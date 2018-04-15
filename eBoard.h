//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 15.04.2018 20:16:17
#pragma GCC diagnostic push
 #pragma GCC diagnostic ignored "-Wall"
 #pragma GCC diagnostic ignored "-Wextra"
 #pragma pack(push)
 #pragma pack(16)
#define EBOARD_VERSION "3.0c"
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
 DEBUG_MSG("You are using eBoard-header v3.0c written by EagleoutIce");



//i am a guard... leave me alone :D
#ifndef EBOARD_HEADER_GUARD
    #define EBOARD_HEADER_GUARD
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
      DEBUG_MSG("You enabled I²C feature"s);
       INTERNAL
      #define twi_h
    //#define ATMEGA8
    #ifndef TWI_FREQ
      #define TWI_FREQ 100000L
    #endif
    # ifndef TWI_BUFFER_LENGTH
    #define TWI_BUFFER_LENGTH 32
    #endif
    #define TWI_READY 0
    #define TWI_MRX   1
    #define TWI_MTX   2
    #define TWI_SRX   3
    #define TWI_STX   4
    //#include <inttypes.h>
    //#include <avr/io.h>
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
      
      #include <inttypes.h>
      #include "Stream.h"
      #define BUFFER_LENGTH 32
      namespace eagle_impl {
      
        class TwoWire : public Stream {
          private:
            
            static uint8_t rxBuffer[];
            
            static uint8_t rxBufferIndex;
            
            static uint8_t rxBufferLength;
            
            static uint8_t txAddress;
            
            static uint8_t txBuffer[];
            
            static uint8_t txBufferIndex;
            
            static uint8_t txBufferLength;
            
            static uint8_t transmitting;
            
            static void (*user_onRequest)(void);
            
            static void (*user_onReceive)(int numBytes);
            
            static void onRequestService(void);
            
            static void onReceiveService(uint8_t* inBytes, int numBytes);
          public:
            
            TwoWire();
            
            void begin();
            
            void begin(uint8_t address);
            
            inline void begin(int address);
            
            void beginTransmission(uint8_t address);
            
            inline void beginTransmission(int address);
            
            inline uint8_t endTransmission(void);
            
            uint8_t endTransmission(uint8_t sendStop);
            
            inline uint8_t requestFrom(uint8_t address, uint8_t quantity);
            
            uint8_t requestFrom(uint8_t address , uint8_t quantity, uint8_t sendStop);
            
            inline uint8_t requestFrom(int address, int quantity);
            
            inline uint8_t requestFrom(int address, int quantity, int sendStop);
            
            virtual size_t write(uint8_t data);
            
            virtual size_t write(const uint8_t *data, size_t quantity);
            
            virtual int available(void);
            
            virtual int read(void);
            
            virtual int peek(void);
            
            void onReceive( void (*function)(int) );
            
            void onRequest( void (*function)(void) );
            
            using Print::write;
        };
        }
        extern "C" {
          #include <stdlib.h>
          #include <string.h>
          #include <inttypes.h>
          //#include "twi.h"
        }
         INTERNAL
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
          int8_t value = -1;
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
          if(!user_onRequest) return;
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
        
      
      TwoWire Wire = TwoWire();
      #else
      DEBUG_MSG("You disabled I²C");
      #endif
      
      #ifndef EBOARD_USE_SPI
          #define EBOARD_USE_SPI 0x1
      #endif
    #if EBOARD_USE_SPI > 0x0
      DEBUG_MSG("You enabled SPI");
      
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
       INTERNAL
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
    #if EBOARD_NANO > 0x0
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
         //again to resolve including errors we'll include the SoftwareSerial cpp file
         #define _SS_MAX_RX_BUFF 64 // RX buffer size
         #ifndef GCC_VERSION
            #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
         #endif
         namespace eagle_impl {
         
         class SoftwareSerial : public Stream {
         private:
           
           uint8_t _receivePin;
           
           uint8_t _receiveBitMask;
           
           volatile uint8_t *_receivePortRegister;
           
           uint8_t _transmitBitMask;
           
           volatile uint8_t *_transmitPortRegister;
           
           uint16_t _rx_delay_centering;
           
           uint16_t _rx_delay_intrabit;
           
           uint16_t _rx_delay_stopbit;
           
           uint16_t _tx_delay;
           
           uint16_t _buffer_overflow:1;
           
           uint16_t _inverse_logic:1;
           
           static char _receive_buffer[_SS_MAX_RX_BUFF];
           
           static volatile uint8_t _receive_buffer_tail;
           
           static volatile uint8_t _receive_buffer_head;
           
           static SoftwareSerial *active_object;
           
           void recv(void);
           
           inline uint8_t rx_pin_read(void);
           
           inline void tx_pin_write(uint8_t pin_state);
           
           void setTX(uint8_t transmitPin);
           
           void setRX(uint8_t receivePin);
           
           static inline void tunedDelay(uint16_t delay);
         public:
           // public methods
           
           SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
           
           ~SoftwareSerial(void);
           
           void begin(long speed);
           
           bool listen(void);
           
           inline void end(void);
           
           inline bool isListening(void);
           
           inline bool overflow(void);
           
           int peek(void);
           
           virtual size_t write(uint8_t byte);
           
           virtual int read(void);
           
           virtual int available(void);
           
           virtual void flush(void);
           //used to save codespace
           using Print::write;
           
           static inline void handle_interrupt(void);
         };
       }
        INTERNAL
         bool SoftwareSerial::isListening(void) {
            return this == active_object;
         }
         bool SoftwareSerial::overflow(void) {
            bool ret = _buffer_overflow;
            _buffer_overflow = false;
            return ret;
         }
         
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
         SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic ) :
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
        
      #endif
        
        SoftwareSerial _serial(PIN_BLUETOOTH_RX,PIN_BLUETOOTH_TX);
    #endif
    #if EBOARD_DEBUG_MODE > 0x0
        
        #define __ASSERT_USE_STDERR
        #include <assert.h>
        
        void __assert (const char *__func, const char *__file, optVAL_t __lineno, const char *__sexp);
         INTERNAL
        void __assert (const char *__func, const char *__file, optVAL_t __lineno, const char *__sexp){
            Serial.print("Error with: "); Serial.print(__func);
            Serial.print(" in "); Serial.print(__file);
            Serial.print("         >>");
            Serial.println(__sexp);
            if(strcmp(__func,"checkIdx")==0){
                Serial.println("   This happens if an out of bounds exception");
                Serial.println("   has occured. Following pins shouldn't be used:");
                Serial.print("   D" + PIN_BLUETOOTH_RX);Serial.print("&");
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
        
    #endif
    
    inline void checkIdx(optVAL_t idx);
     INTERNAL
    inline void checkIdx(optVAL_t idx){
        #if EBOARD_DEBUG_MODE > 0x0
            assert(idx>=0x0 && idx < PIN_MAX); //changed pins? change me! (didn't want to use macros)
            assert(idx!=PIN_BLUETOOTH_RX&&idx!=PIN_BLUETOOTH_TX);
        #endif
    }
    
    #if EBOARD_COPY_AND_PASTE > 0x0
        #if EBOARD_CHECK_PINS_PWM > 0x0
            
            optVAL_t countSetBits (optVAL_t x);
             INTERNAL
            optVAL_t countSetBits (optVAL_t x) {
                optVAL_t count; //dont't want to overuse global space^^
                for (count = 0; x; count++)
                    x &= x - 1;
                return count;
            }
            
        #endif
        #if EBOARD_CHECK_PINS > 0x0
            
            #if defined(__AVR_ATmega328P__) && not defined(__AVR_ATmega2560__)
              uint16_t pin_out = 0x0;
            #elif defined(__AVR_ATmega2560__)
              uint64_t pin_out = 0x0;
            #endif
            
            #if defined(__AVR_ATmega328P__) && not defined(__AVR_ATmega2560__)
              uint16_t pin_in = 0x0;
            #elif defined(__AVR_ATmega2560__)
              uint64_t pin_in = 0x0;
            #endif
            
            inline bool checkPin(optVAL_t idx, optVAL_t mode = OUTPUT);
             INTERNAL
            inline bool checkPin(optVAL_t idx, optVAL_t mode){
                checkIdx(idx);
                return (mode == OUTPUT)? ((pin_out & (1<<idx))>0x0):((pin_in & (1<<idx))>0x0);
            }
            
        #endif
        
        void setPin(optVAL_t idx, optVAL_t mode = OUTPUT);
         INTERNAL
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
        
    #endif
    #if EBOARD_BLUETOOTH > 0x0
        
        inline char readVal(char oF = '.');
        
        inline bool checkOverflow(void);
        
        template <typename T>
        inline void writeVal(const T& val);
        
        inline bool isConnected(void);
         INTERNAL
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
        
    #endif
    #if EBOARD_SHIFT_REGISTER > 0x0
        
        long store_bits = 0L;
        
        inline void shiftSingle(optVAL_t idx, bool val);
        
        void shiftAll(void);
         INTERNAL
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
        
    #endif
    
    optVAL_t _pwmValue = 0x0, _OpwmValue = 0x0;
    
    inline void writePWM (optVAL_t val);
     INTERNAL
    inline void writePWM(optVAL_t val){
        val = min(val,0xFF); val = max(0x0,val);
        _pwmValue = val;
    }
    #ifdef REPT_TASK
        extern void rept_task(void);
        DEBUG_MSG("You defined REPT_TASK: you have to define rept_task(void)!");
    #else
        DEBUG_MSG("You did not define REPT_TASK: rept_task(void) will not have any effect");
    #endif
   
    
    inline void writePin(optVAL_t idx,bool val);
     INTERNAL
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
    
    
    inline optVAL_t readPin(optVAL_t idx,bool dig = true);
     INTERNAL
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
    
    #if EBOARD_USE_SPI > 0x0 && (EBOARD_NANO == 0x0)
         INTERNAL
        //won't be commented
        struct ServoCds55 {
            public:
              #if defined(__AVR_ATmega2560__)
                ServoCds55(int CS=53);
              #else
                ServoCds55(int CS=10);
              #endif
            	void begin();
              void WritePos(int ID,int Pos);
              void write(int ID,int Pos);
              inline void setVelocity(int velocity);
              inline void setPoslimit(int posLimit);
              void rotate(int ID,int velocity);
              void SetServoLimit(int ID,int upperLimit);
              void SetMotormode(int ID, int velocity);
              void SetID(int ID, int newID);
              void Reset(int ID);
              byte sendWait (const byte what);
              int velocity_temp;
              int upperLimit_temp;
              int cs;
            };
            ServoCds55::ServoCds55 (int CS):cs(CS) {
              velocity_temp = 150;
              upperLimit_temp = 300;
            }
        void ServoCds55::begin() {
          pinMode(cs,OUTPUT);
          digitalWrite(cs,HIGH);
          SPI.begin ();
          SPI.setClockDivider(SPI_CLOCK_DIV8);
        }
        byte ServoCds55::sendWait (const byte what) {
          byte a = SPI.transfer (what);
          delayMicroseconds (20);
          return a;
        }
        void ServoCds55::setVelocity(int velocity){   //set servo velocity
          velocity_temp = velocity;
        }
        void ServoCds55::setPoslimit(int posLimit){  // set servo pos limit
          upperLimit_temp =  posLimit;
        }
        void ServoCds55::write(int ID,int Pos){     //  Servo Mode
          SetServoLimit(ID,upperLimit_temp);
          WritePos(ID,Pos);// default velocity:150
        }
        void ServoCds55::rotate(int ID,int velocity){ // Motor Mode
          SetServoLimit(ID,0);
          delay(100);
          SetMotormode(ID,velocity);
        }
        void ServoCds55::WritePos(int ID,int Pos){
          int PosB = (Pos>>8 & 0xff);//low
          int PosS = (Pos & 0xff);//high
          int velocityB = (velocity_temp>>8 & 0xff);
          int velocityS = (velocity_temp & 0xff);
          digitalWrite(cs, LOW);
          sendWait ('p'); sendWait (ID);
          sendWait (PosB); sendWait (PosS);
          sendWait (velocityB); sendWait (velocityS);
          sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
          digitalWrite(cs, HIGH);
          delay(10);
        }
        void ServoCds55::SetServoLimit(int ID,int  upperLimit_temp){
          int upperLimitB = (upperLimit_temp>>8 & 0xff);
          int upperLimitS =  (upperLimit_temp & 0xff);
          digitalWrite(cs, LOW);
          sendWait ('s'); sendWait (ID);
          sendWait (upperLimitB); sendWait (upperLimitS);
          sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
          digitalWrite(cs, HIGH);
          delay(10);
        }
        void ServoCds55::SetMotormode(int ID, int velocity){
          int velocityB = (velocity>>8 & 0xff);
          int velocityS = (velocity & 0xff);
          digitalWrite(cs, LOW);
          sendWait ('m'); sendWait (ID);
          sendWait (velocityB); sendWait (velocityS);
          sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
          digitalWrite(cs, HIGH);
          delay(10);
        }
        void ServoCds55::SetID(int ID, int newID){
          digitalWrite(cs, LOW);
          sendWait ('i'); sendWait (ID);
          sendWait (newID);
          sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
          digitalWrite(cs, HIGH);
          delay(10);
        }
        void ServoCds55::Reset(int ID){
          digitalWrite(cs, LOW);
          sendWait ('r'); sendWait (ID);
          sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
          digitalWrite(cs, HIGH);
          delay(10);
        }
        
        
        ServoCds55 _servoHandler;
    #endif
    #if EBOARD_COPY_AND_PASTE > 0x0 && EBOARD_NANO == 0
        
        struct SoccerBoard {
            
            inline SoccerBoard(void);
            //inline ~SoccerBoard(void) {}
            #if EBOARD_USE_UTILITY > 0x0 or defined(__AVR_ATmega2560__) //won't shrink space... just speed things up
                
                inline void led(int idx,bool state);
                
                inline void ledOn(int idx);
                
                inline void ledOff(int idx);
                
                inline void ledsOff(void);
                
                inline void ledMeter(int);
            #endif
            #if EBOARD_USE_UTILITY > 0x0
                
                inline void  button(int);
                
                inline void waitForButton(int);
            #endif
            
            inline void motor(uint8_t id,int16_t val);
            
            inline void motorsOff(void);
            //ARDUINO UNO PINOUT
            //D0,D1   => Bluetooth connection
            //D4,D5   => MotorControl (D5: 980Hz)
            //D10,D13 => SPI
            
            inline void power(optVAL_t id, bool state);
            
            inline void powerOn(optVAL_t id);
            
            inline void powerOff(optVAL_t id);
            
            inline void sleep(uint16_t t);
            
            inline void msleep(uint16_t t);
            
            inline bool digital (optVAL_t id);
            
            inline optVAL_t  analog (optVAL_t id);
            
            inline void reset(void);  
        };
         INTERNAL
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
                for(;;) {}
            #endif
        }
        void SoccerBoard::power(optVAL_t id, bool state) {writePin(id,state);}
        void SoccerBoard::powerOn(optVAL_t id) {this->power(id,1);}
        void SoccerBoard::powerOff(optVAL_t id) {this->power(id,0);}
        void SoccerBoard::sleep(uint16_t t) {delay(1000*t);}
        void SoccerBoard::msleep(uint16_t t) {delay(t);}
        bool SoccerBoard::digital (optVAL_t id) {return readPin(id);}
        optVAL_t  SoccerBoard::analog (optVAL_t id) {return readPin(id,0);}
        
        //To avoid not_found issues
        
        #define DIGITAL_IN            0x0
        
        #define DIGITAL_IN_INV        0x1
        
        #define DIGITAL_IN_PULLUP     0x2
        
        #define DIGITAL_IN_PULLUP_INV 0x3
        
        #define DIGITAL_OUT           0x4
        
        #define DIGITAL_OUT_INV       0x5
        
        #define DIGITAL_OUT_LOW       0x6
        
        #define DIGITAL_OUT_HIGH      0x7
        
        #define ANALOG_IN_8_BIT       0x8
        
        #define ANALOG_IN_10_BIT      0x9
        
        #define ANALOG_IN_MEAN_8_BIT  0xA
        
        #define ANALOG_IN_MEAN_10_BIT 0xB
        
        #define COUNTER_8_BIT         0xC
        
        #define COUNTER_16_BIT        0xD
        
        #define COUNTER_RISE_8_BIT    0xE
        
        #define COUNTER_RISE_16_BIT   0xF
        
        #define PWM_SLOW              0x8
        
        #define PWM_FAST              0x9
        
        #define FREQ_LOW              0xA
        
        #define FREQ_HIGH             0xB
        
        #define COUNTER_B_DIR         0xC
        
        #define COUNTER_B_DIR_PULLUP  0xD
        
        #define COUNTER_MEAN_8_BIT    0xE
        
        #define COUNTER_MEAN_16_BIT   0xF
        
        struct I2CInOut{
            
            I2CInOut(SoccerBoard&, optVAL_t, optVAL_t, optVAL_t, optVAL_t);
            #if EBOARD_USE_UTILITY > 0x0
                
                inline void read(void);
                
                inline void changeAddress(optVAL_t);
                
                inline void changeModes(optVAL_t,optVAL_t,optVAL_t);
            #endif
            
            inline void write(void);
            
            optVAL_t A; //if you've used uint16_t values you'll have to replace it here
            //we only have B - DiOut and C - AO [OUT]
            
            optVAL_t B;
            
            optVAL_t C;
        };
         INTERNAL
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
        
         INTERNAL
        struct DynamixelBoard;
        
        
        struct AX12Servo {
            
            AX12Servo(void);
            
            AX12Servo(DynamixelBoard &dBoard, optVAL_t servoID); //if borders => setPosLimit
            DynamixelBoard *_conBoard;
            #if EBOARD_USE_UTILITY > 0x0
                
                inline void setID(optVAL_t newID);
                
                inline void changeMotorID(optVAL_t newID);                    //this should change the hardwareaddress...
                
                inline void setPositionMode(void);
                
                inline void setSpeedMode(void);
                
                inline void setSpeed(optVAL_t);
                
                inline void ledOff(void);
                
                inline void ledOn(void);
                
                inline void setTorque(uint16_t);
            #endif
            
            void setPosition(int pos, int speed=0x3FF);
            
            inline void storePosition(int pos, int speed = 0x3FF);
            
            inline optVAL_t getPosition(void);
            
            inline bool isMoving(void);
            
            int storedPos;
            
            int storedSpe;
            //bool posMode; //we don't care wich mode we are in ^^
            
            optVAL_t id;
        private:
            
            int actPos;
            
            int actSpe;
        }; //shield //set limits auto register for begin
         INTERNAL
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
        
        
        struct DynamixelBoard {
            
            inline DynamixelBoard(SoccerBoard&);
            //inline ~DynamixelBoard(void) {}
            #if EBOARD_USE_UTILITY > 0x0
                
                inline void changeId(optVAL_t);
                
                inline void changeMotorID(optVAL_t);
                
                inline void ledOn(optVAL_t);
                
                inline void ledOff(optVAL_t);
            #endif
            
            inline void action(void);
            
            friend struct AX12Servo;
        protected:
            
            AX12Servo* connected[EBOARD_SPI_SERVO_MAX];
        };
         INTERNAL
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
        
        #endif
        #if EBOARD_BLUETOOTH > 0x0
            
            struct RB14Scan {
                
                inline RB14Scan(void);
                
                
                inline int raw(optVAL_t);
                
                
                inline char channel(optVAL_t);
                
                inline void write(const char* const  val);
            };
             INTERNAL
            inline RB14Scan::RB14Scan(void) {}
            inline int RB14Scan::raw(optVAL_t) {return isConnected();}
            inline char RB14Scan::channel(optVAL_t) {return ((isConnected())?(readVal()):(-1));}
            inline void RB14Scan::write(const char* const val) {writeVal(val);}
            
        
    #endif
#if EBOARD_I2C > 0x0
        
        inline optVAL_t sendI2C(optVAL_t deviceID,byte *buf, byte buf_len);
        
        inline optVAL_t sendI2C(optVAL_t deviceID, byte buf);
        
        inline void pingI2C(optVAL_t ret[], optVAL_t ret_len);
         INTERNAL
        inline void pingI2C(optVAL_t ret[], optVAL_t ret_len){
            optVAL_t count = 0;
            for (byte i = 1; (i < 255 && !STOP); i++)  {
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
        
        
        inline void readI2C(optVAL_t deviceID, optVAL_t ret[], optVAL_t ret_len,bool blocking=true);
         INTERNAL
        inline void readI2C(optVAL_t deviceID,optVAL_t ret[] , optVAL_t ret_len,bool blocking) {
            for(optVAL_t rect = 0x0; (Wire.available() || (((blocking && (rect < ret_len))) && (!STOP))); rect++)
                ret[rect] = Wire.read();
        }
        
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
            
            //Definition of OLED Constants
            
            #define LCD_COMMAND_MODE                0x80
            
            #define LCD_DATA_MODE                   0x40
            
            #define LCD_COMMAND_DISPLAY_OFF         0xAE
            
            #define LCD_COMMAND_DISPLAY_ON          0xAF
            
            #define LCD_COMMAND_BLACK_BACKGROUND    0xA6
            
            #define LCD_COMMAND_WHITE_BACKGROUND    0xA7
            
            #define LCD_COMMAND_SET_BRIGHTNESS      0x81
            
            #define LCD_PAGE_ADDRESSING	            0x02
            
            #define LCD_HORIZONTAL_ADDRESSING       0x00
            //The regulator
            
            #define LCD_COMMAND_CHARGE_PUMP_SETTING	0x8d
            
            #define LCD_COMMAND_CHARGE_PUMP_ENABLE 0x14
            #ifndef LCD_WIDTH
                
                #define LCD_WIDTH 128
            #endif
            #ifndef LCD_HEIGHT
                
                #define LCD_HEIGHT 64
            #endif
            
            struct LCD {
                #if EBOARD_NANO == 0
                
                LCD(SoccerBoard &soccerBoard, optVAL_t id=0x3C);
                #else
                LCD(optVAL_t id=0x3C);
                #endif
                
                inline bool changeID(optVAL_t newID = 0x3C);
                
                inline bool clear(void);
                
                inline void print(const char* data);
                
                inline void print(int data);
                
                inline void print(optVAL_t line, optVAL_t col, const char* data);
                
                inline void print(optVAL_t line, optVAL_t col, int data);
               
                inline void lightOn(void);
                
                inline void lightOff(void);
                
                inline bool reset(void);
                //added features
                
                inline bool init(void);
                
                inline void drawBitmap(const unsigned char *bitmap, byte posX, byte posY, byte hiX, byte hiY);
                
                inline void changeMode(bool newMode = true);
                
                inline bool setCursor(byte posX = 0x0, byte posY = 0x0);
                
                inline bool changeBrightness (byte val = 0x64);
                
                inline void changeBackground(bool newBackground = false);
                
                optVAL_t ID;
                private:
                
                
                byte pX;
                
                byte pY;
                
                bool _cI;
                
                inline void s2Cmd(optVAL_t o, optVAL_t t);
                
                inline bool s1Cmd(optVAL_t o);
                
                inline void s1Dat(optVAL_t o);
            };
             INTERNAL
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
                    for (byte j = 0; j < 128; j++)
                        this->s1Dat(0);
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
                this->pX = posX; this->pY = posY;
                return this->s1Cmd(0xB0 + posY);
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
            inline bool LCD::s1Cmd(optVAL_t C) {
                if(!this->_cI) this->init();
                Wire.beginTransmission(this->ID);
                Wire.write(LCD_COMMAND_MODE); Wire.write(C);
                return (Wire.endTransmission()==0);
            }
            inline void LCD::s1Dat(optVAL_t o){
                if(!this->_cI) this->init();
                Wire.beginTransmission(this->ID);
                Wire.write(LCD_DATA_MODE); Wire.write(o);
                Wire.endTransmission();
            }
            
        #endif
        #endif
        #if EBOARD_NEO > 0x0
        // Codesection based on official NeoPixel library
        // RGB NeoPixel permutations; white and red offsets are always same
        // Offset:         W          R          G          B
        
        #define EBOARD_NEO_RGB  ((0 << 6) | (0 << 4) | (1 << 2) | (2))
        
        #define EBOARD_NEO_RBG  ((0 << 6) | (0 << 4) | (2 << 2) | (1))
        
        #define EBOARD_NEO_GRB  ((1 << 6) | (1 << 4) | (0 << 2) | (2))
        
        #define EBOARD_NEO_GBR  ((2 << 6) | (2 << 4) | (0 << 2) | (1))
        
        #define EBOARD_NEO_BRG  ((1 << 6) | (1 << 4) | (2 << 2) | (0))
        
        #define EBOARD_NEO_BGR  ((2 << 6) | (2 << 4) | (1 << 2) | (0))
        // RGBW NeoPixel permutations; all 4 offsets are distinct
        // Offset:         W          R          G          B
        
        #define EBOARD_NEO_WRGB ((0 << 6) | (1 << 4) | (2 << 2) | (3))
        
        #define EBOARD_NEO_WRBG ((0 << 6) | (1 << 4) | (3 << 2) | (2))
        
        #define EBOARD_NEO_WGRB ((0 << 6) | (2 << 4) | (1 << 2) | (3))
        
        #define EBOARD_NEO_WGBR ((0 << 6) | (3 << 4) | (1 << 2) | (2))
        
        #define EBOARD_NEO_WBRG ((0 << 6) | (2 << 4) | (3 << 2) | (1))
        
        #define EBOARD_NEO_WBGR ((0 << 6) | (3 << 4) | (2 << 2) | (1))
        
        #define EBOARD_NEO_RWGB ((1 << 6) | (0 << 4) | (2 << 2) | (3))
        
        #define EBOARD_NEO_RWBG ((1 << 6) | (0 << 4) | (3 << 2) | (2))
        
        #define EBOARD_NEO_RGWB ((2 << 6) | (0 << 4) | (1 << 2) | (3))
        
        #define EBOARD_NEO_RGBW ((3 << 6) | (0 << 4) | (1 << 2) | (2))
        
        #define EBOARD_NEO_RBWG ((2 << 6) | (0 << 4) | (3 << 2) | (1))
        
        #define EBOARD_NEO_RBGW ((3 << 6) | (0 << 4) | (2 << 2) | (1))
        
        #define EBOARD_NEO_GWRB ((1 << 6) | (2 << 4) | (0 << 2) | (3))
        
        #define EBOARD_NEO_GWBR ((1 << 6) | (3 << 4) | (0 << 2) | (2))
        
        #define EBOARD_NEO_GRWB ((2 << 6) | (1 << 4) | (0 << 2) | (3))
        
        #define EBOARD_NEO_GRBW ((3 << 6) | (1 << 4) | (0 << 2) | (2))
        
        #define EBOARD_NEO_GBWR ((2 << 6) | (3 << 4) | (0 << 2) | (1))
        
        #define EBOARD_NEO_GBRW ((3 << 6) | (2 << 4) | (0 << 2) | (1))
        
        #define EBOARD_NEO_BWRG ((1 << 6) | (2 << 4) | (3 << 2) | (0))
        
        #define EBOARD_NEO_BWGR ((1 << 6) | (3 << 4) | (2 << 2) | (0))
        
        #define EBOARD_NEO_BRWG ((2 << 6) | (1 << 4) | (3 << 2) | (0))
        
        #define EBOARD_NEO_BRGW ((3 << 6) | (1 << 4) | (2 << 2) | (0))
        
        #define EBOARD_NEO_BGWR ((2 << 6) | (3 << 4) | (1 << 2) | (0))
        
        #define EBOARD_NEO_BGRW ((3 << 6) | (2 << 4) | (1 << 2) | (0))
       
        #define EBOARD_NEO_800KHZ 0x0000
        
        #define EBOARD_NEO_400KHZ 0x0100
        // uint16_t can be uint8_t in 800Khz mode ^^
        
        struct NeoPixel{
          
          NeoPixel(uint16_t n, uint8_t p = 6, uint16_t t =  EBOARD_NEO_GRB + EBOARD_NEO_800KHZ);
          
          NeoPixel(void);
          
          ~NeoPixel(void);
          
          void begin(void);
          
          void show(void);
          
          void setPin(uint8_t p);
          
          void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
          
          void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
          
          void setPixelColor(uint16_t n, uint32_t c);
          
          void setBrightness(uint8_t val);
          
          void clear(void);
          
          void updateLength(uint16_t n);
          
          void updateType(uint16_t t);
          
          inline uint8_t *getPixels(void) const;
          
          inline uint8_t getBrightness(void) const;
          
          uint8_t sine8(uint8_t x) const;
          
          uint8_t gamma8(uint8_t x) const;
          
          inline int8_t getPin(void);
          
          inline uint16_t numPixels(void) const;
          
          static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
          
          static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
          
          uint32_t getPixelColor(uint16_t n) const;
          
          inline bool canShow(void);
        protected:
          
          bool is800KHz;
          
          bool begun;
          
          uint16_t numLEDs; //maybe shorten with PrepConst 'extendetLED'?
          
          uint16_t numBytes;
          
          int8_t pin;
          
          uint8_t brightness;
          
          uint8_t *pixels;
          
          uint8_t aOffset[4];
          
          uint32_t endTime; //used for diff calc
          #ifdef __AVR__ //not needed (rem?)
            
            volatile uint8_t *port;// Output PORT register
            
            uint8_t pinMask;       // Output PORT bitmask
          #endif
        };
         INTERNAL
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
          endTime(0)
        {aOffset[0]=1;aOffset[1]=0;aOffset[2]=2;aOffset[3]=1;}
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
          numBytes = n * ((aOffset[3] == aOffset[0]) ? 3 : 4);
          if((pixels = (uint8_t *)malloc(numBytes))) {
            memset(pixels, 0, numBytes);
            numLEDs = n;
          } else {
            numLEDs = numBytes = 0;
          }
        }
        void NeoPixel::updateType(uint16_t t) {
          boolean oldThreeBytesPerPixel = (aOffset[3] == aOffset[0]); // false if RGBW
          aOffset[3] = (t >> 6) & 0b11;
          aOffset[0] = (t >> 4) & 0b11;
          aOffset[1] = (t >> 2) & 0b11;
          aOffset[2] =  t       & 0b11;
          is800KHz = (t < 256);      // 400 KHz flag is 1<<8
          if(pixels) {
            boolean newThreeBytesPerPixel = (aOffset[3] == aOffset[0]);
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
          interrupts();
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
            if(aOffset[3] == aOffset[0]) {
              p = &pixels[n * 3];
            } else {
              p = &pixels[n * 4];
              p[aOffset[3]] = 0;
            }
            p[aOffset[0]] = r;
            p[aOffset[1]] = g;
            p[aOffset[2]] = b;
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
            if(aOffset[3] == aOffset[0]) {
              p = &pixels[n * 3];
            } else {
              p = &pixels[n * 4];
              p[aOffset[3]] = w;
            }
            p[aOffset[0]] = r;
            p[aOffset[1]] = g;
            p[aOffset[2]] = b;
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
            if(aOffset[3] == aOffset[0]) {
              p = &pixels[n * 3];
            } else {
              p = &pixels[n * 4];
              uint8_t w = (uint8_t)(c >> 24);
              p[aOffset[3]] = brightness ? ((w * brightness) >> 8) : w;
            }
            p[aOffset[0]] = r;
            p[aOffset[1]] = g;
            p[aOffset[2]] = b;
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
          if(aOffset[3] == aOffset[0]) {
            p = &pixels[n * 3];
            if(brightness) {
              return (((uint32_t)(p[aOffset[0]] << 8) / brightness) << 16) |
                     (((uint32_t)(p[aOffset[1]] << 8) / brightness) <<  8) |
                     ( (uint32_t)(p[aOffset[2]] << 8) / brightness       );
            } else {
              return ((uint32_t)p[aOffset[0]] << 16) |
                     ((uint32_t)p[aOffset[1]] <<  8) |
                      (uint32_t)p[aOffset[2]];
            }
          } else {
            p = &pixels[n * 4];
            if(brightness) {
              return (((uint32_t)(p[aOffset[3]] << 8) / brightness) << 24) |
                     (((uint32_t)(p[aOffset[0]] << 8) / brightness) << 16) |
                     (((uint32_t)(p[aOffset[1]] << 8) / brightness) <<  8) |
                     ( (uint32_t)(p[aOffset[2]] << 8) / brightness       );
            } else {
              return ((uint32_t)p[aOffset[3]] << 24) |
                     ((uint32_t)p[aOffset[0]] << 16) |
                     ((uint32_t)p[aOffset[1]] <<  8) |
                      (uint32_t)p[aOffset[2]];
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
        #endif
        
    
    
    
    
    
    
    
    
    
    
    
#if EBOARD_NANO > 0x0 || defined(DOC)
//offer more functions
  #if EBOARD_GUESSPATH > 0x0
  //import servo-class
   INTERNAL
  //shameless copy paste :D
  #define _useTimer1
  typedef enum { _timer1, _Nbr_16timers } timer16_Sequence_t;
  #define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
  #define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
  #define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
  #define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds
  #define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer
  #define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)
  #define INVALID_SERVO         255     // flag indicating an invalid servo index
  typedef struct  {
    uint8_t nbr        :6 ;             // a pin number from 0 to 63
    uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false
  } ServoPin_t;
  typedef struct {
    ServoPin_t Pin;
    volatile unsigned int ticks;
  } servo_t;
  class Servo {
    public:
      Servo();
      uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
      uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes.
      void detach();
      void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
      void writeMicroseconds(int value); // Write pulse width in microseconds
      inline int read();                        // returns current pulse width as an angle between 0 and 180 degrees
      int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
      inline bool attached();                   // return true if this servo is attached, otherwise false
    private:
       uint8_t servoIndex;               // index into the channel data for this servo
       int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH
       int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH
  };
  #define usToTicks(_us)    (( clockCyclesPerMicrosecond()* _us) / 8)     // converts microseconds to tick (assumes prescale of 8)  // 12 Aug 2009
  #define ticksToUs(_ticks) (( (unsigned)_ticks * 8)/ clockCyclesPerMicrosecond() ) // converts from ticks back to microseconds
 #define TRIM_DURATION       2                               // compensation ticks to trim adjust for digitalWrite delays // 12 August 2009
  //#define NBR_TIMERS        (MAX_SERVOS / SERVOS_PER_TIMER)
  static servo_t servos[MAX_SERVOS];                          // static array of servo structures
  static volatile int8_t Channel[_Nbr_16timers ];             // counter for the servo being pulsed for each timer (or -1 if refresh interval)
  uint8_t ServoCount = 0;                                     // the total number of attached servos
  // convenience macros
  #define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER)) // returns the timer controlling this servo
  #define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)       // returns the index of the servo on this timer
  #define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)     // macro to access servo index by timer and channel
  #define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])            // macro to access servo class by timer and channel
  #define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)  // minimum value in uS for this servo
  #define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)  // maximum value in uS for this servo
  static inline void handle_interrupts(timer16_Sequence_t timer, volatile uint16_t *TCNTn, volatile uint16_t* OCRnA)
  {
    if( Channel[timer] < 0 )
      *TCNTn = 0; // channel set to -1 indicated that refresh interval completed so reset the timer
    else{
      if( SERVO_INDEX(timer,Channel[timer]) < ServoCount && SERVO(timer,Channel[timer]).Pin.isActive == true )
        digitalWrite( SERVO(timer,Channel[timer]).Pin.nbr,LOW); // pulse this channel low if activated
    }
    Channel[timer]++;    // increment to the next channel
    if( SERVO_INDEX(timer,Channel[timer]) < ServoCount && Channel[timer] < SERVOS_PER_TIMER) {
      *OCRnA = *TCNTn + SERVO(timer,Channel[timer]).ticks;
      if(SERVO(timer,Channel[timer]).Pin.isActive == true)     // check if activated
        digitalWrite( SERVO(timer,Channel[timer]).Pin.nbr,HIGH); // its an active channel so pulse it high
    }
    else {
      // finished all channels so wait for the refresh period to expire before starting over
      if( ((unsigned)*TCNTn) + 4 < usToTicks(REFRESH_INTERVAL) )  // allow a few ticks to ensure the next OCR1A not missed
        *OCRnA = (unsigned int)usToTicks(REFRESH_INTERVAL);
      else
        *OCRnA = *TCNTn + 4;  // at least REFRESH_INTERVAL has elapsed
      Channel[timer] = -1; // this will get incremented at the end of the refresh period to start again at the first channel
    }
  }
  #ifndef WIRING // Wiring pre-defines signal handlers so don't define any if compiling for the Wiring platform
  // Interrupt handlers for Arduino
    #if defined(_useTimer1)
    SIGNAL (TIMER1_COMPA_vect)
    {
      handle_interrupts(_timer1, &TCNT1, &OCR1A);
    }
    #endif
  #elif defined WIRING
    // Interrupt handlers for Wiring
    #if defined(_useTimer1)
    void Timer1Service()
    {
      handle_interrupts(_timer1, &TCNT1, &OCR1A);
    }
    #endif
  #endif
  static void initISR(timer16_Sequence_t timer) {
    if(timer == _timer1) {
      TCCR1A = 0;             // normal counting mode
      TCCR1B = _BV(CS11);     // set prescaler of 8
      TCNT1 = 0;              // clear the timer count
      TIFR1 |= _BV(OCF1A);     // clear any pending interrupts;
      TIMSK1 |=  _BV(OCIE1A) ; // enable the output compare interrupt
      #if defined(WIRING)
        timerAttach(TIMER1OUTCOMPAREA_INT, Timer1Service);
      #endif
      }
  }
  static void finISR(timer16_Sequence_t timer) {
    #if defined WIRING   // Wiring
    if(timer == _timer1) {
      TIMSK &=  ~_BV(OCIE1A) ;  // disable timer 1 output compare interrupt
      timerDetach(TIMER1OUTCOMPAREA_INT);
    }
    else if(timer == _timer3) {
      ETIMSK &= ~_BV(OCIE3A);    // disable the timer3 output compare A interrupt
      timerDetach(TIMER3OUTCOMPAREA_INT);
    }
    #else
    //For arduino - in future: call here to a currently undefined function to reset the timer
    (void) timer;  // squash "unused parameter 'timer' [-Wunused-parameter]" warning
    #endif
  }
  static boolean isTimerActive(timer16_Sequence_t timer) {
    // returns true if any servo is active on this timer
    for(uint8_t channel=0; channel < SERVOS_PER_TIMER; channel++) {
      if(SERVO(timer,channel).Pin.isActive == true)
        return true;
    }
    return false;
  }
  Servo::Servo() {
    if( ServoCount < MAX_SERVOS) {
      this->servoIndex = ServoCount++;                    // assign a servo index to this instance
  	  servos[this->servoIndex].ticks = usToTicks(DEFAULT_PULSE_WIDTH);   // store default values  - 12 Aug 2009
    }
    else
      this->servoIndex = INVALID_SERVO ;  // too many servos
  }
  uint8_t Servo::attach(int pin) {
    return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  }
  uint8_t Servo::attach(int pin, int min, int max) {
    if(this->servoIndex < MAX_SERVOS ) {
      pinMode( pin, OUTPUT) ;                                   // set servo pin to output
      servos[this->servoIndex].Pin.nbr = pin;
      // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
      this->min  = (MIN_PULSE_WIDTH - min)/4; //resolution of min/max is 4 uS
      this->max  = (MAX_PULSE_WIDTH - max)/4;
      // initialize the timer if it has not already been initialized
      timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
      if(isTimerActive(timer) == false)
        initISR(timer);
      servos[this->servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
    }
    return this->servoIndex ;
  }
  void Servo::detach() {
    servos[this->servoIndex].Pin.isActive = false;
    timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
    if(isTimerActive(timer) == false) {
      finISR(timer);
    }
  }
  void Servo::write(int value) {
    if(value < MIN_PULSE_WIDTH)
    {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
      if(value < 0) value = 0;
      if(value > 180) value = 180;
      value = map(value, 0, 180, SERVO_MIN(),  SERVO_MAX());
    }
    this->writeMicroseconds(value);
  }
  void Servo::writeMicroseconds(int value) {
    // calculate and store the values for the given channel
    byte channel = this->servoIndex;
    if( (channel < MAX_SERVOS) )   // ensure channel is valid
    {
      if( value < SERVO_MIN() )          // ensure pulse width is valid
        value = SERVO_MIN();
      else if( value > SERVO_MAX() )
        value = SERVO_MAX();
      value = value - TRIM_DURATION;
      value = usToTicks(value);  // convert to ticks after compensating for interrupt overhead - 12 Aug 2009
      uint8_t oldSREG = SREG;
      cli();
      servos[channel].ticks = value;
      SREG = oldSREG;
    }
  }
  inline int Servo::read() // return the value as degrees
  {
    return  map( this->readMicroseconds()+1, SERVO_MIN(), SERVO_MAX(), 0, 180);
  }
  int Servo::readMicroseconds() {
    unsigned int pulsewidth;
    if( this->servoIndex != INVALID_SERVO )
      pulsewidth = ticksToUs(servos[this->servoIndex].ticks)  + TRIM_DURATION ;   // 12 aug 2009
    else
      pulsewidth  = 0;
    return pulsewidth;
  }
  inline bool Servo::attached() {
    return servos[this->servoIndex].Pin.isActive ;
  }
  
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
       
        extern int eVirtual_main();
        
        
        void setup(void);
         INTERNAL
        void setup(void) {
            //setup of RX and TX should be handled manually - in everyCase ^^
            setPin(PIN_MOTOR_DIR);
            setPin(PIN_MOTOR_SPE);
            #if EBOARD_DEBUG_MODE > 0x0
                Serial.begin(EBOARD_DEBUG_SPEED);
            #endif
            //this will initialize the interrupt handling!
            cli();
            TIMSK2 &= ~(1<<TOIE2);
          	TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
          	TCCR2B &= ~(1<<WGM22);
          	ASSR &= ~(1<<AS2);
            TIMSK2 &= ~(1<<OCIE2A);
            TCCR2B |= (1<<CS22);
            TCCR2B &= ~((1<<CS21) | (1<<CS20));
            TCNT2 = 256 - (int)((float)F_CPU * 0.001 / 64);
            TIMSK2 |= (1<<TOIE2);
            sei();
            #if EBOARD_BLUETOOTH > 0x0
                
                
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
            #if EBOARD_NANO > 0x0
              mainMotor.attach(EBOARD_NANO_MAIN);
              steerMotor.attach(EBOARD_NANO_STEER);
              #if EBOARD_DEBUG_MODE > 0x0
                Serial.println("Initializing main driving motor (3s)");
              #endif
                mainMotor.write(90);
                delay(3005);
              #if EBOARD_DEBUG_MODE > 0x0
                Serial.println("Initializing of main driving motor completed");
              #endif
            #endif
            #if EBOARD_DEBUG_MODE > 0x0
                Serial.print((char) eVirtual_main());
                Serial.println("fin");
            #else
                eVirtual_main();
            #endif
            if (STOP) {} //prevent unused error
            delay(200);
            #if EBOARD_NANO > 0x0
              mainMotor.write(90);
            #endif
            cli(); //disable timers after running the program :D
            #if EBOARD_NANO == 0x0
              writePWM(0);analogWrite(PIN_MOTOR_SPE,0);
            #endif
        }
        
        
        void loop(void);
         INTERNAL
        void loop(void){
          //shall be empty
          }
        
#endif
#if EBOARD_NANO > 0x0 || defined(DOC)
  
  inline void set_motor_speed(optVAL_t spe);
 inline void set_steer_angle(optVAL_t ang);
  
  inline void set_motor_speed(optVAL_t spe){
      if(spe < 0 || spe > 180) return;
      mainMotor.write(spe);
  }
  inline void set_steer_angle(optVAL_t ang){
      if(ang < 0 || ang > 180) return;
      steerMotor.write(ang);
  }
  
#endif
#else
    #error This library is build for arduino-devices and should be used only in the Arduino IDE or with a similar linking process
#endif
#pragma GCC diagnostic pop
#pragma pack(pop)
#endif
