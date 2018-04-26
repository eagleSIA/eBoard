//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 27.04.2018 00:20:08
#ifndef EAGLE_EBOARD_HELPLIB_NEOPIXEL
#define EAGLE_EBOARD_HELPLIB_NEOPIXEL
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
	
	inline bool NeoPixel::canShow(void) { return (micros() - endTime) >= 300L; }
	uint8_t *NeoPixel::getPixels(void) const {
	  return pixels;
	}
	uint16_t NeoPixel::numPixels(void) const {
	  return numLEDs;
	}
	uint8_t NeoPixel::getBrightness(void) const {
	  return brightness - 1;
	}
	NeoPixel::NeoPixel(uint16_t n, uint8_t p, uint16_t t) :
	  begun(false), brightness(0), pixels(NULL), endTime(0) {
	  updateType(t);
	  updateLength(n);
	  setPin(p);
	}
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
	void NeoPixel::clear() {
	  memset(pixels, 0, numBytes);
	}
	
#endif
