//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 20.04.2018 22:20:28
#ifndef EAGLE_EBOARD_HELPLIB_TWOWIRE
#define EAGLE_EBOARD_HELPLIB_TWOWIRE
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
	      
	       void begin(int address);
	      
	      void beginTransmission(uint8_t address);
	      
	       void beginTransmission(int address);
	      
	       uint8_t endTransmission(void);
	      
	      uint8_t endTransmission(uint8_t sendStop);
	      
	       uint8_t requestFrom(uint8_t address, uint8_t quantity);
	      
	      uint8_t requestFrom(uint8_t address , uint8_t quantity, uint8_t sendStop);
	      
	       uint8_t requestFrom(int address, int quantity);
	      
	       uint8_t requestFrom(int address, int quantity, int sendStop);
	      
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
	  
	  extern TwoWire Wire;
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
	  #define TwoWire_h
	  
#endif
