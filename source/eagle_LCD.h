//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 18.04.2018 19:59:08

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



