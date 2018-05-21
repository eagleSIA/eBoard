//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 21.05.2018 05:40:11
#ifndef EAGLE_EBOARD_HELPLIB_SPI
    #define EAGLE_EBOARD_HELPLIB_SPI

    


//=====================================================================================================================================================
//                                                                  Macro Definitions                                                                  
//=====================================================================================================================================================

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

//=====================================================================================================================================================
//                                                                         SPI                                                                         
//=====================================================================================================================================================

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                    class                                                                        
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	  struct SPIClass {
	    

	    inline static byte transfer(byte data);
	    

	    inline static void attachInterrupt(void);
	    

	    inline static void detachInterrupt(void); // Default
	    

	    static void begin(void); // Default
	    

	    inline static void end(void);
	    

	    inline static void setBitOrder(uint8_t bitOrder);
	    

	    inline static void setDataMode(uint8_t mode);
	    

	    inline static void setClockDivider(uint8_t rate);
	  };
	}
	


    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                definitions                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	byte SPIClass::transfer(byte data) {
        SPDR = data;
        while (!(SPSR & _BV(SPIF)));
        return SPDR;
	}

	void SPIClass::attachInterrupt() { SPCR |=  _BV(SPIE);}

	void SPIClass::detachInterrupt() { SPCR &= ~_BV(SPIE);}

	

	void SPIClass::end() { SPCR &= ~_BV(SPE); }

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
    void SPIClass::begin() {
        digitalWrite(SS, HIGH);
        pinMode(SS, OUTPUT); //doesn't block common use as_ OUTPUT!
        SPCR |= _BV(MSTR);
        SPCR |= _BV(SPE);
        pinMode(SCK, OUTPUT);
        pinMode(MOSI, OUTPUT);
    }

	

#endif
