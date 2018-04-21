//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 21.04.2018 16:31:58
#ifndef EAGLE_EBOARD_HELPLIB_SOFTWARESERIAL
#define EAGLE_EBOARD_HELPLIB_SOFTWARESERIAL
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
