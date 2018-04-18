//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 18.04.2018 20:47:12

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

